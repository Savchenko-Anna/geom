#include "stdafx.h"

#include "main_window.h"

#include "printer_impl.h"

#include "io/point.h"
#include "geom/primitives/rectangle.h"

main_window_t::main_window_t(viewer_type * viewer)
    : viewer_(viewer)
    , size_(100000, 100000)
    , current_pos_(center_)
    , zoom_(1.0)
{
    setMouseTracking(true);
    viewer_->draw(drawer_);
}

void main_window_t::initializeGL()
{
    assert(doubleBuffer());
    setAutoBufferSwap(true);
    qglClearColor(Qt::black);
    //glEnable(GL_PROGRAM_POINT_SIZE);
}

using geom::structures::point_type;
using geom::structures::vector_type;

namespace
{
    int32 limit(geom::structures::range_type const & range, double v)
    {
        if (v < double(range.inf))
            return range.inf;
        else if (v > double(range.sup))
            return range.sup;
        else
            return int32(v);
    }

    point_type limit(point_type const & pt)
    {
        using geom::structures::rectangle_type;
        rectangle_type max_rect = rectangle_type::maximal();

        return point_type(
            limit(max_rect.x, pt.x),
            limit(max_rect.y, pt.y)
        );
    }

    // в этом месте возможно переполнение!
    vector_type const operator * (double alpha, vector_type const & v) 
    {
        using geom::structures::rectangle_type;
        rectangle_type max_rect = rectangle_type::maximal();

        return vector_type(
            limit(max_rect.x, v.x * alpha),
            limit(max_rect.y, v.y * alpha)
        );
    }
}

void main_window_t::resize_impl(int screen_w, int screen_h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    vector_type size = (zoom_ / 2) * vector_type(screen_w, screen_h);

    point_type left_bottom = center_ + (-size);
    point_type right_top   = center_ + size;

    glOrtho(left_bottom.x, right_top.x, left_bottom.y, right_top.y, -1.0, 1.0);
    glViewport(0, 0, screen_w, screen_h);
}

void main_window_t::resizeGL(int screen_w, int screen_h)
{
    resize_impl(screen_w, screen_h);
}

void main_window_t::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    for (drawer_impl::point_buffer_t const & buffer : drawer_.point_buffers)
    {
        glPointSize(buffer.radius);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        
        glVertexPointer (2, GL_INT, 0, &buffer.points[0]);
        glColorPointer  (3, GL_DOUBLE, 0, &buffer.colors[0]);

        glDrawArrays(GL_POINTS, 0, buffer.points.size() / 2);

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    }

    for (drawer_impl::segment_buffer_t const & buffer : drawer_.segment_buffers)
    {
        glLineWidth(buffer.width);
        
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glVertexPointer (2, GL_INT, 0, &buffer.segments[0]);
        glColorPointer  (3, GL_DOUBLE, 0, &buffer.colors[0]);

        glDrawArrays(GL_LINES, 0, buffer.segments.size() / 2);
        
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
    }

    printer_impl printer(   boost::bind(&main_window_t::draw_string,        this, _1, _2, _3),
                            boost::bind(&main_window_t::draw_string_global, this, _1, _2, _3)   );

    printer.corner_stream() << "Mouse pos: " << current_pos_ << endl;

    viewer_->print(printer);
}

void main_window_t::wheelEvent(QWheelEvent * e)
{
    double old_zoom = zoom_;

    int delta = e->delta() / 8 / 15;
    if (delta > 0)
    {
        for (int i = 0; i != delta; ++i)
            zoom_ *= 1.1;
    }
    else if (delta < 0)
    {
        for (int i = 0; i != delta; --i)
            zoom_ /= 1.1;
    }

    point_type pos(e->pos().x(), e->pos().y());
    point_type sz(size().width() / 2, size().height() / 2);

    vector_type diff = pos - sz;

    center_ += (old_zoom - zoom_) * vector_type(diff.x, -diff.y);
    center_ = limit(center_);

    e->accept();

    viewer_->on_move(limit(screen_to_global(e->pos())));

    resize_impl(size().width(), size().height());
    updateGL();
}

void main_window_t::mousePressEvent(QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton && e->modifiers() == Qt::NoModifier)
        start_point_ = limit(screen_to_global(e->pos()));
    else if (e->button() == Qt::RightButton)
    {
        if (viewer_->on_press(current_pos_))
        {
            drawer_.clear();
            viewer_->draw(drawer_);
            updateGL();
        }
    }
    e->accept();
}

void main_window_t::mouseMoveEvent(QMouseEvent * e)
{
    current_pos_ = limit(screen_to_global(e->pos()));

    if (start_point_ )
    {
        const int w = size().width(); 
        const int h = size().height();

        point_type pos(e->pos().x(), e->pos().y());
        point_type sz(w / 2, h / 2);

        using geom::structures::vector_type;

        vector_type diff = pos - sz;
        diff.x = -diff.x;

        center_ = *start_point_ + zoom_ * diff;
        center_ = limit(center_);

        resize_impl(w, h);
    }
    else if (viewer_->on_move(current_pos_))
    {
        drawer_.clear();
        viewer_->draw(drawer_);
    }
    e->accept();
    updateGL();
}

void main_window_t::mouseReleaseEvent(QMouseEvent * e)
{
    if (e->button() == Qt::LeftButton)
        start_point_ = boost::none;
    else if (viewer_->on_release(limit(screen_to_global(e->pos()))))
    {
        drawer_.clear();
        viewer_->draw(drawer_);
        updateGL();
    }
    e->accept();
}

void main_window_t::mouseDoubleClickEvent(QMouseEvent * event)
{
    if (viewer_->on_double_click(limit(screen_to_global(event->pos()))))
    {
        drawer_.clear();
        viewer_->draw(drawer_);
        updateGL();
    }
}

void main_window_t::keyReleaseEvent(QKeyEvent * event)
{
    if ((event->key() == Qt::Key_C) && (event->modifiers() == Qt::ControlModifier))
    {
        std::stringstream ss;
        ss << QInputDialog::getText(this, "center selection", "type point: ").toStdString();
        point_type old_pos = current_pos_;
        ss >> current_pos_;

        center_ += (current_pos_ - old_pos);

        resize_impl(size().width(), size().height());
        updateGL();
    }
    else if ((event->key() == Qt::Key_I) && (event->modifiers() == Qt::ControlModifier))
    {
        auto txt = boost::lexical_cast<std::string>(current_pos_); 
        QApplication::clipboard()->setText(txt.c_str());
    }
    else if (viewer_->on_key(event->key()))
    {
        drawer_.clear();
        viewer_->draw(drawer_);
        updateGL();
    }
    event->accept();
}

point_type main_window_t::screen_to_global(QPoint const & screen_pos) const
{
    point_type pos(screen_pos.x(), screen_pos.y());
    point_type sz(size().width() / 2, size().height() / 2);

    vector_type diff = pos - sz;
    diff.y = -diff.y;

    return center_ + zoom_ * diff;
}

void main_window_t::draw_string(int x, int y, const char * s)
{
    qglColor(Qt::white);
    renderText(x, y, s);
}

void main_window_t::draw_string_global(int x, int y, const char * s)
{
    qglColor(Qt::white);
    renderText(x, y, 0, s);
}

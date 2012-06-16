#include "visualization/viewer.h"

#include "drawer_impl.h"

using namespace visualization;

struct main_window_t : QGLWidget
{
public:
    main_window_t(viewer_type * viewer);

private:
    void initializeGL();
    void resizeGL(int, int);
    void paintGL();

    void wheelEvent(QWheelEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void keyReleaseEvent(QKeyEvent *);

    void resize_impl(int, int);
    point_type screen_to_global(QPoint const & screen_pos) const;

private:
    void draw_string(int x, int y, const char * s);
    void draw_string_global(int, int, const char * s);

private:
    viewer_type * viewer_;

    point_type center_;
    point_type size_;
    point_type current_pos_;
    double  zoom_;
    optional<point_type> start_point_;
    drawer_impl drawer_;
};

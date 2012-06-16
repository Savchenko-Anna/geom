#ifndef _DRAWER_IMPL_H_ 
#define _DRAWER_IMPL_H_ 

#include <QtOpenGL>

#include "visualization/viewer.h"

namespace visualization
{

struct drawer_impl : drawer_type
{
    void set_color(QColor const & c);
    void draw_line(segment_type const &, double width);
    void draw_line(point_type const &, point_type const &, double width);
    void draw_point(point_type const & pt, uint8 radius);

    drawer_impl()
        : current_color_ (Qt::black)
    {}

    void clear();

    struct point_buffer_t
    {
        std::vector<GLint>      points;
        std::vector<GLdouble>   colors;
        size_t radius;
    };

    struct segment_buffer_t
    {
        std::vector<GLint>      segments;
        std::vector<GLdouble>   colors;
        double width;
    };

    std::vector<point_buffer_t>     point_buffers;
    std::vector<segment_buffer_t>   segment_buffers;

private:
    QColor current_color_;
};

}

#endif /*_DRAWER_IMPL_H_*/

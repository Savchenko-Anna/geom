#ifndef _PRINTER_IMPL_H_
#define _PRINTER_IMPL_H_

#include "visualization/viewer.h"

namespace visualization
{

struct printer_impl : printer_type
{
    stream_type& corner_stream();
    stream_type& global_stream(point_type const & pt);

    printer_impl(   std::function<void (int, int, const char *)>          const & draw_string_corner,
                    std::function<void (double, double, const char *)>    const & draw_string_global);

private:
    std::function<void (double, double, const char *)>    draw_string_global_;
    int corner_stream_height_indent_;

    std::unique_ptr<stream_type> corner_stream_;
    std::unique_ptr<stream_type> global_stream_;
};

}

#endif /*_PRINTER_IMPL_H_*/

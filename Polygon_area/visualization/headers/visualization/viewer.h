#ifndef _VIEWER_H_
#define _VIEWER_H_

#include <QColor>

#include "geom/primitives/point.h"
#include "geom/primitives/segment.h"

namespace visualization 
{

    using geom::structures::point_type;
    using geom::structures::segment_type;

    struct stream_type
    {
        typedef void (* manipulator_type)(stream_type&); 

#define PRINT(type) virtual stream_type & operator << (type) = 0;
        PRINT(const char *)
        PRINT(std::string const &)
        PRINT(size_t)
        PRINT(point_type const &)
        PRINT(segment_type const &)
        PRINT(manipulator_type)
#undef PRINT
        
        virtual void end_line() = 0;

        virtual ~stream_type() {};
    };

    void endl(stream_type& s);

    struct drawer_type
    {
        virtual void set_color  (QColor const &)                                            = 0;
        virtual void draw_line  (segment_type const &,                   double width  = 1) = 0;
        virtual void draw_line  (point_type const &, point_type const &, double width  = 1) = 0;
        virtual void draw_point (point_type const &,                     uint8  radius = 1) = 0;

        virtual ~drawer_type() {};
    };

    struct printer_type
    {
        virtual stream_type& corner_stream()                        = 0;
        virtual stream_type& global_stream(point_type const & pos)  = 0;

        virtual ~printer_type() {};
    };

    struct viewer_type
    {
        virtual void draw   (drawer_type &  )           const   = 0;
        virtual void print  (printer_type & )           const   = 0;

        virtual void set_window(QWidget *)                      = 0;

        virtual bool on_key         (int key)                   = 0; 
        virtual bool on_double_click(point_type const & pos)    = 0;
        virtual bool on_move        (point_type const & pos)    = 0;
        virtual bool on_press       (point_type const & pos)    = 0;
        virtual bool on_release     (point_type const & pos)    = 0;

        virtual ~viewer_type() {};
    };

    void run_viewer(viewer_type * viewer, const char * title);

} // namespace visualization

#endif

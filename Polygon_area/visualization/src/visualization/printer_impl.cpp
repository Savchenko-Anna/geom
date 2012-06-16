#include "stdafx.h"

#include "printer_impl.h"

#include "io/point.h"
#include "io/segment.h"

namespace visualization 
{
    struct stream_impl : stream_type
    {
        stream_impl(std::function<void (const char *)> const & write)    
            : write_(write)
        {}

#define PRINT(type) \
        stream_type & operator << (type t) \
        { \
            ss_ << t; \
            return *this; \
        }
        PRINT(const char *)
        PRINT(std::string const &)
        PRINT(size_t)
        PRINT(point_type const &)
        PRINT(segment_type const &)
#undef PRINT
        stream_type & operator << (manipulator_type f)
        {
            f(*this);
            return *this;
        }

        ~stream_impl() { flush(); }

        void end_line() {}

    protected: 
        void flush()
        {
            write_(ss_.str().c_str());                 
            ss_.str("");
        }

    private:
        std::function<void (const char *)> write_;
        std::ostringstream ss_;
    };

    struct extended_stream_impl : stream_impl
    {
        extended_stream_impl(std::function<void (const char *)> const & write)    
            : stream_impl(write)
        {}

        void end_line() { flush(); }
    };

    void endl(stream_type & out) { out.end_line(); }

    printer_impl::printer_impl( std::function<void (int, int, const char *)>          const & draw_string_corner,
                                std::function<void (double, double, const char *)>    const & draw_string_global) 
        : draw_string_global_(draw_string_global)
        , corner_stream_height_indent_(15)
        , corner_stream_(
                new extended_stream_impl(
                    [draw_string_corner, &corner_stream_height_indent_] (const char * str) {
                        draw_string_corner(10, corner_stream_height_indent_, str);
                        corner_stream_height_indent_ += 15;
                    }
                ))
    {}

    stream_type & printer_impl::corner_stream()
    {
        return *corner_stream_;
    }

    stream_type & printer_impl::global_stream(point_type const & pt)
    {
        global_stream_.reset(
            new stream_impl([pt, this] (const char * str) {
                draw_string_global_(pt.x, pt.y, str);
            })
        ); 

        return *global_stream_;
    }
}

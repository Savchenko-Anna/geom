#ifndef _SEGMENT_H_
#define _SEGMENT_H_

#include <stdexcept>
#include <boost/lexical_cast.hpp>

#include "geom/primitives/point.h"

namespace geom {
namespace structures {

    struct segment_type
    {
        segment_type() {}

        segment_type(point_type const & beg, point_type const & end)
            : beg(beg)
            , end(end)
        {}

        point_type const & operator[] (size_t i) const 
        { 
            switch (i)
            {
            case 0: return beg;
            case 1: return end;
            default:
                throw std::logic_error("invalid index: " + boost::lexical_cast<std::string>(i));
            }
        }

        point_type & operator[] (size_t i) 
        { 
            switch (i)
            {
            case 0: return beg;
            case 1: return end;
            default:
                throw std::logic_error("invalid index: " + boost::lexical_cast<std::string>(i));
            }
        }

    private:
        point_type beg, end;
    };

    inline point_type const & min(segment_type const & seg) { return std::min(seg[0], seg[1]); }
    inline point_type const & max(segment_type const & seg) { return std::max(seg[0], seg[1]); }

    inline bool operator == (segment_type const & a, segment_type const & b)
    {
        return (a[0] == b[0]) && (a[1] == b[1]);
    }

    inline bool operator != (segment_type const & a, segment_type const & b)
    {
        return !(a == b);
    }
}}

#endif /* _SEGMENT_H_ */

#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include "geom/primitives/range.h"
#include "geom/primitives/point.h"

namespace geom {
namespace structures {

    struct rectangle_type
    {
        range_type x, y;

        rectangle_type(range_type const & x, range_type const & y)
            : x(x)
            , y(y)
        {}

        rectangle_type() {}

        bool is_empty() const
        {
            return x.is_empty() && y.is_empty();
        }

        bool contains(point_type const & pt) const
        {
            return x.contains(pt.x) && y.contains(pt.y);
        }

        point_type corner(size_t h, size_t v) const
        {
            return point_type(  (h == 0) ? x.inf : x.sup,
                                (v == 0) ? y.inf : y.sup  );
        }

        static rectangle_type maximal()
        {
            return rectangle_type(range_type::maximal(), range_type::maximal());
        }
    };

    inline rectangle_type const operator & (rectangle_type const & a, rectangle_type const & b)
    {
        return rectangle_type(a.x & b.x, a.y & b.y);
    }

    inline point_type center(rectangle_type const & rect)
    {
        return point_type(center(rect.x), center(rect.y));
    }
}}

#endif /* _RECTANGLE_H_ */

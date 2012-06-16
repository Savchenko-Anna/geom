#ifndef _POINT_H_
#define _POINT_H_

#include "geom/primitives/vector.h"

namespace geom {
namespace structures {

    struct point_type
    {
        int32 x, y;

        point_type(int32 x, int32 y)
            : x(x)
            , y(y)
        {}

        point_type()
            : x(0)
            , y(0)
        {}

        point_type & operator += (vector_type const & delta)
        {
            x += delta.x;
            y += delta.y;
            return *this;
        }
    };

    inline bool operator < (point_type const & a, point_type const & b)
    {
        if (a.x == b.x)
            return a.y < b.y;
        else
            return a.x < b.x;
    }

    inline bool operator > (point_type const & a, point_type const & b)
    {
        return b < a;
    }

    inline bool operator == (point_type const & a, point_type const & b)
    {
        return (a.x == b.x) && (a.y == b.y);
    }

    inline bool operator != (point_type const & a, point_type const & b)
    {
        return !(a == b);
    }

    // в этом месте возможно переполнение!
    inline vector_type const operator - (point_type const & a, point_type const & b)
    {
        return vector_type(a.x - b.x, a.y - b.y);
    }

    // в этом месте возможно переполнение!
    inline point_type const operator + (point_type const & pt, vector_type const & delta)
    {
        point_type res(pt);
        res += delta;
        return res;
    }
}}

#endif /* _POINT_H_ */

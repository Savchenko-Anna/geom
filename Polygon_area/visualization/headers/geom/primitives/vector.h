#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "type_aliases.h"
#include "geom/primitives/range.h"

namespace geom {
namespace structures {

    struct vector_type
    {
        int32 x, y;

        vector_type(int32 x, int32 y)
            : x(x)
            , y(y)
        {}
    };

    inline int64 operator ^ (vector_type const & v1, vector_type const & v2)
    {
        int64 x1 = v1.x, y1 = v1.y, x2 = v2.x, y2 = v2.y;
        return x1 * y2 - x2 * y1;
    }

    inline int64 operator * (vector_type const & v1, vector_type const & v2)
    {
        int64 x1 = v1.x, y1 = v1.y, x2 = v2.x, y2 = v2.y;
        return x1 * x2 + y1 * y2;
    }

    inline vector_type const operator - (vector_type const & v) { return vector_type(-v.x, -v.y); }

}}

#endif /* _VECTOR_H_ */

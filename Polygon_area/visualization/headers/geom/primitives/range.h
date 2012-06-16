#ifndef _RANGE_H_
#define _RANGE_H_

#include "type_aliases.h"

namespace geom {
namespace structures {

    // closed range
    struct range_type
    {
        int32 inf, sup;

        range_type(int32 inf, int32 sup)
            : inf(inf)
            , sup(sup)
        {}

        range_type()
            : inf(0)
            , sup(-1)
        {}

        bool is_empty() const { return inf > sup; }

        bool contains(int32 x) const { return (inf <= x) && (x <= sup); }

        static range_type maximal() 
        { 
            static const int32 max_val = (1 << 30) - 1;
            return range_type(-max_val, max_val);
        }
    };

    inline range_type const operator & (range_type const & a, range_type const & b)
    {
        return range_type(std::max(a.inf, b.inf), std::min(a.sup, b.sup));
    }

    inline int32 center(range_type const & r)
    {
        return (int64(1) + r.inf + r.sup) / 2;
    }

}}

#endif /* _RANGE_H_ */

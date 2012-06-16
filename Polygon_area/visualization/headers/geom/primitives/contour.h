#ifndef _CONTOUR_H_
#define _CONTOUR_H_

#include <vector>

#include "geom/primitives/point.h"
#include "common/range.h"

namespace geom {
namespace structures {

    struct contour_type
    {
        contour_type(contour_type const &)              = delete;
        contour_type& operator = (contour_type const &) = delete;

        contour_type(contour_type && cnt);
        contour_type& operator = (contour_type && cnt);

        typedef std::vector<point_type>::const_iterator const_iterator;

        const_iterator begin()    const { return pts_.begin(); }
        const_iterator end()      const { return pts_.end();   }

        size_t vertices_num() const { return pts_.size(); }

    private:
        friend struct contour_builder_type;

        contour_type(std::vector<point_type> && pts);

        std::vector<point_type> pts_;
    };

    typedef common::range_circulator<contour_type> contour_circulator;

}}

#endif /* _CONTOUR_H_ */

#ifndef _RECTANGLE_IO_H__
#define _RECTANGLE_IO_H__

#include "geom/primitives/rectangle.h"

namespace geom {
namespace structures {

    std::ostream & operator << (std::ostream & out, rectangle_type const &);
    std::istream & operator >> (std::istream & in, rectangle_type & rect);

}}

#endif /* _RECTANGLE_IO_H_ */

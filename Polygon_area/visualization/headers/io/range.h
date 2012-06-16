#ifndef _RANGE_IO_H_
#define _RANGE_IO_H_

#include "geom/primitives/range.h"

namespace geom {
namespace structures {

    std::ostream & operator << (std::ostream & out, range_type const &);

}}

#endif /* _RANGE_IO_H_ */

#ifndef _VECTOR_IO_H_
#define _VECTOR_IO_H_

#include "geom/struct/primitives/vector.h"

namespace geom {
namespace structures {

    std::ostream & operator << (std::ostream & out, vector_type const & v);

}}

#endif /* _VECTOR_IO_H_ */

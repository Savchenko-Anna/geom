#include "visualization/viewer.h"

#include "geom/primitives/rectangle.h"
#include "geom/primitives/contour.h"

namespace visualization
{
    void draw(drawer_type & drawer, geom::structures::rectangle_type    const & rect);
    void draw(drawer_type & drawer, geom::structures::contour_type      const & cnt);
}

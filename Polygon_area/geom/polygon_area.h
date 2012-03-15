#include "geom/primitives/point.h"
#include<algorithm>
#include<cmath>
#include<vector>
#include <stdlib.h>
#include <time.h>

namespace geom {
namespace algorithms {
namespace polygon_area {

    using geom::structures::point_type;

	bool check_point(const std::vector<point_type> &poly_vert, point_type pt);
	double area(const std::vector<point_type>& poly_vert); 
	double Monte_Karlo_area(const std::vector<point_type> &poly_vert, const std::vector<point_type>& 		rect_vert, int pnum);

}}}

#ifndef _POLYGON_AREA_H_
#define _POLYGON_AREA_H_

#include "geom/primitives/point.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>

namespace geom {
namespace algorithms {
namespace polygon_area {

    using geom::structures::point_type;

	bool check_point(std::vector<point_type> &poly_vert, std::vector<point_type>& rect_vert, 			point_type pt);
	double area(std::vector<point_type>& poly_vert); 
	double Monte_Karlo_area(std::vector<point_type> &poly_vert, std::vector<point_type>& rect_vert, 		int32 pnum);
	std::vector<point_type> rectangle(std::vector<point_type>& poly_vert);

}}}

#endif

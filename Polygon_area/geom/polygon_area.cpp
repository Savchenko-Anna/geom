#include<polygon_area.h>

using namespace std;

namespace geom {
namespace algorithms {
namespace polygon_area {

double area(vector<point_type>& poly_vert)
{
	int32 res = 0;
	int j;
	for(int i = 0; i < poly_vert.size(); i++)
	{
		j = (i+1)%poly_vert.size();
		res += poly_vert[i].x*poly_vert[j].y - poly_vert[j].x*poly_vert[i].y;
	}
	double res1=((double)res)/2;
	return res1;
}
bool orient(point_type A, point_type B, point_type C)
{
	vector<point_type> vertices;
	vertices.push_back(A);
	vertices.push_back(B);
	vertices.push_back(C);
	if(area(vertices) < 0) return false;
	return true;
}

double log2(double x)
{
	double res = log(x)/log(2.0);
	return res;
}
vector<point_type> rectangle(vector<point_type>& poly_vert)
{ //rectangle around poly
	int32 xmin,xmax,ymin,ymax;
	xmin = poly_vert[0].x, ymin = poly_vert[0].y;
	xmax = poly_vert[0].x, ymax = poly_vert[0].y;
	for(int i = 1; i < poly_vert.size(); i++)
	{
		if(poly_vert[i].x < xmin) xmin = poly_vert[i].x;
		if(poly_vert[i].y < ymin) ymin = poly_vert[i].y;
		if(poly_vert[i].x > xmax) xmax = poly_vert[i].x;
		if(poly_vert[i].y > ymax) ymax = poly_vert[i].y;
	}
	point_type v1,v2,v3,v4;
	vector<point_type> rect_vert;
	int powl = (int)log2((double)(xmax-xmin));
	int length = pow(2.0, (double)powl + 1);
	int powh = (int)log2((double)(ymax-ymin));
	int height = pow(2.0, (double)powh + 1);
	v1.x = xmin; v1.y = ymin; rect_vert.push_back(v1);
	v2.x = xmin + length; v2.y = ymin; rect_vert.push_back(v2);
	v3.x = xmin + length; v3.y = ymin + height; rect_vert.push_back(v3);
	v4.x = xmin; v4.y = ymin + height; rect_vert.push_back(v4);

	return rect_vert;
}

bool intersect(point_type a, point_type b, point_type c, point_type d) 
{
	return (orient(a,b,c)^orient(a,b,d)) && (orient(c,d,a)^orient(c,d,b));
}


bool check_point(vector<point_type> &poly_vert, vector<point_type>& rect_vert, point_type pt)
{
	int intersectnum;

	point_type point_for_beam;
	point_for_beam.x = rect_vert[0].x;
	point_for_beam.y = pt.y;
	intersectnum = 0;
	bool belongs_to_boundary=false;
	for(int j = 0; j < poly_vert.size(); j++)
	{
		int k,h,m;
		m=(j+1)%poly_vert.size();
		h=(j+2)%poly_vert.size();
		if(j==0){ k=poly_vert.size()-1;} else{ k=j-1; }

		if((pt.x-poly_vert[j].x)*(poly_vert[m].y-poly_vert[j].y) == 
		   (pt.y-poly_vert[j].y)*(poly_vert[m].x-poly_vert[j].x))
		{  //point belongs to the line on which poly's boundary is
			if(((poly_vert[j]<poly_vert[m])&&(poly_vert[j].x<=pt.x)&&(pt.x<=poly_vert[m].x)
										   &&(poly_vert[j].y<=pt.y)&&(pt.y<=poly_vert[m].y)) 
				||
			   ((poly_vert[m]<poly_vert[j])&&(poly_vert[m].x<=pt.x)&&(pt.x<=poly_vert[j].x)
										   &&(poly_vert[m].y<=pt.y)&&(pt.y<=poly_vert[j].y)))
			{  //point belongs to boundary
				belongs_to_boundary = true;
			}
		} 
		else
		{//doesn't belong to boundary
			if((poly_vert[j].y == poly_vert[m].y)&&(pt.y == poly_vert[j].y))
			{  //beam matches poly's side
			
				if(((poly_vert[k].y-pt.y)*(poly_vert[h].y-pt.y))<0)
				{
						intersectnum++;
				}
			} 
			/*if((pt.y == poly_vert[j].y)&&(pt.x > poly_vert[j].x))
			{  //beam crosses the vertex
				if((poly_vert[k].y-pt.y)*(poly_vert[m].y-pt.y)>0)
				{
						intersectnum++;
				}
			} */
			
			if(intersect(pt, point_for_beam, poly_vert[j], poly_vert[m])) 
			{  //beam crosses poly's side
					intersectnum++;
			}
		}
	}
	if(belongs_to_boundary || intersectnum%2 == 1)
	{
		return true;
	}
	return false;
}

int32 roll(int32 min, int32 max)
{
	static boost::mt19937 gen(time(NULL));
	boost::uniform_int<int32> dist(min, max);
	boost::variate_generator<boost::mt19937&, boost::uniform_int<int32> > p(gen, dist);
	return p();
}
double Monte_Karlo_area(vector<point_type> &poly_vert, vector<point_type>& rect_vert, int32 pnum)
{	
	int32 inside_points=0;
	for(int32 i = 0; i < pnum; i++)
	{
		point_type pt;
		pt.x = roll(rect_vert[0].x, rect_vert[2].x);
		pt.y = roll(rect_vert[0].y, rect_vert[2].y);
		if(check_point(poly_vert, rect_vert, pt)) 
		{
			inside_points++;
		}
	}
	double mkarea;
	return mkarea = area(rect_vert)*inside_points/pnum; 
}

}}}


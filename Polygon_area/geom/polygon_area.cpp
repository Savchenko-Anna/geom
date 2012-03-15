#include<polygon_area.h>

using namespace std;

namespace geom {
namespace algorithms {
namespace polygon_area {

int length;
int height;
int xmin,ymin,xmax,ymax;

double area(const vector<point_type>& poly_vert)
{
	double res = 0;
	int j;
	for(i = 0; i < poly_vert.size(); i++)
	{
		j = (i+1)%poly_vert.size();
		res += poly_vert[i].x*poly_vert[j].y - poly_vert[j].x*poly_vert[i].y;
	}
	return res/2;
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
vector<point_type> rectangle(const vector<point_type> &poly_vert)
{ //rectangle around poly
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
	length = pow(2.0, (double)powl + 1);
	int powh = (int)log2((double)(ymax-ymin));
	height = pow(2.0, (double)powh + 1);
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

vector<point_type> trow_points(int n)
{
	vector<point_type> points;
	int i = 0;
	srand(time(NULL));
	while(i < n)
	{
		point_type v;
		v.x = rand()%length + xmin;
		v.y = rand()%height + ymin;
		points.push_back(v);
		i++;
	}
	return points;
}

bool check_point(const vector<point_type> &poly_vert, point_type pt)
{
	vector<point_type> rect_vert;
	rect_vert = rectangle(poly_vert);
	int intersectnum;
	Vertex point_for_beam;
	point_for_beam.x = rect_vert[0].x;
	intersectnum = 0;
	point_for_beam.y = pt.y;
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
				pointsnum--;
			}
		} 
		else
		{//doesn't belong to boundary
			if((pt.y == poly_vert[j].y)&&(pt.x < poly_vert[j].x))
			{  //beam crosses the vertex
				if((poly_vert[k].y-pt.y)*(poly_vert[m].y-pt.y)<0)
				{
						intersectnum++;
				}
			} 
			else if((poly_vert[j].y == poly_vert[m].y)&&(pt.y == poly_vert[j].y))
			{  //beam matches poly's side
				if((poly_vert[k].y-pt.y)*(poly_vert[h].y-pt.y)<0)
				{
						intersectnum++;
				}
			} 
			else if(intersect(pt, point_for_beam, poly_vert[j], poly_vert[m])) 
			{  //beam crosses poly's side
					intersectnum++;
			}
		}
	}
	if(intersectnum%2 == 1)
	{
		return true;
	}
	return false;
}
double Monte_Karlo_area(const vector<point_type> &poly_vert, const vector<point_type> &rect_vert, int pnum)
{
	vector<point_type> rand_points;
	rand_points = trow_points(pnum);
	int inside_points=0;
	vector<point_type>::iterator it;
	for(it=rand_points.begin(); it!=rand_points.end();it++)
	{
		if(check_point(*it)) 
		{
			inside_points++;
		}
	}
	double mkarea;
	return mkarea = area(rect_vert)*inside_points/pnum; 
}
}}}
/*int main(){

	double polygon_area;
	double polygon_mkarea;

	//freopen("polygon_area.in", "r", stdin);
	//freopen("polygon_area.out", "w", stdout);

	vector<point_type> vertices;
	for(int i = 0; i < P.N; i++){
		point_type v;
		std::cin >> v.x >> v.y;
		vertices.push_back(v);
	}

	polygon_area = abs(area(P));
	polygon_mkarea = abs(Monte_Karlo_area(P));
	std::cout << "Polygon area = " << polygon_area << "\n";
	std::cout << "Polygon Monte-Karlo area = " << polygon_mkarea;
	return 0;
}

#include "visualization/viewer_adapter.h"
#include "visualization/draw_util.h"

#include "io/point.h"

#include "polygon_area.h"

using namespace visualization;
using geom::structures::point_type;
using geom::structures::contour_type;

struct polygon_area_viewer : viewer_adapter
{
		polygon_area_viewer()
			: putting_vertices(true)
			, checking_pt(true)
			, counting_marea(false)
			, pointsnum(1000000)
			, answer(false)
			//,putting_pnum(false)
		{}

    void draw(drawer_type & drawer)     const;
    void print(printer_type & printer)  const;

    bool on_double_click(point_type const & pt);
    bool on_key(int key);

private:
    std::vector<point_type> poly_vert; 
	point_type point_to_check;
	std::vector<point_type> rect_vert;
	bool putting_vertices;
	//bool putting_pnum;
	bool checking_pt;
	bool counting_marea;
	bool answer;
	double area;
	double marea;
	int32 pointsnum;
    
};

void polygon_area_viewer::draw(drawer_type & drawer) const
{
    drawer.set_color(Qt::blue);
    for (point_type const & pt : poly_vert){
        drawer.draw_point(pt, 3);
	}
	for(int i = 0; i < poly_vert.size(); i++){
		point_type const & pt1 = poly_vert[i];
		point_type const & pt2 = poly_vert[(i+1)%poly_vert.size()];
		drawer.draw_line(pt1, pt2, 2);
	}
	drawer.set_color(Qt::green);
	if(!putting_vertices){
		drawer.draw_point(point_to_check, 3);
		point_type beam;
		beam.x=rect_vert[0].x;
		beam.y=point_to_check.y;
		drawer.draw_line(point_to_check, beam, 1);
	}
	drawer.set_color(Qt::red);
	
	if(!counting_marea){
		for(int i=0; i< rect_vert.size();i++){
			point_type const & pt1 = rect_vert[i];
			point_type const & pt2 = rect_vert[(i+1)%rect_vert.size()];
			drawer.draw_line(pt1, pt2, 3);
		}
	}
}

void polygon_area_viewer::print(printer_type & printer) const
{
	printer.corner_stream() << "Put vertices of polygon in counterclockwise order, then press \"d\"." << endl;
    printer.corner_stream() << "Double-click to put the point to check. Press \"Enter\"." << endl;
    if (!checking_pt){
		if(answer){
       		printer.corner_stream() <<"The point is inside the polygon" << endl;
		} else{
			printer.corner_stream() <<"The point is outside the polygon"<< endl;
		}
		printer.corner_stream() <<"Area of the polygon = " << area << endl;
		if(!counting_marea){
			printer.corner_stream() <<"mArea of the polygon = " << marea << endl;
		}
	}
	
	//printer.corner_stream() <<"For checking area with Monte-Karlo method press \"m\"." << endl
	//if(putting_pnum){
		//printer.corner_stream() <<"Put the number of random points, then press \"a\"." << endl;
	//}
	//if(!counting_mk)
		//printer.corner_stream() <<"Monte-Karlo area of the polygon = " << marea << endl;
}

bool polygon_area_viewer::on_double_click(point_type const & pt)
{
    if(putting_vertices){
		poly_vert.push_back(pt);
	} else{
    	point_to_check = pt;
		checking_pt = true;
	}
    return true;
}

bool polygon_area_viewer::on_key(int key)
{
    switch (key)
    {
    case Qt::Key_Return: 
        if (poly_vert.size() > 2)
        {
            answer = geom::algorithms::polygon_area::check_point(poly_vert, rect_vert, point_to_check);
			area = abs(geom::algorithms::polygon_area::area(poly_vert));
			checking_pt = false;
			marea = geom::algorithms::polygon_area::Monte_Karlo_area(poly_vert, rect_vert, pointsnum);
			counting_marea = false;
            return true;
        }
        break;
	/*case Qt::Key_m:
		{ 
			counting_mk = true;
			putting_pnum = true;
        }
        break;
	case Qt::Key_a:
		{ 
			marea = geom::algorithms::polygon_area::Monte_Karlo_area(&poly_vert, &rect_vert, pointsnum);
			counting_mk = false;
        	return true;
        }
        break;*/
	case Qt::Key_D:
        {
			putting_vertices = false;
			rect_vert = geom::algorithms::polygon_area::rectangle(poly_vert);
		}
		break;
    case Qt::Key_S:
        {
            std::string filename = QFileDialog::getSaveFileName(
                get_wnd(), 
                "Save Points"
            ).toStdString();
            if (filename != "")
            {
                std::ofstream out(filename.c_str());
                boost::copy(poly_vert, std::ostream_iterator<point_type>(out, "\n"));
            }
        }
        break;
    case Qt::Key_L:
        {
            std::string filename = QFileDialog::getOpenFileName(
                get_wnd(), 
                "Load Points"
            ).toStdString();
            if (filename != "")
            {
                std::ifstream in(filename.c_str());
                std::istream_iterator<point_type> beg(in), end;
                poly_vert.assign(beg, end);
                return true;
            }
        }
    }
    return false;
}

#include "stdafx.h"

#include "viewer.h"

int main(int argc, char ** argv)
{
    QApplication app(argc, argv);
    polygon_area_viewer viewer;
    visualization::run_viewer(&viewer, "Area of the polygon");
}

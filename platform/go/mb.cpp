

#include "mb.h"
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometry.hpp>
#include <iostream>

using namespace boost::geometry;

float doit() {
    model::d2::point_xy<double> p1(1, 1.2), p2(2, 2);
    return distance(p1, p2);
}

/*
int main(int argc, const char * argv[]) {
    std::cout << "Distance" << doit() << std::endl;
    return 0;
}
*/

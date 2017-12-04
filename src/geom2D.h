#ifndef TOWER_DEFENCE_2_GEOMETRY2D_H
#define TOWER_DEFENCE_2_GEOMETRY2D_H

#include <vector>

//TODO: namespace

/// 2-Dimensional point.
class Point {
public:
    Point(double xvalue, double yvalue);
    double x, y;
};

/// Collection of points connected with line segments.
typedef std::vector<Point> LineString;

/// Distance between two points.
double distance(Point &p1, Point &p2);

/// Length of the linestring.
double length(LineString &ls);


#endif //TOWER_DEFENCE_2_GEOMETRY2D_H

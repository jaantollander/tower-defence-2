#include <cmath>
#include "path.h"


Point::Point(double xvalue, double yvalue) : x(xvalue), y(yvalue) { }

double distance(Point &p1, Point &p2) {
    return hypot(p2.x - p1.x, p2.y - p1.y);
}

double length(LineString &ls) {
    double l = 0;
    for (int i = 0; i < ls.size() - 1; ++i) {
        l += distance(ls[i], ls[i+1]);
    }
    return l;
}

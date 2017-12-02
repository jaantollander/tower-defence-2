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


LineString construct_path(int x, int y, Tiles &tiles) {
    LineString path = {};

    auto tilesize = tiles.tilesize;
    auto direction = tiles.tile(x, y)->direction();

    // FIXME: directions

    // Beginning of the path
    switch (direction) {
        case north:
            path.emplace_back(Point((x + 0.5)*tilesize, (y + 1.0)*tilesize));
            break;
        case east:
            path.emplace_back(Point((x + 0.0)*tilesize, (y + 0.5)*tilesize));
            break;
        case south:
            path.emplace_back(Point((x + 0.5)*tilesize, (y + 0.0)*tilesize));
            break;
        case west:
            path.emplace_back(Point((x + 1.0)*tilesize, (y + 0.5)*tilesize));
            break;
        default:
            throw invalid_path("Invalid path");
    }

    // Follow the path
    while (0 <= x && x < tiles.xsize && 0 <= y && y < tiles.ysize) {
        // Coordinates of the center of the tile
        path.emplace_back(Point((x + 0.5)*tilesize, (y + 0.5)*tilesize));

        direction = tiles.tile(x, y)->direction();

        // Calculate new coordinates
        switch (direction) {
            case north: y -= 1; break;
            case east: x += 1; break;
            case south: y += 1; break;
            case west: x -= 1; break;
            default: throw invalid_path("Invalid path");
        }
    }

    // end of the path
    switch (direction) {
        case north:
            y -= 1;
            path.emplace_back(Point((x + 0.5)*tilesize, (y + 0.0)*tilesize));
            break;
        case east:
            x -= 1;
            path.emplace_back(Point((x + 1.0)*tilesize, (y + 0.5)*tilesize));
            break;
        case south:
            y += 1;
            path.emplace_back(Point((x + 0.5)*tilesize, (y + 1.0)*tilesize));
            break;
        case west:
            x += 1;
            path.emplace_back(Point((x + 0.0)*tilesize, (y + 0.5)*tilesize));
            break;
        default:
            throw invalid_path("Invalid path");
    }

    return path;
}


Path::Path(LineString &path) : m_path(path), m_length(length(path)) { }
Point Path::start() { return m_path.front(); }
double Path::distance_from_end(double d) { return m_length - d; }
bool Path::has_reached_end(double d) { return d >= m_length; }

Point Path::position(double d) {
    if (d <= 0)
        return m_path.front();
    else if(d >= m_length)
        return  m_path.back();
    else {
        // Find index of the line segment
        int i = 0;
        double l = 0;
        for (; i < m_path.size() - 1; ++i) {
            l += distance(m_path[i], m_path[i+1]);
            if (d <= l)
                break;
        }
        double l2 = l - d;
        auto p1 = m_path[i];
        auto p2 = m_path[i+1];
        return {(p1.x - p2.x) * l2 + p2.x, (p1.y - p2.y) * l2 + p2.y};
    }

}

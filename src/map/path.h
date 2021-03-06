#ifndef TOWER_DEFENCE_2_PATH_H
#define TOWER_DEFENCE_2_PATH_H

#include <vector>
#include "tiles.h"
#include "../geom2D.h"


/// Invalid path exception class
class invalid_path : public std::exception {
public:
    explicit invalid_path(const std::string msg) : m_msg(msg) { };
    const char* what() { return m_msg.c_str(); }
private:
    const std::string m_msg;
};

/// Construct a path from tiles. Will not detect cyclical paths!
/// @param x coordinate for starting point
/// @param y coordinate for starting point
/// @param tiles
LineString construct_path(int x, int y, Tiles &tiles);

/// Class for moving objects along a path consisting of connected line segments.
class Path {
public:
    /// Construct the path from linestring.
    explicit Path(LineString &path);

    /// Total length of the path.
    double get_length() const;

    /// Starting points of the path.
    Point start();

    /// @param d is the distance travelled by the object along the path.
    double distance_from_end(double d);

    /// @param d is the distance travelled by the object along the path.
    bool has_reached_end(double d);

    /// Compute the position along the path.
    /// @param d is the distance travelled by the object along the path.
    /// @returns the position of the object along the path.
    ///        - length <= 0 returns the starting point
    ///        - length >= m_total_length returns the ending point
    Point position(double d);

private:
    LineString m_path;

    /// Total length of the path.
    const double m_length;
};


#endif //TOWER_DEFENCE_2_PATH_H

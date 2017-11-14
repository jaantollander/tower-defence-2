#ifndef TOWER_DEFENCE_2_OBJECT_H
#define TOWER_DEFENCE_2_OBJECT_H


/// Base class for objects in tower defence. Contains position, speed and the
/// movement of the object.
class Object {
public:
    Object(int x, int y, int radius, int speed);

    void set_x(int x) { m_x = x; }
    int get_x() { return m_x; };

    void set_y(int y) { m_y = y; }
    int get_y() { return m_y; };

    int get_radius() { return m_radius; };

    /// Distance to another object.
    double distance(Object &other);

    /// Change the speed of the object between zero and maximum speed.
    void change_speed(int amount);

protected:
    int m_x;
    int m_y;
    const int m_radius;
    int m_speed;
    const int m_max_speed;
};


#endif //TOWER_DEFENCE_2_OBJECT_H

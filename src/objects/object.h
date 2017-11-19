#ifndef TOWER_DEFENCE_2_OBJECT_H
#define TOWER_DEFENCE_2_OBJECT_H


/// Base class for objects in tower defence. Contains position, speed and the
/// movement of the object.
class Object {
public:
    Object(int x, int y, int radius, int speed);

    int x();
    int y();
    int radius();

    void set_x(int x);
    void set_y(int y);

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

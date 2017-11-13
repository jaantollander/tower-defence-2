#include <cmath>
#include "object.h"

Object::Object(int x, int y, int radius, int speed) :
        m_x(x), m_y(y), m_radius(radius), m_speed(speed), m_max_speed(speed) {}


double Object::distance(Object &other) {
    return hypot((m_x - other.get_x()), (m_y - other.get_y())) -
            (m_radius + other.get_radius());
}

void Object::change_speed(int amount) {
    int new_speed = m_speed + amount;
    if (new_speed < 0)
        m_speed = 0;
    else if (new_speed > m_max_speed)
        m_speed = m_max_speed;
    else
        m_speed = new_speed;
}

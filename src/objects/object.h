#ifndef TOWER_DEFENCE_2_OBJECT_H
#define TOWER_DEFENCE_2_OBJECT_H


/* Base class for objects in tower defence. Contains position, speed and the
 * movement of the object.
 */
class Object {
    //TODO: constructor

    /* Distance to another object.
     */
    double distance(Object &other);

    /* Move the object.
     */
    void move();

    /* Change the speed of the object between zero and maximum speed.
     */
    void change_speed(int amount);

protected:
    int x;
    int y;
    int max_speed;
    int speed;
};


#endif //TOWER_DEFENCE_2_OBJECT_H

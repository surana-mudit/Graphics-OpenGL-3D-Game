#include "main.h"

#ifndef BOAT_H
#define BOAT_H


class Boat {
public:
    Boat() {}
    Boat(float x, float y, color_t color);
    glm::vec3 position;
    float rotation;
    float rotation_y;
    void draw(glm::mat4 VP, int flag);
    void set_position(float x, float y);
    void tick();
    double speed;
    double accr;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BOAT_H
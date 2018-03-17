#include "main.h"

#ifndef BARREL_H
#define BARREL_H


class Barrel {
public:
    Barrel() {}
    Barrel(float x, float z, color_t color);
    glm::vec3 position;
    float rotation;
    // float rotation_y;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    void tick();
    double speed;
    // double accr;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // BARREL_H
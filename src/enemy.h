#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:
    Enemy() {}
    Enemy(float x, float z, color_t color);
    glm::vec3 position;
    float rotation;
    float rotation_y;
    void draw(glm::mat4 VP);
    void set_position(float x, float z);
    void tick();
    double speed;
    // double accr;
    bounding_box_t bounding_box();
private:
    VAO *object;
};

#endif // ENEMY_H
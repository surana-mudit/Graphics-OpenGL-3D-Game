#include "fireball.h"
#include "main.h"

Fireball::Fireball(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.1;
    accr = 0.005;
    static const GLfloat vertex_buffer_data[] = {
        -0.1f,0.0f,-0.1f, // triangle 1 : begin
        -0.1f,0.0f, 0.1f,
        -0.1f, 0.2f, 0.1f, // triangle 1 : end
        0.1f, 0.2f,-0.1f, // triangle 2 : begin
        -0.1f,0.0f,-0.1f,
        -0.1f, 0.2f,-0.1f, // triangle 2 : end
        0.1f,0.0f, 0.1f,
        -0.1f,0.0f,-0.1f,
        0.1f,0.0f,-0.1f,
        0.1f, 0.2f,-0.1f,
        0.1f,0.0f,-0.1f,
        -0.1f,0.0f,-0.1f,
        -0.1f,0.0f,-0.1f,
        -0.1f, 0.2f, 0.1f,
        -0.1f, 0.2f,-0.1f,
        0.1f,0.0f, 0.1f,
        -0.1f,0.0f, 0.1f,
        -0.1f,0.0f,-0.1f,
        -0.1f, 0.2f, 0.1f,
        -0.1f,0.0f, 0.1f,
        0.1f,0.0f, 0.1f,
        0.1f, 0.2f, 0.1f,
        0.1f,0.0f,-0.1f,
        0.1f, 0.2f,-0.1f,
        0.1f,0.0f,-0.1f,
        0.1f, 0.2f, 0.1f,
        0.1f,0.0f, 0.1f,
        0.1f, 0.2f, 0.1f,
        0.1f, 0.2f,-0.1f,
        -0.1f, 0.2f,-0.1f,
        0.1f, 0.2f, 0.1f,
        -0.1f, 0.2f,-0.1f,
        -0.1f, 0.2f, 0.1f,
        0.1f, 0.2f, 0.1f,
        -0.1f, 0.2f, 0.1f,
        0.1f,0.0f, 0.1f
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Fireball::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Fireball::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Fireball::tick() {
    // this->rotation += speed;
    this->position.x += speed;
    // this->position.y -= speed;
}

bounding_box_t Fireball::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x, y, z, 0.2, 0.2, 0.2 };
    return bbox;
}
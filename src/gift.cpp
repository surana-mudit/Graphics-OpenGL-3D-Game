#include "gift.h"
#include "main.h"

Gift::Gift(float x, float z, color_t color) {
    this->position = glm::vec3(x, 0, z);
    this->rotation = 0;
    speed = 0.1;
    // accr = 0.005;
    GLfloat vertex_buffer_data[] = {
        -0.5f,0.0f,-0.5f, // triangle 1 : begin
        -0.5f,0.0f,+0.5f,
        -0.5f, 1.0f,+0.5f, // triangle 1 : end
        +0.5f, 1.0f,-0.5f, // triangle 2 : begin
        -0.5f,0.0f,-0.5f,
        -0.5f, 1.0f,-0.5f, // triangle 2 : end
        +0.5f,0.0f, +0.5f,
        -0.5f,0.0f,-0.5f,
        +0.5f,0.0f,-0.5f,
        +0.5f, 1.0f,-0.5f,
        +0.5f,0.0f,-0.5f,
        -0.5f,0.0f,-0.5f,
        -0.5f,0.0f,-0.5f,
        -0.5f, 1.0f,+0.5f,
        -0.5f, 1.0f,-0.5f,
        +0.5f,0.0f, +0.5f,
        -0.5f,0.0f,+0.5f,
        -0.5f,0.0f,-0.5f,
        -0.5f, 1.0f,+0.5f,
        -0.5f,0.0f,+0.5f,
        +0.5f,0.0f, +0.5f,
        +0.5f, 1.0f, +0.5f,
        +0.5f,0.0f,-0.5f,
        +0.5f, 1.0f,-0.5f,
        +0.5f,0.0f,-0.5f,
        +0.5f, 1.0f, +0.5f,
        +0.5f,0.0f, +0.5f,
        +0.5f, 1.0f, +0.5f,
        +0.5f, 1.0f,-0.5f,
        -0.5f, 1.0f,-0.5f,
        +0.5f, 1.0f, +0.5f,
        -0.5f, 1.0f,-0.5f,
        -0.5f, 1.0f,+0.5f,
        +0.5f, 1.0f, +0.5f,
        -0.5f, 1.0f,+0.5f,
        +0.5f,0.0f, +0.5f
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Gift::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Gift::set_position(float x, float z) {
    this->position = glm::vec3(x, 0, z);
}

void Gift::tick() {
    this->rotation += speed;
    // this->position.x += speed;
    // this->position.y -= speed;
}

bounding_box_t Gift::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x, y, z, 1.0, 1.0, 1.0 };
    return bbox;
}
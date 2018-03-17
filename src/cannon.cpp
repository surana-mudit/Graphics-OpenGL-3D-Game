#include "cannon.h"
#include "main.h"

Cannon::Cannon(float x, float y, color_t color) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    speed = 0.25;
    static const GLfloat vertex_buffer_data[] = {
        -0.1f,0.0f,-0.1f, 
        -0.1f,0.0f, 0.1f,
        -0.1f, 0.2f, 0.1f, 
        0.1f, 0.2f,-0.1f, 
        -0.1f,0.0f,-0.1f,
        -0.1f, 0.2f,-0.1f, 
        0.3f,0.0f, 0.1f,
        -0.1f,0.0f,-0.1f,
        0.3f,0.0f,-0.1f,
        0.1f, 0.2f,-0.1f,
        0.1f,0.0f,-0.1f,
        -0.1f,0.0f,-0.1f,
        -0.1f,0.0f,-0.1f,
        -0.1f, 0.2f, 0.1f,
        -0.1f, 0.2f,-0.1f,
        0.3f,0.0f, 0.1f,
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
        0.3f, 0.2f, 0.1f,
        0.3f, 0.2f,-0.1f,
        -0.1f, 0.2f,-0.1f,
        0.3f, 0.2f, 0.1f,
        -0.1f, 0.2f,-0.1f,
        -0.1f, 0.2f, 0.1f,
        0.1f, 0.2f, 0.1f,
        -0.1f, 0.2f, 0.1f,
        0.1f,0.0f, 0.1f
    };

    this->object = create3DObject(GL_TRIANGLES, 12*3, vertex_buffer_data, color, GL_FILL);
}

void Cannon::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cannon::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Cannon::tick() {
    this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

// bounding_box_t Ball::bounding_box() {
//     float x = this->position.x, y = this->position.y;
//     bounding_box_t bbox = { x, y, 0.4, 0.4 };
//     return bbox;
// }
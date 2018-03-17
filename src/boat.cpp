#include "boat.h"
#include "main.h"

Boat::Boat(float x, float y, color_t color) {
    color_t arr[]={color,COLOR_BLACK,COLOR_YELLOW};
    this->position = glm::vec3(x, y, 0);
    this->rotation = 0;
    this->rotation_y = 0;
    speed = 0.25;
    accr = 0.025;
    static const GLfloat vertex_buffer_data[] = {
        // -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        // -1.0f,-1.0f, 1.0f,
        // -1.0f, 1.0f, 1.0f, // triangle 1 : end
        
        // 1.0f, 1.0f,-1.0f, // triangle 2 : begin
        // 0.0f,-1.0f,-1.0f,
        // 0.0f, 1.0f,-1.0f, // triangle 2 : end
        // 0.0f,-1.0f, 1.0f,
        // -1.0f,-1.0f,0.0f,
        // 0.0f,-1.0f,-1.0f,
        // 1.0f, 1.0f,-1.0f,
        // 1.0f,-1.0f,-1.0f,
        // 0.0f,-1.0f,-1.0f,
        // 0.0f,-1.0f,1.0f,
        // 0.0f,-1.0f,-1.0f,
        // 1.0f,-1.0f,1.0f,
        // 1.0f,-1.0f,1.0f,
        // 0.0f,-1.0f,-1.0f,
        // 1.0f,-1.0f,-1.0f,
        // 0.0f,1.0f,1.0f,
        // 0.0f,1.0f,-1.0f,
        // 1.0f,1.0f,1.0f,
        // 1.0f,1.0f,1.0f,
        // 0.0f,1.0f,-1.0f,
        // 1.0f,1.0f,-1.0f,

        // // -1.0f,-1.0f,-1.0f,
        // // -1.0f, 1.0f, 1.0f,
        // // -1.0f, 1.0f,-1.0f,
        
        // // 1.0f,-1.0f, 1.0f,
        // // -1.0f,-1.0f, 1.0f,
        // // -1.0f,-1.0f,-1.0f,
        // 0.0f, 1.0f, 1.0f,
        // 0.0f,-1.0f, 1.0f,
        // 1.0f,-1.0f, 1.0f,
        // 0.0f, 1.0f, 1.0f,
        // 0.0f, 1.0f,-1.0f,
        // -1.0f, 1.0f,0.0f,
        // // 1.0f, 1.0f, 1.0f,
        // // -1.0f, 1.0f,-1.0f,
        // // -1.0f, 1.0f, 1.0f,
        // 1.0f, 1.0f, 1.0f,
        // 0.0f, 1.0f, 1.0f,
        // 1.0f,-1.0f, 1.0f,
        // 1.0f, 1.0f, 1.0f,
        // 1.0f,-1.0f,-1.0f,
        // 1.0f, 1.0f,-1.0f,
        // 1.0f,-1.0f,-1.0f,
        // 1.0f, 1.0f, 1.0f,
        // 1.0f,-1.0f, 1.0f,

        0.5f,0.0f,-0.5f,
        -0.5f,0.0f,-0.5f,
        -0.5f,0.25f,-0.5f,     //left face
        -0.5f,0.25f,-0.5f,
        0.5f,0.0f,-0.5f,
        0.5f,0.25f,-0.5f,

        0.5f,0.0f,0.5f,
        -0.5f,0.0f,0.5f,
        -0.5f,0.25f,0.5f,
        -0.5f,0.25f,0.5f,      //right face
        0.5f,0.0f,0.5f,
        0.5f,0.25f,0.5f,

        0.5f,0.0f,-0.5f,
        0.5f,0.0f,0.5f,
        0.5f,0.25f,0.5f,       //front face
        0.5f,0.25f,0.5f,
        0.5f,0.0f,-0.5f,
        0.5f,0.25f,-0.5f,

        -0.5f,0.0f,-0.5f,
        -0.5f,0.0f,0.5f,
        -0.5f,0.25f,0.5f,     //back face
        -0.5f,0.25f,0.5f,
        -0.5f,0.0f,-0.5f,
        -0.5f,0.25f,-0.5f,

        0.5f,0.0f,-0.5f,
        0.5f,0.0f,0.5f,       //lower triangle
        1.0f,0.0f,0.0f,

        0.5f,0.25f,-0.5f,
        0.5f,0.25f,0.5f,       //upper triangle
        1.0f,0.25f,0.0f,       

        0.5f,0.0f,-0.5f,
        1.0f,0.0f,0.0f,
        0.5f,0.25f,-0.5f,      //left cover
        0.5f,0.25f,-0.5f,
        1.0f,0.0f,0.0f,
        1.0f,0.25f,0.0f,

        0.5f,0.0f,0.5f,
        1.0f,0.0f,0.0f,
        0.5f,0.25f,0.5f,      //right cover
        0.5f,0.25f,0.5f,
        1.0f,0.0f,0.0f,
        1.0f,0.25f,0.0f, 

        0.5f,0.0f,-0.5f,
        -0.5f,0.0f,-0.5f,
        -0.5f,0.0f,0.5f,     //bottom face
        -0.5f,0.0f,0.5f,
        0.5f,0.0f,-0.5f,
        0.5f,0.0f,0.5f,

    };

    this->object = create3DObject(GL_TRIANGLES, 48, vertex_buffer_data, arr, GL_FILL,42);
}

void Boat::draw(glm::mat4 VP, int flag) {
    // printf("%d\n", flag);
    Matrices.model = glm::mat4(1.0f);
    // Matrices.model1 = glm::mat4(1.0f);
    
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
    // glm::mat4 rotate1    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));

    // if (flag == 0)
    // {
    //     rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    //     Matrices.model *= (translate * rotate);
    // }
    // else
    // {
    //     rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 0, 1));
    //     rotate1    = glm::rotate((float) (this->rotation_y * M_PI / 180.0f), glm::vec3(0, 1, 0));
    //     Matrices.model *= (translate * rotate1 * rotate);
    // }
    // rotate          = rotate * glm::translate(glm::vec3(0, 0, 0));    
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    // draw3DObject(this->object);

    // Matrices.model1 *= (translate * rotate1);    
    // glm::mat4 MVP1 = VP * Matrices.model1;
    // glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP1[0][0]);
    draw3DObject(this->object);    
}

void Boat::set_position(float x, float y) {
    this->position = glm::vec3(x, y, 0);
}

void Boat::tick() {
    // this->rotation += speed;
    // this->position.x -= speed;
    // this->position.y -= speed;
}

bounding_box_t Boat::bounding_box() {
    float x = this->position.x, y = this->position.y, z = this->position.z;
    bounding_box_t bbox = { x, y, z, 1.5, 0.25, 1.0 };
    return bbox;
}
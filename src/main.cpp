#include "main.h"
#include "timer.h"
#include "ball.h"
#include "boat.h"
#include "water.h"
#include "rock.h"
#include "fireball.h"
#include "cannon.h"
#include "enemy.h"
#include "gift.h"
#include "boss.h"
#include "barrel.h"

using namespace std;

GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;

/**************************
* Customizable functions *
************************
**/
int wind1=0,wind2=0;
Ball ball1;
Boat boat;
Water water;
Rock rock[1010];
Enemy ene[20];
Fireball fireball;
Cannon cannon;
Gift gifts[100];
Boss boss;
char status[200];
Barrel barrels[50];

int k=1000, flag=0, kill=1, count=0, score=0, health=100, prize=0;
int view = 1, jum=0, fire=0, wind=0;
int t = 10;
float tower_pos_x,tower_pos_z;
float fix;
int wind3=0;
float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;

glm::vec3 eye;
glm::vec3 target;  
glm::vec3 up;
float angle;
Timer t60(1.0 / 60);

/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {

    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // use the loaded shader program
    // Don't change unless you know what you are doing
    glUseProgram (programID);

    // Eye - Location of camera. Don't change unless you are sure!!
    // glm::vec3 eye (boat.position.x-10, boat.position.y+10, boat.position.z);
    // // Target - Where is the camera looking at.  Don't change unless you are sure!!
    // glm::vec3 target (boat.position.x, boat.position.y, boat.position.z);
    // // Up - Up vector defines tilt of camera.  Don't change unless you are sure!!
    // glm::vec3 up (1, 0, 0);
    if(view==1){
       eye[0] = boat.position.x - 18*sin((boat.rotation+90) * M_PI/180.0);
       eye[1] = 10;
       eye[2] = boat.position.z - 18*cos((boat.rotation+90) * M_PI/180.0);

       target[0] = boat.position.x;
       target[1] = boat.position.y;
       target[2] = boat.position.z;

       up[0] = 0;
       up[1] = 1;
       up[2] = 0;
    }
    else if(view==2){
      // eye = (boat.position.x, boat.position.y+10, boat.position.z);
      eye[0]=boat.position.x;
      eye[1]=10.0;
      eye[2]=boat.position.z;
      // target = (boat.position.x, boat.position.y, boat.position.z);
      target[0]=boat.position.x;
      target[1]=boat.position.y;
      target[2]=boat.position.z;
      // up = (0,0,1);
      up[0]=0;
      up[1]=0;
      up[2]=1;
    }
    else if(view==3){
      // eye[0]=boat.position.x + 18;//-50*sin(boat.rotation * M_PI/180.0);
      // eye[1]=10;
      // eye[2]=boat.position.z + 18;//-50*cos(boat.rotation * M_PI/180.0);
      eye[0] = boat.position.x;
      eye[1] = 2;
      eye[2] = boat.position.z;  

      target[0] = boat.position.x+50*sin((boat.rotation+90) * M_PI/180.0);
      target[1] = boat.position.y;
      target[2] = boat.position.z+50*cos((boat.rotation+90) * M_PI/180.0);

      up[0] = 0;
      up[1] = 1;
      up[2] = 0;
    }
    else if(view==4){
      // eye[0]=boat.position.x + 18;//-50*sin(boat.rotation * M_PI/180.0);
      // eye[1]=10;
      // eye[2]=boat.position.z + 18;//-50*cos(boat.rotation * M_PI/180.0);
      eye[0] = tower_pos_x-1;
      eye[1] = 8;
      eye[2] = tower_pos_z-1;  

      target[0]=boat.position.x;
      target[1]=boat.position.y+5;
      target[2]=boat.position.z;

      up[0]=0;
      up[1]=1;
      up[2]=0;
    }


    // Compute Camera matrix (view)
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    // Don't change unless you are sure!!
    // Matrices.view = glm::lookAt(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)); // Fixed camera for 2D (ortho) in XY plane

    // Compute ViewProject matrix as view/camera might not be changed for this frame (basic scenario)
    // Don't change unless you are sure!!
    glm::mat4 VP = Matrices.projection * Matrices.view;

    // Send our transformation to the currently bound shader, in the "MVP" uniform
    // For each model you render, since the MVP will be different (at least the M part)
    // Don't change unless you are sure!!
    glm::mat4 MVP;  // MVP = Projection * View * Model

    // Scene render
    // ball1.draw(VP);
    // boat.rotate -= 90;
    // printf("%d\n", flag)

    fireball.draw(VP);
    boat.draw(VP, flag);
    water.draw(VP);
    cannon.draw(VP);
    // printf("%d\n", t);
    // if ((t%100 == 0) || (t%40==0) || (t%60==0)) {
    //     ene1.draw(VP);
    // }
    int tmp = k;
    while (tmp!=0)
    {
        tmp--;
        rock[tmp].draw(VP);
    }
    for (int i=0;i<100;i++)
    {gifts[i].draw(VP);}
    for (int i=0;i<20;i++)
    {ene[i].draw(VP);}
    for (int i=0;i<50;i++)
    {barrels[i].draw(VP);}
    // printf("%d\n", kill);
    if (kill%5 == 0)
    {
        // boss_posx = boat.position.x+5.0;
        // boss_posz = boat.position.z+0.5;
        boss.position.x = boat.position.x+20.0;
        boss.position.z = boat.position.z+20.0;
        // boss.draw(VP);
        kill++;
    }
    boss.draw(VP);

    // printf("%f\n", boat.position.z);
}

void jump(int flag1){
    if(flag1==0)
        return;
    boat.position.y += boat.speed;
    cannon.position.y += boat.speed;
    boat.speed -= boat.accr;
    cannon.speed -= boat.accr;
    fireball.position.y += boat.speed;
    fireball.speed -= boat.accr;
    if (boat.position.y<=0.0 ){
        boat.speed = 0.25;
        jum = 0;
        return;
    }
    return ;
}

void tick_input(GLFWwindow *window) {
    // t += 10;
    jump(jum);
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int up = glfwGetKey(window, GLFW_KEY_UP);
    int down = glfwGetKey(window, GLFW_KEY_DOWN);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    int f = glfwGetKey(window, GLFW_KEY_F);
    int z = glfwGetKey(window, GLFW_KEY_Z);
    int x = glfwGetKey(window, GLFW_KEY_X);
    int c = glfwGetKey(window, GLFW_KEY_C);
    int v = glfwGetKey(window, GLFW_KEY_V);
    int b = glfwGetKey(window, GLFW_KEY_B);
    // flag = 1;
    if (left) {
        // wind+=10;
        // flag = 1;
        // boat.position.z -= 0.25;
        boat.rotation += 1;
        // cannon.position.z -= 0.25;
        // cannon.rotation += 1;
        // boat.rotation -= 45;
        // ball2.rotation += -9;
    }
    if (right) {
        // wind+=10;
        // flag = 1;
        // boat.position.z += 0.25;
        boat.rotation -= 1;
        // cannon.position.z += 0.25;
        // cannon.rotation -= 1;
    }
    if (up) {
        t += 10;
        boat.position.z += 0.25*cos((boat.rotation+90)*M_PI/180.0);
        boat.position.x += 0.25*sin((boat.rotation+90)*M_PI/180.0);
        cannon.position.z += 0.25*cos((boat.rotation+90)*M_PI/180.0);
        cannon.position.x += 0.25*sin((boat.rotation+90)*M_PI/180.0);
        fireball.position.z += 0.25*cos((boat.rotation+90)*M_PI/180.0);
        fireball.position.x += 0.25*sin((boat.rotation+90)*M_PI/180.0);
    }
    if (down) {
        boat.position.z -= 0.25*cos((boat.rotation+90)*M_PI/180.0);
        boat.position.x -= 0.25*sin((boat.rotation+90)*M_PI/180.0);
        cannon.position.z -= 0.25*cos((boat.rotation+90)*M_PI/180.0);
        cannon.position.x -= 0.25*sin((boat.rotation+90)*M_PI/180.0);
        fireball.position.z -= 0.25*cos((boat.rotation+90)*M_PI/180.0);
        fireball.position.x -= 0.25*sin((boat.rotation+90)*M_PI/180.0);
    }
    if (space and jum==0) {
        jum = 1;
        jump(jum);    
    }
    if (jum==0 and boat.position.y>0.0){
        boat.position.y = 0.0;
    }
    if (z) {
        view = 1;
    }
    if (x) {
        view = 2;
    }
    if (c) {
        view = 3;
    }
    if (v) {
        tower_pos_x = boat.position.x;
        tower_pos_z = boat.position.z;
        view = 4;
    }
    if (b) {
        view = 5;
    }
    if (f) {
        fix = fireball.rotation;
        fireball.position.x = boat.position.x;
        fireball.position.y = boat.position.y;
        fireball.position.z = boat.position.z;
        fireball.speed = 0.1;
        fireball.accr = 0.005;
        fire = 1;
    }    
}

void tick_elements() {
    srand(time(NULL));

    if(wind1==0){
        wind2 = 100+rand()%900;
    }
    wind1++;
    if(wind2==wind1){
        wind3=150;
        angle = rand()%360;
    }
    if(wind3){
        boat.position.x+=0.25*sin(angle*M_PI/180.0);
        boat.position.z+=0.25*cos(angle*M_PI/180.0);
        cannon.position.x+=0.25*sin(angle*M_PI/180.0);
        cannon.position.z+=0.25*cos(angle*M_PI/180.0);
        fireball.position.x+=0.25*sin(angle*M_PI/180.0);
        fireball.position.z+=0.25*cos(angle*M_PI/180.0);
        wind3--;
    }
    // printf("%d\n", wind);
    // if (wind%100 == 0 or wind%30 == 0)
    // {      
    //     if (wind%60!=0 and wind%40!=0) {
    //         boat.position.x += 0.25*sin(rand()%360);
    //         boat.position.z += 0.25*cos(rand()%360);
    //         wind+=10;
    //     }
    // }

    if (health==0)
    {
        printf("\n\n\nGAME OVER !!!\n");
        printf("Score : %d\n",score);
        printf("Gifts Collected : %d\n",prize);
        exit(0);
    }

    sprintf(status,"\t\t\tScore: %d | Health: %d | Gifts: %d",score,health,prize);
    glfwSetWindowTitle(window,status);

    boat.tick();
    // printf("%f\n", fireball.rotation);
    // printf("%f %f %f\n", boat.position.x,boat.position.y,boat.position.z);
    // ball1.tick();
    // ball2.tick();

    int temp = k;
    while (temp)
    {
        temp--;
        if (detect_collision(boat.bounding_box(), rock[temp].bounding_box())) {
            // printf("Yes\n");
            boat.position.z -= 1.0;
            cannon.position.z -= 1.0;
            fireball.position.z -= 1.0;
            health--;
            break;
        }
    }

    if (detect_collision(fireball.bounding_box(), boss.bounding_box())) {
        count++;
        if (count==100) {
            boss.position.x += 1000.0;
            boss.position.z += 1000.0;
            score += 100;
            count = 0;
            // kill++;
        }
        // printf("%d\n", count);
    }
    // printf("%d %d\n", count,kill);
    for (int i=0;i<20;i++) {
        if (detect_collision(fireball.bounding_box(), ene[i].bounding_box())) {
            // if (kill%5 != 0){
                ene[i].position.x += 1000.0;
                ene[i].position.z += 1000.0;
                score += 10;
                kill++;
                break;
            // }
        }
    }

    if (detect_collision(boat.bounding_box(), boss.bounding_box())) {
        boat.position.z -= 1.0;
        cannon.position.z -= 1.0;
        fireball.position.z -= 1.0;
        health -= 2;
    }

    for (int i=0;i<50;i++) {
        if (detect_collision(boat.bounding_box(), barrels[i].bounding_box())) {
            score += 80;
            barrels[i].position.x += 1000;
            barrels[i].position.z += 1000;
            break;
        }
    }

    for (int i=0;i<20;i++) {
        if (detect_collision(boat.bounding_box(), ene[i].bounding_box())) {
            boat.position.z -= 1.0;
            cannon.position.z -= 1.0;
            fireball.position.z -= 1.0;
            health -= 1;
            break;
        }
    }

    for (int i=0;i<100;i++){
        if (detect_collision(boat.bounding_box(), gifts[i].bounding_box())) {
            gifts[i].position.x += 1000.0;
            gifts[i].position.z += 1000.0;
            score += 50;
            health += 10;
            prize++;
            break;
        }
    }

    // printf("%d %d\n", count, kill);

    if (fire==1) {
        fireball.position.x += fireball.speed*sin((fix+90)*M_PI/180.0);
        fireball.position.z += fireball.speed*cos((fix+90)*M_PI/180.0);
        fireball.speed += fireball.accr;
        // fire = 0;
    }

    for (int i=0;i<100;i++)
    {
        gifts[i].rotation += 5.0;
    }
    // camera_rotation_angle += 1;
}

/* Initialize the OpenGL rendering properties */
/* Add all the models to be created here */
void initGL(GLFWwindow *window, int width, int height) {
    /* Objects should be created before any other gl function and shaders */
    // Create the models
    srand(time(NULL));
    boat = Boat(0, 0, COLOR_RED);
    boat.rotation -= 90;
    water = Water(0, 0, COLOR_BLUE);
    fireball = Fireball(0, 0, COLOR_ORANGE);
    cannon = Cannon(0, 0, COLOR_YELLOW);
    boss = Boss(1000.0, 1000.0, COLOR_FORESTGREEN);
    // ene1 = Enemy(10.0, 0 , 10.0, COLOR_FORESTGREEN);
    // ene2 = Enemy(boat.position.x+2.0, 0 , boat.position.z+2.0, COLOR_FORESTGREEN);.h
    // ene1.rotation -= 90;
    // ene2.rotation -= 90;
    // gifts[0] = Gift(0,0,COLOR_GOLD);
    for (int i=0;i<50;i++)
    {
        barrels[i] = Barrel(-300.0+rand()%601, -300.0+rand()%601, COLOR_DARKBLUE);
    }
    for (int i=0;i<100;i++)
    {
        gifts[i] = Gift(-600.0+rand()%1201, -600.0+rand()%1201, COLOR_GOLD);
    }
    for (int i=0;i<20;i++)
    {
        ene[i] = Enemy(-100.0+rand()%201, -100.0+rand()%201, COLOR_RED);
    }
    for (int i=0;i<1000;i++) {
        rock[i] = Rock(-600.0+rand()%1201, -600+rand()%1201, COLOR_BROWN);
    }
    // for (int i=-50.0;i<=100.0;i+=15)
    // {
    //     for (int j=-50.0;j<=100.0;j+=15)
    //     {
    //         rock[k++] = Rock(i,j,COLOR_BROWN);
    //     }
    // }
    // ball1       = Ball(0, 0, COLOR_RED);
    // ball2       = Ball(-2, 0, COLOR_RED);
    // ball2.speed = -ball2.speed;

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }
        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    // return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
    //        (abs(a.z - b.z) * 2 < (a.length + b.length));
    return (sqrt(pow(a.x-b.x,2)+pow(a.z-b.z,2)) < (a.length+b.length));
}

void reset_screen() {
    // float top    = screen_center_y + 4 / screen_zoom;
    // float bottom = screen_center_y - 4 / screen_zoom;
    // float left   = screen_center_x - 4 / screen_zoom;
    // float right  = screen_center_x + 4 / screen_zoom;
    // Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
    Matrices.projection = glm::perspective(45.0f,1.0f,10.0f,250.0f);
}

void cannon_pos(double xpos, double zpos) {
    // printf("%lf %lf\n", xpos,zpos);
    // float dx = (xpos-300.0)/(zpos-300.0);
    // cannon.rotation += 0.1*(atan(dx)*180.0/M_PI);
    if(view==5){
            eye[0] = boat.position.x;
            eye[1] = 40;
            eye[2] = boat.position.z-100;

            up[0] = 0;
            up[1] = 1;
            up[2] = 0;

            target[0] = boat.position.x+ (xpos-300)/300 * 50;
            target[1] = boat.position.y;
            target[2] = boat.position.z+ (zpos-300)/300 * 50;
    }
    else {
        cannon.rotation = boat.rotation-((3*xpos/5) - 180);
        fireball.rotation = boat.rotation-((3*xpos/5) - 180);
    }// cannon.rotation_h = -(3*y/20) + 90;
    // printf("%f\n", cannon.rotation);

}
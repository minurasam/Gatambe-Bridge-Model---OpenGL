#include <stdlib.h>  
#include <GL/glut.h>  
#include <math.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <iostream>
using namespace std;

GLfloat x = 2.0f;
GLfloat y = 2.0f;
GLfloat z = 2.0f;

GLuint makeaTree;

GLfloat poss = 0.0f;
GLfloat possNut = 0.0f;
// (to move all the rendered environment) Calls in keyboard method
GLfloat moveX = 0.0f;
GLfloat moveY = 0.0f;
GLfloat moveZ = 0.0f;

// (to move all the rendered environment) Calls in keyboard method
GLfloat rotX = 0.0f;
GLfloat rotY = 0.0f;
GLfloat rotZ = 0.0f;

//variables to move the camera
GLfloat camY = 5.0f;
GLfloat camX = 5.0f;
GLfloat camZ = 0.0f;


GLUquadricObj* qobj;   //For circle




void initLights() {
    // Lighting setup
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_LIGHT0);

    // Set lighting intensity and color
    GLfloat qaAmbientLight[] = { 0.3, 0.3, 0.3, 1.0 };
    GLfloat qaDiffuseLight[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat qaSpecularLight[] = { 1.0, 1.0, 1.0, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, qaSpecularLight);

    // Set the light position
    GLfloat qaLightPosition[] = { 0,10, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);

    glLightfv(GL_LIGHT1, GL_AMBIENT, qaAmbientLight);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, qaDiffuseLight);
    glLightfv(GL_LIGHT1, GL_SPECULAR, qaSpecularLight);
    GLfloat qaLightPosition1[] = { 10, 10, 0.0, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, qaLightPosition1);

}

void drawAxes() {

    glBegin(GL_LINES);

    glLineWidth(10.5);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-20, 0, 0);
    glVertex3f(20, 0, 0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(0, -20, 0);
    glVertex3f(0, 20, 0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(0, 0, -20);
    glVertex3f(0, 0, 20);

    glEnd();
}

void keyboardSpecial(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {
        moveZ += 1;
    }
    if (key == GLUT_KEY_DOWN) {
        moveZ -= 1;
    }

    if (key == GLUT_KEY_LEFT) {
        rotY += 5;
    }
    if (key == GLUT_KEY_RIGHT) {
        rotY -= 5;
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'w')
        camY += 0.5f;
    if (key == 's')
        camY -= 0.5;
    if (key == 'a')
        camX += 0.5f;
    if (key == 'd')
        camX -= 0.5;
    if (key == '1')
        glEnable(GL_LIGHT0);
    if (key == '!')
        glDisable(GL_LIGHT0);
    if (key == '2')
        glEnable(GL_LIGHT1);
    if (key == '@')
        glDisable(GL_LIGHT1);

    if (key == 'c')
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    if (key == 'C')
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


    glutPostRedisplay();
}

GLfloat animateRotation = 0.0f;

void Timer(int x) {
    animateRotation += animateRotation >= 360.0 ? -animateRotation : 5;
    poss += poss >= 20 ? -poss : 0.2;
    possNut += possNut >= 19 ? -possNut : 0.2;
    glutPostRedisplay();

    glutTimerFunc(60, Timer, 1);
}
void drawCube() {
    // glTranslatef(0.0, 1.6, 0.0);
            // BACK
    glBegin(GL_QUADS);
    glColor3f(0.4f, 0.3f, 0.5f);
    glVertex3f(11 * x, y, z);
    glVertex3f(11 * x, -y, z);
    glVertex3f(-x, -y, z);
    glVertex3f(-x, y, z);
    glEnd();

    // FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex3f(11 * x, y, -z);
    glVertex3f(-x, y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(11 * x, -y, -z);
    glEnd();

    // LEFT
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, y, -z);
    glVertex3f(-x, y, z);
    glVertex3f(-x, -y, z);
    glEnd();

    //Right
    glBegin(GL_QUADS);
    glColor3f(1, 1, 0.5);
    glVertex3f(11 * x, y, z);
    glVertex3f(11 * x, -y, z);
    glVertex3f(11 * x, -y, -z);
    glVertex3f(11 * x, y, -z);
    glEnd();

    //Top
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.0, 0.0);
    glVertex3f(11 * x, y, -z);
    glVertex3f(11 * x, y, z);
    glVertex3f(-x, y, z);
    glVertex3f(-x, y, -z);
    glEnd();

    //Bottom
    glBegin(GL_QUADS);
    glColor3f(0.4, 0.0, 0.4);
    glVertex3f(11 * x, -y, z);
    glVertex3f(11 * x, -y, -z);
    glVertex3f(-x, -y, -z);
    glVertex3f(-x, -y, z);
    glEnd();
}
void DrawGrid() {
    GLfloat ext = 1000.0f;
    GLfloat step = 1.0f;
    GLfloat yGrid = -0.4f;
    GLint line;

    glBegin(GL_LINES);
    for (line = -ext; line <= ext; line += step) {
        glVertex3f(line, yGrid, ext);
        glVertex3f(line, yGrid, -ext);

        glVertex3f(ext, yGrid, line);
        glVertex3f(-ext, yGrid, line);
    }
    glEnd();
}
void drawarc()
{

    double equ[4];
    double equ1[4];

    equ[0] = 0;	//0.x
    equ[1] = 0;	//0.y
    equ[2] = -1;//-1.z
    equ[3] = 53;//50

    equ1[0] = -1;	//0.x
    equ1[1] = 0;	//0.y
    equ1[2] = 0;//-1.z
    equ1[3] = 111;//52



    glClipPlane(GL_CLIP_PLANE0, equ);
    glClipPlane(GL_CLIP_PLANE1, equ1);


    //now we enable the clip plane
    glEnable(GL_CLIP_PLANE1); {
        glPushMatrix(); {
            glEnable(GL_CLIP_PLANE0); {
                glColor3f(35.0f / 255.0f, 85.0f / 255.0f, 250.0f / 255.0f);	//blue
                glRotatef(90, 1.0, 0.0, 0.0);
                glTranslatef(115.0f, 55.0f, 0.0f);
                glutSolidTorus(0.75, 52, 4, 1000);

            }glDisable(GL_CLIP_PLANE0);

        }glPopMatrix();


    }glDisable(GL_CLIP_PLANE1);


    //second


    //now we enable the clip plane
    glEnable(GL_CLIP_PLANE1); {
        glPushMatrix(); {
            glEnable(GL_CLIP_PLANE0); {
                //glColor3f(0.2,0.3,0.8);	//blue

                glRotatef(90, 1.0, 0.0, 0.0);
                glTranslatef(265.0f, 200.0f, 0.0f);
                glutSolidTorus(0.75, 250, 4, 1000);

            }glDisable(GL_CLIP_PLANE0);
        }glPopMatrix();
    }glDisable(GL_CLIP_PLANE1);


}

void drawBridgeRoad() {
    // glTranslatef(0.0, 1.6, 0.0);
            // BACK
    glBegin(GL_QUADS);
    glColor3f(1, 1, 1);
    glVertex3f(x, y, z);
    glVertex3f(x, -y + 3, z);
    glVertex3f(-x, -y + 3, z);
    glVertex3f(-x, y, z);
    glEnd();

    // FRONT
    glBegin(GL_QUADS);
    glColor3f(1, 0, 0);
    glVertex3f(x, y, -z);
    glVertex3f(-x, y, -z);
    glVertex3f(-x, -y + 3, -z);
    glVertex3f(x, -y + 3, -z);
    glEnd();

    // LEFT
    glBegin(GL_QUADS);
    glColor3f(0, 0, 1);
    glVertex3f(-x, -y + 3, -z);
    glVertex3f(-x, y, -z);
    glVertex3f(-x, y, z*11);
    glVertex3f(-x, -y + 3, z * 11);
    glEnd();

    //Right
    glBegin(GL_QUADS);
    glColor3f(1, 1, 0.5);
    glVertex3f(x, y, z * 11);
    glVertex3f(x, -y + 3, z * 11);
    glVertex3f(x, -y + 3, -z);
    glVertex3f(x, y, -z);
    glEnd();

    //Top
    glBegin(GL_QUADS);
    glColor3f(0.6, 0.0, 0.0);
    glVertex3f(x, y, -z);
    glVertex3f(x, y, z * 11);
    glVertex3f(-x, y, z * 11);
    glVertex3f(-x, y, -z);
    glEnd();

    //Bottom
    glBegin(GL_QUADS);
    glColor3f(0.4, 0.0, 0.4);
    glVertex3f(x, -y + 3, z * 11);
    glVertex3f(x, -y + 3, -z);
    glVertex3f(-x, -y + 3, -z);
    glVertex3f(-x, -y + 3, z * 11);
    glEnd();
}

void drawCylinder(GLdouble base, GLdouble top, GLdouble height, GLdouble slices, GLdouble stacks) {
    glPushMatrix();
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    gluCylinder(qobj, base, top, height, slices, stacks);
    glPopMatrix();

}



void changeSize(GLsizei w, GLsizei h) {
    glViewport(0, 0, w, h);
    GLfloat aspect_ratio = h == 0 ? w / 1 : (GLfloat)w / (GLfloat)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Define the Perspective projection frustum
    // (FOV_in_vertical, aspect_ratio, z-distance to the near plane from the camera position, z-distance to far plane from the camera position)
    gluPerspective(120.0, aspect_ratio, 1.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


}


void drawBridgePoles() {
    glPushMatrix();
    for (int i = 3; i < 20; i++)
    {
        glTranslatef(i + 6, 0, 0);
        drawCylinder(2, 2, i, 5, 1);
     }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 20);
    for (int x = 3; x < 20; x++)
    {
        glTranslatef(x + 6, 0, 0);
        drawCylinder(2, 2, x, 5, 1);  
    }
    glPopMatrix();
}

void roadSeg() {
    glPushMatrix();
    glTranslatef(30, 18, 0);
    glScalef(5.5f, 0.5f, 1);
    drawBridgeRoad();
    glPopMatrix();

    for (int i = 0; i < 100; i++)
    {

        glPushMatrix();
        glTranslatef(i + 6, 18 - (i * 0.01f), 0);
        glScalef(5.5f, 0.5f, 1);
        drawBridgeRoad();
        glPopMatrix();
    }
}

void road() {
    glPushMatrix();
    glTranslatef(0, 18, 0);
    glScalef(5.5f, 0.5f, 1);
    drawBridgeRoad();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0.5f, 0);
    glRotatef(-2.5, 0.0f, 0.0f, 1.0f);
    roadSeg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100, -4.5f, 0);
    glRotatef(-2.4f, 0.0f, 0.0f, 1.0f);
    roadSeg();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(190, -9.5f, 0);
    glRotatef(-2.8, 0.0f, 0.0f, 1.0f);
    roadSeg();
    glPopMatrix();
}

void bridge() {
    glPushMatrix();
    glTranslatef(10.75f, 2, 0);
    glScalef(1.5f, 1, 1);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-10.75f, 2, 0);
    glScalef(1.5f, 1, 1);
    glRotatef(-90, 0.0f, 1.0f, 0.0f);
    drawCube();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-300, 0, 0);
    drawBridgePoles();
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 0.0f, 1.0f, 0.0f);
    glTranslatef(-300, 0, -20);
    drawBridgePoles();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 18.2f, 0);
    glScalef(5.5f, 0.5f, 1);
    drawBridgeRoad();
    glPopMatrix();

    glPushMatrix();
    road();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 20);
    glRotatef(180, 0.0f, 1.0f, 0.0f);
    road();
    glPopMatrix();
}

void makeCylinder(float height, float base) {
    GLUquadric* obj = gluNewQuadric();
    //gluQuadricDrawStyle(obj, GLU_LINE);
    glColor3f(0.64f, 0.16, 0.16f); glPushMatrix();
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(obj, base, base - (0.2 * base), height, 20, 20);
    glPopMatrix();
    glutSwapBuffers();
}

void makeTree(GLfloat height, GLfloat base) {
    float angle;
    makeCylinder(height, base); glTranslatef(0.0, height, 0.0);
    height -= height * .2; base -= base * 0.3;
    for (int a = 0; a < 3; a++) {
        angle = rand() % 50 + 20;
        if (angle > 48)
            angle = -(rand() % 50 + 20);
        if (height > 1) {
            glPushMatrix();
            glRotatef(angle, 1, 0.0, 1);
            makeTree(height, base);
            glPopMatrix();
        }
        //else glColor3f(0.0,1.0/a,0.0);glutSolidSphere(.2,10,10); add like fruits...
    }

}

void tree() {
    glPushMatrix();
    glTranslatef(0, 0, 50);
    glCallList(makeaTree);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 50);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glCallList(makeaTree);
    glPopMatrix();

}

void trees() {
    for (int i = 0; i < 20; i++)
    {
        glPushMatrix();
        glTranslatef(i*10, 0, 0);
        tree();
        glPopMatrix();
    }
}
void oldRoads() {

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(0, 0.1, 35);
    glScalef(200, 0, 1.5);
    glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(0, 0.2, 0);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glScalef(200, 0, 0.2);
    glutSolidCube(4);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(0, 0.2, 35);
    glRotatef(0, 0.0f, 1.0f, 0.0f);
    glScalef(200, 0, 0.2);
    glutSolidCube(4);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0, 0, 0);
    glTranslatef(0, 0.1, 0);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glScalef(200, 0, 1.5);
    glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
    glColor3f(82.0 / 255.0, 88.0 / 255.0, 102.0 / 255.0);
    glTranslatef(0, 0, 50);
    glRotatef(90, 0.0f, 1.0f, 0.0f);
    glScalef(1, 0, 20);
    glutSolidCube(10000);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 35);
    glRotatef(-90, 0.0f, 0.0f, 1.0f);
    GLdouble plane[] = { -1, 0, 0, 0 };
    glClipPlane(GL_CLIP_PLANE0, plane);
    glEnable(GL_CLIP_PLANE0);
    glutSolidSphere(3.0, 50, 50);
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
}

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    // camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
    gluLookAt(0.0 + camX, 2.0 + camY, 5.0 + camZ, 0, 0, 0, 0, 1.0, 0);
    glTranslatef(moveX, moveY, moveZ);
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

    bridge();


    glPushMatrix();
    oldRoads();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(0, 0,10);
    trees();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -60);
    trees();
    glPopMatrix();


   


    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    DrawGrid();
    glPopMatrix();

    drawAxes();
    glPopMatrix();


    glutSwapBuffers();

  


}
void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    qobj = gluNewQuadric();  //inside init
    initLights();

    makeaTree = glGenLists(1);
    glNewList(makeaTree, GL_COMPILE);
    makeTree(4, 0.2f);
    glEndList();
    //glEnable(GL_LIGHTING);
    //glShadeModel(GL_SMOOTH);
    //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

}
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(150, 150);
    glutCreateWindow("OpenGL Setup Test");
    glutDisplayFunc(display);
    glutReshapeFunc(changeSize);

    // keyboard function activation
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);

    glutTimerFunc(60.0, Timer, 1);
    init();
    glutMainLoop();


    return 0;
}

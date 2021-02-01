#include <GL/glut.h>  
#include <math.h>

GLfloat x = 2.0f;
GLfloat y = 2.0f;
GLfloat z = 2.0f;


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

void display() {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

    // camera orientation (eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ)
    gluLookAt(0.0 + camX, 2.0 + camY, 5.0 + camZ, 0, 0, 0, 0, 1.0, 0);
    glTranslatef(moveX, moveY, moveZ);
    glRotatef(rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(rotZ, 0.0f, 0.0f, 1.0f);

    glPushMatrix();
    glTranslatef(10.75f, 2, 0);
    glScalef(1.5f,1, 1);
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

    qobj = gluNewQuadric();  //inside init

    initLights();
    //qobj = gluNewQuadric();
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

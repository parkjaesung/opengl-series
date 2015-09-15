#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>

#define GL_pi 3.1415f
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

static int iCull = 0;
static int iDepth = 1;
static int iOutline = 0;

void RenderScene(void)
{
    GLfloat x, y, angle;
    int pivot = 1;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    if(iCull == 1)
        glEnable(GL_CULL_FACE);
    else
        glDisable(GL_CULL_FACE);
    
    if(iDepth == 1)
        glEnable(GL_DEPTH_TEST);
    else
        glDisable(GL_DEPTH_TEST);
    
    if(iOutline == 1)
        glPolygonMode(GL_BACK, GL_LINE);
    else
        glPolygonMode(GL_BACK, GL_FILL);
    
    glPushMatrix();
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 75.0f);
    
    for (angle = 0.0f; angle <= (2.0f * GL_pi); angle += (GL_pi/10.0f)) {
        x = 50.0f * sin(angle);
        y = 50.0f * cos(angle);
        
        if (pivot % 2 == 0) {
            glColor3f(0.0f, 1.0f, 0.0f);
        } else {
            glColor3f(1.0f, 0.0f, 0.0f);
        }
        
        pivot ++;
        glVertex2f(x, y);
    }
    
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    
    for (angle = 0.0f; angle <= (2.0f * GL_pi); angle += (GL_pi/10.0f)) {
        x = 50.0f * sin(angle);
        y = 50.0f * cos(angle);
        
        if (pivot % 2 == 0) {
            glColor3f(0.0f, 1.0f, 0.0f);
        } else {
            glColor3f(1.0f, 0.0f, 0.0f);
        }
        
        pivot ++;
        glVertex2f(x, y);
    }
    
    glEnd();
    
    glPopMatrix();
    glutSwapBuffers();
}
void KeyControl(int key, int x, int y) {
    if (key == GLUT_KEY_UP)
        yRot += 5.0f;
    
    if (key == GLUT_KEY_DOWN)
        yRot -= 5.0f;
    
    if (key == GLUT_KEY_RIGHT)
        xRot += 5.0f;
    
    if (key == GLUT_KEY_LEFT)
        xRot -= 5.0f;
    
    glutPostRedisplay();
}
void SetupRC(void)
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT);
    glFrontFace(GL_CW);
}
void ChangeSize(int w, int h)
{
    
    GLfloat nRange = 100.0f;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(0, 0, w, h);
    if (w <= h)
        glOrtho(-nRange, nRange, -nRange*h / w, nRange*h / w, -nRange, nRange);
    else
        glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("SpringVertex");
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(KeyControl);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
}

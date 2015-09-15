#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>

#define GL_PI 3.1415f

static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

void SetupRC()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f );
    glEnable(GL_DEPTH_TEST);  //add
    glFrontFace(GL_CCW);      //add
    glEnable(GL_CULL_FACE);   //add
}

void TimerFunc(int value)
{
    glMatrixMode(GL_MODELVIEW);
    glutTimerFunc(100, TimerFunc, 1);
}

void ChangeSize(int w, int h)
{
    GLfloat nRange = 100.0f;
//    GLfloat fAspect;
    
    glViewport(0, 0, w, h);
    
//     fAspect = (GLfloat)w/(GLfloat)h;
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    // gluPerspective(60.0f, fAspect, 1.0f, 100.0f);
    
    if (w <= h)
        glOrtho(-nRange, nRange, -nRange * h/w, nRange*h/w, -nRange * 2.0f, nRange * 2.0f);
    else
        glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange * 2.0f, nRange * 2.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void RenderScene() {
    static GLfloat fElect1=0.0f;
    
    glClear(GL_COLOR_BUFFER_BIT |
        GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -100.0f);
    glColor3ub(255, 0,0);
    glutSolidSphere(10.0f,15,15);
    
    glPushMatrix();
    glRotatef(fElect1, 0.0f,1.0f,0.0f);
    glTranslatef(90.0f,0.0f,0.0f);
    glColor3ub(255,100,0);
    glutSolidSphere(6.0f,15,15);
    glPopMatrix();

    glPushMatrix();
    glRotatef(fElect1, 0.0f,1.0f,0.0f);
    glTranslatef(90.0f,0.0f,0.0f);
    glColor3ub(100,255,255);
    glutSolidSphere(6.0f,15,15);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(45.0f, 0.0f,0.0f, 1.0f);
    glRotatef(fElect1, 0.0f,1.0f,0.0f);
    glTranslatef(-70.0f, 0.0f,0.0f);
    glutSolidSphere(6.0f,15,15);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(90.0f,0.0f, 0.0f, 1.0f);
    glRotatef(fElect1, 0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 60.0f);
    glutSolidSphere(6.0f, 15, 15);
    glPopMatrix();
    
    fElect1 += 10.0f;
    if(fElect1 > 360.0f)
        fElect1 = 0.0f;
        
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


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(512, 512);
    glutCreateWindow("Atom");
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(33,TimerFunc,1);
    glutSpecialFunc(KeyControl);
    glutDisplayFunc(RenderScene);
    SetupRC();
    glutMainLoop();
}

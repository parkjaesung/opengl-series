#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#ifdef _WIN32
    #include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

GLfloat x1 = 0.0f;
GLfloat y1 = 0.0f;
GLsizei rsize = 30.0f;
GLsizei halfRsize = rsize/2;

GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

GLfloat window_width;
GLfloat window_height;

void RenderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f,0.0f,0.0f);
    glRectf(x1, y1, x1 + rsize, y1 + rsize);
    
    glColor3f(0.0f,1.0f,0.0f);
    glRectf(x1-rsize * 2, y1, x1 - rsize,y1 + rsize);
    
    glColor3f(0.0f,0.0f,1.0f);
    glRectf(x1-rsize, y1 - rsize - halfRsize, x1, y1 - halfRsize);
    
    glutSwapBuffers();
}

void TimerFunction2(int value)
{
    if(x1> window_width - rsize || x1 < -window_width + (rsize * 2))
        xstep = -xstep;
    
    if(y1>window_height - rsize || y1 < -window_height + (rsize * 2))
        ystep = -ystep;
    
    if(x1 > window_width - rsize)
        x1 = window_width-rsize-1;
    
    if(y1 > window_height - rsize)
        y1 = window_height-rsize-1;
    
    x1 +=xstep;
    y1 +=ystep;
    glutPostRedisplay();
    glutTimerFunc(33,TimerFunction2,1);
}

void SetupRC(void)
{	glClearColor(1.0f,1.0f,1.0f,1.0f);  }

void ChangeSize(GLsizei w, GLsizei h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(w<=h)
    {
        window_width = 100.0f;
        window_height = 100.0f*h/w;
        glOrtho (-100.0f, 100.0f, -window_height, window_height, 1.0, -1.0);
    }
    else
    {
        window_width = 100.0f*w/h;
        window_height = 100.0f;
        glOrtho (-window_width, window_width, -100.0f, 100.0f, 1.0, -1.0);
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity(); 
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("BounceRectangle");
    glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutTimerFunc(2000,TimerFunction2,1);
    SetupRC();
    glutMainLoop();
    return 0;
}

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include <stdio.h>

#define Dt 1

class Point {
public:
	Point ();
	float x[2];
	float v[2];
	float m;
	void motion ();
};

Point::Point () {
	x[0] = 0.0; x[1] = 0.0;
	v[0] = 1.0; v[1] = 0.0;
	m = 10.0;
}
void Point::motion () {
	x[0] = x[0] + v[0]*Dt;
	x[1] = x[1] + v[1]*Dt;
}

Point Punto[4];

void init () {
	for (unsigned int i = 1; i <= 4; i++)
		Punto[i-1].x[0] = (i-1)*50;
}

void square (float* center, float size) {
	glBegin(GL_POLYGON);
		glVertex2f(center[0]-size/2, center[1]-size/2);
		glVertex2f(center[0]+size/2, center[1]-size/2);
		glVertex2f(center[0]+size/2, center[1]+size/2);
		glVertex2f(center[0]-size/2, center[1]+size/2);
	glEnd();
}

void display () {
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f (1.0, 1.0, 1.0);

	for (unsigned int i = 1; i <= 4; i++) {
		square (Punto[i-1].x, 5);
	}
	
	glutSwapBuffers ();
}

void reshape (int w, int h) {
	glViewport (0, 0, w, h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (-w/2, w/2, -h/2, h/2);
}

void idle () {
	for (unsigned int i = 1; i <= 4; i++)
		Punto[i-1].motion ();

	glutPostRedisplay ();
}

int main (int argc, char** argv) {
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Collision");
	glClearColor (0.0, 0.0, 0.0, 0.0);

	init ();

	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
	glutIdleFunc (idle);

	glutMainLoop ();
	return 0;
}
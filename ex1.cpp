#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>

#define M1 10
#define M2 10
#define Dt 0.1
#define dc 0.3
#define e 1

float x1[2] = {-10.0f,10.0f}, x2[2] = {0.0f,0.0f},
		v1[2] = {1.0f,-1.0f}, v2[2] = {0.0f,0.0f};

float distance (float* x1, float* x2) {
	return sqrt ( (x1[0]-x2[0])*(x1[0]-x2[0]) + (x1[1]-x2[1])*(x1[1]-x2[1]) );
}

void drawSquare (float* centre, float l) {
	glBegin (GL_POLYGON);
		glVertex2f (centre[0]-l/2, centre[1]-l/2);
		glVertex2f (centre[0]+l/2, centre[1]-l/2);
		glVertex2f (centre[0]+l/2, centre[1]+l/2);
		glVertex2f (centre[0]-l/2, centre[1]+l/2);
	glEnd ();
}

void CalculatePositions () {

	x1[0] = x1[0] + v1[0]*Dt;
	x1[1] = x1[1] + v1[1]*Dt;

	x2[0] = x2[0] + v2[0]*Dt;
	x2[1] = x2[1] + v2[1]*Dt;

	if (distance (x1,x2) <= dc) {
		float vcm[2], v1_r[2], v2_r[2], v1_r_f[2], v2_r_f[2];

		vcm[0] = ( M1*v1[0]+M2*v2[0] ) / (M1+M2);
		vcm[1] = ( M1*v1[1]+M2*v2[1] ) / (M1+M2);

		v1_r[0] = v1[0]-vcm[0]; v1_r[1] = v1[1]-vcm[1];
		v2_r[0] = v2[0]-vcm[0]; v2_r[1] = v2[1]-vcm[1];

		v1_r_f[0] = -e*v1_r[0]; v1_r_f[1] = -e*v1_r[1];
		v2_r_f[0] = -e*v2_r[0]; v2_r_f[1] = -e*v2_r[1];

		v1[0] = vcm[0]+v1_r_f[0]; v1[1] = vcm[1]+v1_r_f[1];
		v2[0] = vcm[0]+v2_r_f[0]; v2[1] = vcm[1]+v2_r_f[1];

	}
}

void display () {
	glClear (GL_COLOR_BUFFER_BIT);

	glColor3f (1.0f, 1.0f, 1.0f);
	drawSquare (x1, 0.2);
	glColor3f (1.0f, 0.0f, 0.0f);
	drawSquare (x2, 0.2);

	glutSwapBuffers ();
}

void idle () {
	CalculatePositions ();
	glutPostRedisplay ();
}

int main (int argc, char** argv) {
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("Collision");
	glClearColor (0.0f, 0.0f, 0.0f, 0.0f);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (-10.0, 10.0, -10.0, 10.0, -1000.0, 1000.0);

	glutDisplayFunc (display);
	glutIdleFunc (idle);

	glutMainLoop ();

	return 0;
}

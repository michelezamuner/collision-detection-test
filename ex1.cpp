#include <GL/freeglut.h>
#include <GL/gl.h>
#include <cmath>
#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <slc/Vector.h>

/**
 * Masses
 */
#define M1 10
#define M2 50

#define Dt 0.017

/**
 * Distance threshold to trigger collision
 */
#define dc 0.3

/**
 * Elasticity (<= 1)
 */
#define e 1

using slc::Vector;

Vector& startx1 = *new Vector(-10.0f, 10.0f),
	startx2 = *new Vector(10.0f, 10.0f),
	startv1 = *new Vector(5.0f, -5.0f),
	startv2 = *new Vector(-5.0f, -5.0f);
float *x1 = startx1.toArray(2),
      *x2 = startx2.toArray(2),
      *v1 = startv1.toArray(2),
      *v2 = startv2.toArray(2);
const Vector& refPos = *new Vector(0.0f, 9.0f);

struct timeval start;
long mtime = 0;
float kinetic = 0;

float distance (float* x1, float* x2) {
	return sqrt ( (x1[0]-x2[0])*(x1[0]-x2[0]) + (x1[1]-x2[1])*(x1[1]-x2[1]) );
}

void drawSquare (const Vector& pos, float size) {
	float halfSize = size/2;
	glPushMatrix();
	glBegin (GL_POLYGON);
	glVertex2f(pos.getX() - halfSize, pos.getY() - halfSize);
	glVertex2f(pos.getX() + halfSize, pos.getY() - halfSize);
	glVertex2f(pos.getX() + halfSize, pos.getY() + halfSize);
	glVertex2f(pos.getX() - halfSize, pos.getY() + halfSize);
	glEnd ();
	glPopMatrix();
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

void drawText(const char* format, float value, float height, int length = 15)
{
	glPushMatrix();
	glTranslatef(-10.0f, height, 0.0f);
	glScalef(0.005f, 0.005f, 0.005f);
        char text[length] = {'\0'};
	sprintf(text, format, value);
	int i = 0;
	for (; i < length; i++)
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	glPopMatrix();
}

void display () {
	struct timeval start, end;
	gettimeofday(&start, NULL);

	Vector& prev1 = *new Vector(x1, 2),
		prev2 = *new Vector(x2, 2),
		p1, p2;
	CalculatePositions();
	p1 = *new Vector(x1, 2);
	p2 = *new Vector(x2, 2);

	glClear (GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);

	drawText("Time: %.0f", (float)mtime, 9.0f);
	drawText("Kinetic: %f", kinetic, 8.0f);
	drawText("V1: %f", sqrt(v1[0]*v1[0] + v1[1]*v1[1]), 7.0f);
	drawText("V2: %f", sqrt(v2[0]*v2[0] + v2[1]*v2[1]), 6.0f);
	
	drawText("DX1: %f", p1.getDistanceFrom(prev1), 5.0f);
	drawText("DX2: %f", p2.getDistanceFrom(prev2), 4.0f);
	drawText("X1: %f", p1.getDistanceFrom(startx1), 3.0f);
	drawText("X2: %f", p2.getDistanceFrom(startx2), 2.0f);

        drawSquare (*new Vector(x1[0], x1[1]), 0.2);
	glColor3f (1.0f, 0.0f, 0.0f);
	drawSquare (*new Vector(x2[0], x2[1]), 0.2);
	glColor3f(0.0f, 1.0f, 0.0f);
	drawSquare (refPos, 1.0f);

	// 17 milliseconds = 60FPS
	int minTimeFrame = 17;
	gettimeofday(&end, NULL);
	long mstart = start.tv_sec * 1000 + start.tv_usec/1000.0 + 0.5;
	long mend = end.tv_sec * 1000 + end.tv_usec/1000.0 + 0.5;
	long mdiff = mend - mstart;
	long timetowait = 0;
	if (mdiff < minTimeFrame) timetowait = minTimeFrame - mdiff;
	if (timetowait > 0) usleep(timetowait * 1000);
	glutSwapBuffers ();
}

void idle () {
	struct timeval t;
	gettimeofday(&t, NULL);
	mtime = ((t.tv_sec - start.tv_sec) * 1000 + (t.tv_usec - start.tv_usec)/1000.0) + 0.5;
	float v1m = sqrt(v1[0]*v1[0] + v1[1]*v1[1]);
	float v2m = sqrt(v2[0]*v2[0] + v2[1]*v2[1]);
	kinetic = 0.5 * M1 * v1m * v1m + 0.5 * M2 * v2m * v2m;
	//CalculatePositions ();
	glutPostRedisplay ();
}

int main (int argc, char** argv) {
	gettimeofday(&start, NULL);
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

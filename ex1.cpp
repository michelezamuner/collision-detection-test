#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

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

float x1[2] = {-10.0f,10.0f},    // Position of body 1
      x2[2] = {10.0f,10.0f},       // Position of body 2
      v1[2] = {1.0f,-1.0f},      // Velocity of body 1
      v2[2] = {-1.0f,-1.0f};       // Velocity of body 2

struct timeval start;
long mtime = 0;
float kinetic = 0;

float distance (float* x1, float* x2) {
	return sqrt ( (x1[0]-x2[0])*(x1[0]-x2[0]) + (x1[1]-x2[1])*(x1[1]-x2[1]) );
}

void drawSquare (float* centre, float l) {
	glPushMatrix();
	glBegin (GL_POLYGON);
	glVertex2f (centre[0]-l/2, centre[1]-l/2);
	glVertex2f (centre[0]+l/2, centre[1]-l/2);
	glVertex2f (centre[0]+l/2, centre[1]+l/2);
	glVertex2f (centre[0]-l/2, centre[1]+l/2);
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

void drawText(const char* text, const int length)
{
	int i = 0;
	for (; i < length; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
	}
}

// 60 FPS = at least 17 milliseconds
void display () {
	struct timeval start, end;
	gettimeofday(&start, NULL);

	float before1[2] = {x1[0], x1[1]};
	float before2[2] = {x2[0], x2[1]};
	//printf("Before1: %f, %f\n", before1[0], before1[1]);
	CalculatePositions();
	float movement1 = distance(x1, before1);
	float movement2 = distance(x2, before2);

	glClear (GL_COLOR_BUFFER_BIT);

	glColor3f(1.0f, 1.0f, 1.0f);

	char text[15] = "              ";
	glPushMatrix();
	glTranslatef(-10.0f, 9.0f, 0.0f);
	glScalef(0.005, 0.005, 0.005);
	sprintf(text, "Time: %ld", mtime);
	drawText(text, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10.0f, 8.0f, 0.0f);
	glScalef(0.005, 0.005, 0.005);
	sprintf(text, "Mov1: %f", movement1);
	drawText(text, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10.0f, 7.0f, 0.0f);
	glScalef(0.005, 0.005, 0.005);
	sprintf(text, "Mov2: %f", movement2);
	drawText(text, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10.0f, 6.0f, 0.0f);
	glScalef(0.005, 0.005, 0.005);
	sprintf(text, "Kinetic: %f", kinetic);
	drawText(text, 15);
	glPopMatrix();

	drawSquare (x1, 0.2);
	glColor3f (1.0f, 0.0f, 0.0f);
	drawSquare (x2, 0.2);

	int minTimeFrame = 17;
	gettimeofday(&end, NULL);
	long mstart = start.tv_sec * 1000 + start.tv_usec/1000.0 + 0.5;
	long mend = end.tv_sec * 1000 + end.tv_usec/1000.0 + 0.5;
	long mdiff = mend - mstart;
	long timetowait = 0;
	if (mdiff < minTimeFrame) timetowait = minTimeFrame - mdiff;
	if (timetowait > 0)
	{
		usleep(timetowait * 1000);
	}
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

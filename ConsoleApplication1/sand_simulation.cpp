#include <iostream>
#include "GL/glut.h"
#include "SimulationGrid.h"
#include "global.h"

float delta = 0;
SimulationGrid simulationGrid;

using namespace std;

int cnt = 0;

void drawGrid() {
	Vec position = Vec(-0.5, -0.5);
	glLineWidth(1.0f);
	glColor3f(1, 1, 1);
	glBegin(GL_LINES);
	
	for (float i = 0; i < SIZE; i++) {
		for (float t = 0; t < SIZE; t++) {
			glVertex3f(t / SIZE + position.x, i / SIZE + position.y, 0);
			glVertex3f(t / SIZE + position.x, (i + 1.0f) / SIZE + position.y, 0);

			glVertex3f(t / SIZE + position.x, (i + 1.0f) / SIZE + position.y, 0);
			glVertex3f((t + 1.0f) / SIZE + position.x, (i + 1.0f) / SIZE + position.y, 0);

			glVertex3f((t + 1.0f) / SIZE + position.x, (i + 1.0f) / SIZE + position.y, 0);
			glVertex3f((t + 1.0f) / SIZE + position.x, i / SIZE + position.y, 0);

			glVertex3f((t + 1.0f) / SIZE + position.x, i / SIZE + position.y, 0);
			glVertex3f(t / SIZE + position.x, i / SIZE + position.y, 0);
		}
	}
	glEnd();
	
	/*glBegin(GL_POINTS);
	glPointSize(5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);

	for (int i = 0; i < SIZE; i++) {
		for (int t = 0; t < SIZE; t++) {
			float x = t / SIZE + position.x;
			float y = i / SIZE + position.y;

			glVertex3f(t / SIZE + position.x, i / SIZE + position.y, 0);
		}
	}
	glVertex3f(0, 0, 0);
	glPointSize(1.0);*/
	glLineWidth(1.0f);


	glPointSize(1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	/*for (double angle = 0.0; angle <= PI * 2.0; angle += PI / 30.0) {
		glVertex3f(0.5*cos(angle), 0.5*sin(angle), 0.0f);
	}*/

	for (float i = 0; i < SIZE + 1; i++) {
		for (float t = 0; t < SIZE + 1; t++) {
			float x = t / SIZE + position.x;
			float y = i / SIZE + position.y;

			glVertex3f(t / SIZE + position.x, i / SIZE + position.y, 0);
		}
	}
	//glVertex3f(0, 0, 0.0f);
	glEnd();
	glPointSize(1.0f);
}

void drawWater() {
	Vec position = Vec(-0.5, -0.5);
	for (float i = 0; i < SIZE; i++) {
		for (float t = 0; t < SIZE; t++) {
			float density = simulationGrid.grid[(int)i][(int)t].density;
			glColor3f(density, density, density);
			glBegin(GL_POLYGON);
			glVertex3f(t / SIZE + position.x, i / SIZE + position.y, 0);
			glVertex3f(t / SIZE + position.x, (i + 1.0f) / SIZE + position.y, 0);
			glVertex3f((t + 1.0f) / SIZE + position.x, (i + 1.0f) / SIZE + position.y, 0);
			glVertex3f((t + 1.0f) / SIZE + position.x, i / SIZE + position.y, 0);
			glEnd();
		}
	}
	glColor3f(1, 1, 1);
}

void drawCircle() {
	glPointSize(5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	for (double angle = 0.0; angle <= PI * 2.0; angle += PI / 30.0) {
		glVertex3f(0.5*cos(angle), 0.5*sin(angle), 0.0f);
	}
	glVertex3f(0, 0, 0.0f);
	glEnd();
	glPointSize(1.0f);
}

void glDisplay(void) {
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	drawWater();
	drawGrid();
	//drawCircle();

	glColor3f(1.0f, 0.0f, 0.0f);
	/*glBegin(GL_POLYGON);
	glVertex3f(-1.0f + delta, -0.5f, 0.0f);
	glVertex3f(0.0f + delta, -0.5f, 0.0f);
	glVertex3f(0.0f + delta, 0.5f, 0.0f);
	glVertex3f(-1.0f + delta, 0.5f, 0.0f);
	glEnd();*/
	cnt++;
	if (cnt % 100 == 0) {

		simulationGrid.Update();
	}
	glutSwapBuffers();
}

void glReshape(int w, int h) {
	//glLoadIdentity();
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	glMatrixMode(GL_MODELVIEW);
	//gluOrtho2D(0.0, 100.0, 0.0, 100.0);
}

void Idle(void) {
	delta += 0.00005f;
	glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'q':
	case 'Q':
	case 27:
		exit(0);
		break;
	case '1':
		simulationGrid.grid[50][25].density = 1;
	}
}

void main() {
	simulationGrid = SimulationGrid();
	//simulationGrid.Render();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("1");
	//glutReshapeFunc(glReshape);
	glutDisplayFunc(glDisplay);
	glutIdleFunc(Idle);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
}
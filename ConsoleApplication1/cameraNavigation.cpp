//#include "stdafx.h"
#include <Windows.h> // exit(0)
#include "GL\glut.h"

int prevPos[2] = { 0, 0 };
unsigned char mouseState[3] = { 0 };

float zoom = 15.0;
float rot[2] = { 0.0f, 0.001f }; // x,y축에 대한 회전
float trans[2] = { 0.0f, 0.0f }; // 이동

void CameraTransform(void)
{
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -zoom);
	glTranslatef(trans[0], trans[1], 0.0);
	glRotatef(rot[0], 1, 0, 0);
	glRotatef(rot[1], 0, 1, 0);
}

void Draw(void)
{
	glEnable(GL_DEPTH_TEST); // 깊이맵을 사용!
	glEnable(GL_LIGHTING); // 조명을 쓸겁니다.
	glEnable(GL_LIGHT0); // 첫번째 조명을 적용할거예요.
	glutSolidTeapot(2.0f);
	glDisable(GL_LIGHTING); // 조명 끌거예요.
}

void Reshape(int w, int h)
{
	if (w == 0) {
		h = 1;
	}
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	CameraTransform(); // rotate, translate,..
	Draw(); // rendering
	glutSwapBuffers();
}

void Mouse(int button, int state, int x, int y)
{
	prevPos[0] = x;
	prevPos[1] = y;
	switch (button) {
	case GLUT_LEFT_BUTTON:
		mouseState[0] = (state == GLUT_DOWN ? 1 : 0);
		break;
	case GLUT_MIDDLE_BUTTON:
		mouseState[1] = (state == GLUT_DOWN ? 1 : 0);
		break;
	case GLUT_RIGHT_BUTTON:
		mouseState[2] = (state == GLUT_DOWN ? 1 : 0);
		break;
	}
	glutPostRedisplay();
}

void Motion(int x, int y)
{
	int dx = x - prevPos[0];
	int dy = y - prevPos[1];
	prevPos[0] = x;
	prevPos[1] = y;

	if (mouseState[2]) {
		zoom -= (float)0.05f * dx;
	}
	else if (mouseState[0]) {
		rot[0] += (float)0.5 * dy;
		rot[1] += (float)0.5 * dx;
	} else if (mouseState[1]) {
		trans[0] += (float)0.05 * dx;
		trans[1] -= (float)0.05 * dy;
	}
	glutPostRedisplay();
}

void main(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Camera Navigation");
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutMainLoop();
}
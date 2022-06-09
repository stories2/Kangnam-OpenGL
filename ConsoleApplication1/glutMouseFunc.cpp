
	#include <Windows.h>
	#include <glut.h>
	#include <stdio.h>

	float pos1[2] = { 0, 0 };
	float pos2[2] = { 0, 0 };
	int width = 400;
	int height = 400;

	void Display(void)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glColor3f(0.0f, 0.5f, 0.8f);
		glBegin(GL_POLYGON);
		glVertex3f(pos1[0], height - pos1[1], 0.0f);
		glVertex3f(pos1[0], height - pos2[1], 0.0f);
		glVertex3f(pos2[0], height - pos2[1], 0.0f);
		glVertex3f(pos2[0], height - pos1[1], 0.0f);
		glEnd();
		glutSwapBuffers();
	}

	void MouseClick(GLint button, GLint state, GLint x, GLint y)
	{
		if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
			pos1[0] = x;
			pos1[1] = y;
			printf("%d, %d\n", x, y);
		}
	}

	void MouseMotion(GLint x, GLint y)
	{
		pos2[0] = x;
		pos2[1] = y;
		printf("%d, %d\n", x, y);
		glutPostRedisplay();
	}

	void Reshape(int w, int h)
	{
		glLoadIdentity();
		glViewport(0, 0, 400, 400);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, width, 0.0, height, -1.0, 1.0);
	}

	void main()
	{
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
		glutInitWindowSize(width, height);
		glutCreateWindow("glutMouseFunc");
		glutReshapeFunc(Reshape);
		glutDisplayFunc(Display);
		glutMouseFunc(MouseClick);
		glutMotionFunc(MouseMotion);
		glutMainLoop();
	}

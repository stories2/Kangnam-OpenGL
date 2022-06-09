// ConsoleApplication1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "GL/glut.h"
#include <math.h>

float delta = 0;

void glDisplay(void) {
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex3f(-1.0f + delta, -0.5f, 0.0f);
	glVertex3f(0.0f + delta, -0.5f, 0.0f);
	glVertex3f(0.0f + delta, 0.5f, 0.0f);
	glVertex3f(-1.0f + delta, 0.5f, 0.0f);
	glEnd();
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
	}
}

int main()
{
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

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

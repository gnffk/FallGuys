#include "stdafx.h"
#include "Timer.h"
#include "Scene.h"
#include <iostream>


// 콜백함수
GLvoid Display(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char key, int x, int y);
GLvoid KeyboardUp(unsigned char key, int x, int y);
GLvoid SpecialKeyboard(int key, int x, int y);
GLvoid SpecialKeyboardUp(int key, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid PassiveMotion(int x, int y);
GLvoid IdleScene(GLvoid);
GLvoid TimerFunction(int value);


// --- 전역 변수
GLint winWidth = 1600, winHeight = 1000;
std::string Title = "SampleProject_8_2";

CTimer g_gameTimer{ Title };

CScene* g_pscene = nullptr;


void main(int argc, char** argv)								//--- 윈도우 출력하고 콜백함수 설정 
{
	//--- 윈도우 생성하기
	glutInit(&argc, argv);										// glut 초기화
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);	// 디스플레이 모드 설정
	glutInitWindowPosition(100, 100);							// 윈도우의 위치 지정
	glutInitWindowSize(winWidth, winHeight);								// 윈도우의 크기 지정
	glutCreateWindow(Title.c_str());									// 윈도우 생성(윈도우 이름)

	//--- GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {								// glew 초기화
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cout << "GLEW Initialized\n";
	}

	if (glewIsSupported("GL_VERSION_3_0")) {
		std::cout << "GLEW Version is 3.0\n";
	}
	else {
		std::cout << "GLEW 3.0 not supported\n";
	}

	// 씬을 생성한다.
	g_pscene = new CScene{ winWidth, winHeight };


	//	콜백함수 설정
	glutDisplayFunc(Display);									// 출력 함수의 지정
	glutReshapeFunc(Reshape);									// 다시 그리기 함수 지정
	glutKeyboardFunc(Keyboard);									// 키보드 입력(눌렀을 때) 콜백함수 지정
	glutKeyboardUpFunc(KeyboardUp);								// 키보드 입력(뗐을 때) 콜백함수 지정
	glutSpecialFunc(SpecialKeyboard);							// F1~F9 등등
	glutSpecialUpFunc(SpecialKeyboardUp);
	glutMouseFunc(Mouse);										// 클릭했을 때
	glutMotionFunc(Motion);										// 누르고 이동할 때
	glutPassiveMotionFunc(PassiveMotion);						// 누르지 않고 이동할 때
	glutIdleFunc(IdleScene);									// 아무 이벤트가 없을 때
	//glutTimerFunc(16, TimerFunction, 0);						// 특정 시간마다 할 일 설정

	glEnable(GL_DEPTH_TEST);	// 깊이검사 활성화
	glEnable(GL_CULL_FACE);		// 컬링	(뒷면 제거)
	//glFrontFace(GL_CCW);		// 컬링의 앞면 설정 (GL_CW - 시계, GL_CCW - 반시계)
	//glCullFace(GL_BACK);		// 어떤 면을 제거할지 설정

	//glEnable(GL_BLEND);			// 블렌딩 기능을 활성화한다.	// Alpha 활성화
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);	//지수를 원본 컬러 벡터 Csource의 알파값으로 설정

	glutMainLoop();												// 이벤트 처리 시작
	glutLeaveMainLoop();										// 프로그램 종료
}

GLvoid Display(GLvoid)
{
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);						// 바탕색 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// 설정된 색으로 전체를 칠하기

	// 그리기 부분 구현: 그리기 관련 부분이 여기에 포함된다.

	if (g_pscene)
		g_pscene->Render();

	glutSwapBuffers();											// 화면에 출력하기
}

GLvoid Reshape(int w, int h)
{
	winWidth = w;
	winHeight = h;
	glViewport(0, 0, w, h);
}

GLvoid Keyboard(unsigned char key, int x, int y)
{
	if (g_pscene)
		g_pscene->KeyboardEvent(GLUT_DOWN, key);

	switch (key) {
	case 27:			// ESC Key
		glutLeaveMainLoop();
		break;
	default:
		break;
	}
}

GLvoid KeyboardUp(unsigned char key, int x, int y)
{
	if (g_pscene)
		g_pscene->KeyboardEvent(GLUT_UP, key);
}

GLvoid SpecialKeyboard(int key, int x, int y)
{
	if (g_pscene)
		g_pscene->SpecialKeyEvent(GLUT_DOWN, key);
}

GLvoid SpecialKeyboardUp(int key, int x, int y)
{
	if (g_pscene)
		g_pscene->SpecialKeyEvent(GLUT_UP, key);

	switch (key) {
	case GLUT_KEY_F8:			// F9 누르면 전체화면
		
		break;
	case GLUT_KEY_F9:			// F9 누르면 전체화면
		glutFullScreenToggle();
		break;
	}
}

GLvoid Mouse(int button, int state, int x, int y)
{
	if (g_pscene)
		g_pscene->MouseEvent(button, state, x, y);
}

GLvoid Motion(int x, int y)
{
	return GLvoid();
}

GLvoid PassiveMotion(int x, int y)
{
	return GLvoid();
}

GLvoid IdleScene(GLvoid)
{
	float elapsedTime = g_gameTimer.Tick(0);	// 지난 시간 얻기 및 타이머 작동 (value를 0으로 넣으면 프레임제한 X)

	if (g_pscene)
		g_pscene->Update(elapsedTime);

	glutPostRedisplay();
}

GLvoid TimerFunction(int value)
{
	glutPostRedisplay();						// 화면 재 출력
	glutTimerFunc(16, TimerFunction, 0);			// 타이머함수 재 설정
}

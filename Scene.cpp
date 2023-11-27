#include "stdafx.h"
#include "Scene.h"
#include "CubeObject.h"
#include "Character.h"
#include <iostream>

CScene::CScene(int& width, int& height) : w_width{ width }, w_height{ height }
{
	Initialize();
}

CScene::~CScene()
{
	Release();
}

void CScene::Initialize()
{
	GLuint shader = CreateShaderProgram("./Shader/vertex.glsl", "./Shader/fragment.glsl");	// 셰이더 프로그램 생성

	//m_Cube = new CCubeObject;
	//m_Cube->SetShader(shader);
	//auto c_vao = InitCube(shader);
	//m_Cube->SetVao(c_vao.first, c_vao.second);


	m_Character = new CCharacter;
	m_Character->SetShader(shader);

	auto f_vao = InitFace(shader);
	m_Character->SetVao_face(f_vao.first, f_vao.second);
	auto b_vao = InitBody(shader);
	m_Character->SetVao_body(b_vao.first, b_vao.second);
	auto la_vao = InitLeft_arm(shader);
	m_Character->SetVao_left_arm(la_vao.first, la_vao.second);
	auto ra_vao = InitRight_arm(shader);
	m_Character->SetVao_right_leg(ra_vao.first, ra_vao.second);
	auto ll_vao = Initleft_leg(shader);
	m_Character->SetVao_left_arm(ll_vao.first, ll_vao.second);
	auto rl_vao = InitRight_leg(shader);
	m_Character->SetVao_right_arm(rl_vao.first, rl_vao.second);

	
	cameraRot.x = 0.f, cameraRot.y = 2.f, cameraRot.z = 5.f;
	cameraPos = glm::vec3{ cameraRot.x, cameraRot.y, cameraRot.z };
	cameraLook = glm::vec3{ 0.f };

	lightPos = glm::vec3{ 5.f, 5.f, 0.f };
	lightColor = glm::vec3{ 1.f, 1.f, 1.f };


}

void CScene::Update(float ElapsedTime)
{
	// 카메라
	cameraPos = glm::vec3{ cameraRot.x, cameraRot.y, cameraRot.z };

	glm::mat4 cameraMat = glm::lookAt(cameraPos, cameraLook, glm::vec3{ 0.f, 1.f, 0.f });
	glm::mat4 projectMat = glm::perspective(glm::radians(45.f), (float)w_width / (float)w_height, 0.1f, 50.f);

	//if (m_Cube) {
	//	m_Cube->SetCameraMat(cameraMat);
	//	m_Cube->SetProjectMat(projectMat);
	//	m_Cube->SetCameraPos(cameraPos);
	//	m_Cube->SetLightPos(lightPos);
	//	m_Cube->SetLightColor(lightColor);
	//	m_Cube->Update(ElapsedTime);
	//}

	if (m_Character) {
		m_Character->SetCameraMat(cameraMat);
		m_Character->SetProjectMat(projectMat);
		m_Character->SetCameraPos(cameraPos);
		m_Character->SetLightPos(lightPos);
		m_Character->SetLightColor(lightColor);
		m_Character->Update(ElapsedTime);
	}

}

void CScene::FixedUpdate()
{
}

void CScene::Render()
{
	//if (m_Cube) {
	//	m_Cube->Render();
	//}

	if (m_Character) {
		m_Character->Render();
	}
}

void CScene::Release()
{
	//delete m_Cube;
	//m_Cube = nullptr;

	delete m_Character;
	m_Character = nullptr;

}

void CScene::MouseEvent(int button, int state, int x, int y)
{
	static const int WHEEL_UP = 3, WHEEL_DOWN = 4;
	switch (state) {
	case GLUT_DOWN:
		switch (button) {
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case WHEEL_DOWN:
			break;
		case WHEEL_UP:
			break;
		}
		break;
	case GLUT_UP:
		break;
	default:
		break;
	}
}

void CScene::KeyboardEvent(int state, unsigned char key)
{
	switch (state) {
	case GLUT_DOWN:
		switch (key) {
		case 'a':
			cameraRot.x += 1.f;
			break;
		case 's':
			cameraRot.y += 1.f;
			break;
		case 'd':
			cameraRot.z += 1.f;
		case 'q':
			cameraRot.x -= 1.f;
			break;
		case 'w':
			cameraRot.y -= 1.f;
			break;
		case 'e':
			cameraRot.z -= 1.f;
			break;
		default:
			break;
		}
		break;
	case GLUT_UP:
		switch (key) {
		default:
			break;
		}
		break;
	}
}

void CScene::SpecialKeyEvent(int state, int key)
{
	switch (state) {
	case GLUT_DOWN:
		switch (key) {
		default:
			break;
		}
		break;
	case GLUT_UP:
		switch (key) {
		default:
			break;
		}
		break;
	}
}

std::pair<GLuint, GLsizei> CScene::InitCube(GLuint shader)
{
	GLuint VAO, VBO;					// 정점 데이터를 GPU에 넘겨줄 VAO, VBO 생성
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO를 정점버퍼로 설정 및 바인딩
	glm::vec3 fixedColor = { 0.0f, 0.0f, 0.0f }; // 흰색
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/left_leg.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)로 정점 데이터 복사

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// 셰이더에서 vPos의 위치 가져온다.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// 셰이더에서 vColor의 위치 가져온다.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// 셰이더에서 vNormal의 위치 가져온다.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc 찾기 실패" << std::endl;
	}
	// glVertexAttribPointer(attrib 위치, vertex 몇개씩 읽을건지, gl_float, gl_false, stride(간격), 시작 위치(포인터));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// 현재 VBO에 있는 데이터 속성 정의
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute 활성화

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitFace(GLuint shader)
{
	GLuint VAO, VBO;					// 정점 데이터를 GPU에 넘겨줄 VAO, VBO 생성
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO를 정점버퍼로 설정 및 바인딩

	glm::vec3 fixedColor = { 1.0f, 1.0f, 1.0f }; // 흰색
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/face.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)로 정점 데이터 복사

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// 셰이더에서 vPos의 위치 가져온다.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// 셰이더에서 vColor의 위치 가져온다.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// 셰이더에서 vNormal의 위치 가져온다.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc 찾기 실패" << std::endl;
	}
	// glVertexAttribPointer(attrib 위치, vertex 몇개씩 읽을건지, gl_float, gl_false, stride(간격), 시작 위치(포인터));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// 현재 VBO에 있는 데이터 속성 정의
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute 활성화

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitBody(GLuint shader)
{
	GLuint VAO, VBO;					// 정점 데이터를 GPU에 넘겨줄 VAO, VBO 생성
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO를 정점버퍼로 설정 및 바인딩

	glm::vec3 fixedColor = { 1.0f, 0.6f, 0.6f }; // 분홍색
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/body.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)로 정점 데이터 복사

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// 셰이더에서 vPos의 위치 가져온다.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// 셰이더에서 vColor의 위치 가져온다.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// 셰이더에서 vNormal의 위치 가져온다.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc 찾기 실패" << std::endl;
	}
	// glVertexAttribPointer(attrib 위치, vertex 몇개씩 읽을건지, gl_float, gl_false, stride(간격), 시작 위치(포인터));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// 현재 VBO에 있는 데이터 속성 정의
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute 활성화

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitLeft_arm(GLuint shader)
{
	GLuint VAO, VBO;					// 정점 데이터를 GPU에 넘겨줄 VAO, VBO 생성
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO를 정점버퍼로 설정 및 바인딩

	glm::vec3 fixedColor = { 1.0f, 0.6f, 0.6f }; // 분홍색
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/left_arm.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)로 정점 데이터 복사

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// 셰이더에서 vPos의 위치 가져온다.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// 셰이더에서 vColor의 위치 가져온다.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// 셰이더에서 vNormal의 위치 가져온다.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc 찾기 실패" << std::endl;
	}
	// glVertexAttribPointer(attrib 위치, vertex 몇개씩 읽을건지, gl_float, gl_false, stride(간격), 시작 위치(포인터));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// 현재 VBO에 있는 데이터 속성 정의
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute 활성화

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitRight_arm(GLuint shader)
{
	GLuint VAO, VBO;					// 정점 데이터를 GPU에 넘겨줄 VAO, VBO 생성
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO를 정점버퍼로 설정 및 바인딩

	glm::vec3 fixedColor = { 1.0f, 0.6f, 0.6f }; // 분홍색
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/right_arm.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)로 정점 데이터 복사

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// 셰이더에서 vPos의 위치 가져온다.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// 셰이더에서 vColor의 위치 가져온다.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// 셰이더에서 vNormal의 위치 가져온다.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc 찾기 실패" << std::endl;
	}
	// glVertexAttribPointer(attrib 위치, vertex 몇개씩 읽을건지, gl_float, gl_false, stride(간격), 시작 위치(포인터));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// 현재 VBO에 있는 데이터 속성 정의
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute 활성화

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::Initleft_leg(GLuint shader)
{
	GLuint VAO, VBO;					// 정점 데이터를 GPU에 넘겨줄 VAO, VBO 생성
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO를 정점버퍼로 설정 및 바인딩

	glm::vec3 fixedColor = { 1.0f, 0.6f, 0.6f }; // 분홍색
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/left_leg.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)로 정점 데이터 복사

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// 셰이더에서 vPos의 위치 가져온다.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// 셰이더에서 vColor의 위치 가져온다.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// 셰이더에서 vNormal의 위치 가져온다.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc 찾기 실패" << std::endl;
	}
	// glVertexAttribPointer(attrib 위치, vertex 몇개씩 읽을건지, gl_float, gl_false, stride(간격), 시작 위치(포인터));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// 현재 VBO에 있는 데이터 속성 정의
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute 활성화

	return { VAO, static_cast<int>(data.size()) };
}

std::pair<GLuint, GLsizei> CScene::InitRight_leg(GLuint shader)
{
	GLuint VAO, VBO;					// 정점 데이터를 GPU에 넘겨줄 VAO, VBO 생성
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO를 정점버퍼로 설정 및 바인딩

	glm::vec3 fixedColor = { 1.0f, 0.6f, 0.6f }; // 분홍색
	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/right_leg.obj", fixedColor);

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)로 정점 데이터 복사

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// 셰이더에서 vPos의 위치 가져온다.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// 셰이더에서 vColor의 위치 가져온다.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// 셰이더에서 vNormal의 위치 가져온다.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc 찾기 실패" << std::endl;
	}
	// glVertexAttribPointer(attrib 위치, vertex 몇개씩 읽을건지, gl_float, gl_false, stride(간격), 시작 위치(포인터));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// 현재 VBO에 있는 데이터 속성 정의
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute 활성화
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute 활성화

	return { VAO, static_cast<int>(data.size()) };
}
#include "stdafx.h"
#include "Scene.h"
#include "CubeObject.h"
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
	GLuint shader = CreateShaderProgram("./Shader/vertex.glsl", "./Shader/fragment.glsl");	// ���̴� ���α׷� ����

	m_Cube = new CCubeObject;
	m_Cube->SetShader(shader);
	auto c_vao = InitCube(shader);
	m_Cube->SetVao(c_vao.first, c_vao.second);

	cameraPos = glm::vec3{ 0.f, 2.f, 5.f };
	cameraLook = glm::vec3{ 0.f };

	lightPos = glm::vec3{ 5.f, 5.f, 0.f };
	lightColor = glm::vec3{ 1.f, 1.f, 1.f };
}

void CScene::Update(float ElapsedTime)
{
	glm::mat4 cameraMat = glm::lookAt(cameraPos, cameraLook, glm::vec3{ 0.f, 1.f, 0.f });
	glm::mat4 projectMat = glm::perspective(glm::radians(45.f), (float)w_width / (float)w_height, 0.1f, 50.f);

	if (m_Cube) {
		m_Cube->SetCameraMat(cameraMat);
		m_Cube->SetProjectMat(projectMat);
		m_Cube->SetCameraPos(cameraPos);
		m_Cube->SetLightPos(lightPos);
		m_Cube->SetLightColor(lightColor);
		m_Cube->Update(ElapsedTime);
	}
}

void CScene::FixedUpdate()
{
}

void CScene::Render()
{
	if (m_Cube) {
		m_Cube->Render();
	}
}

void CScene::Release()
{
	delete m_Cube;
	m_Cube = nullptr;
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
	GLuint VAO, VBO;					// ���� �����͸� GPU�� �Ѱ��� VAO, VBO ����
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);	// VBO�� �������۷� ���� �� ���ε�

	std::vector<glm::vec3> data = ReadObjWithRColorNormal("./Resources/fall.obj");

	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(glm::vec3), data.data(), GL_STATIC_DRAW);	// VBO(GPU)�� ���� ������ ����

	GLint AttribPosLoc = glGetAttribLocation(shader, "vPos");						// ���̴����� vPos�� ��ġ �����´�.
	GLint AttribColorLoc = glGetAttribLocation(shader, "vColor");					// ���̴����� vColor�� ��ġ �����´�.
	GLint AttribNormalLoc = glGetAttribLocation(shader, "vNormal");					// ���̴����� vNormal�� ��ġ �����´�.
	if (AttribPosLoc < 0 or AttribColorLoc < 0 or AttribNormalLoc < 0) {
		std::cerr << "AttribLoc ã�� ����" << std::endl;
	}
	// glVertexAttribPointer(attrib ��ġ, vertex ��� ��������, gl_float, gl_false, stride(����), ���� ��ġ(������));
	glVertexAttribPointer(AttribPosLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(0));	// ���� VBO�� �ִ� ������ �Ӽ� ����
	glEnableVertexAttribArray(AttribPosLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribColorLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	glEnableVertexAttribArray(AttribColorLoc);										// Attribute Ȱ��ȭ
	glVertexAttribPointer(AttribNormalLoc, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float)));
	glEnableVertexAttribArray(AttribNormalLoc);										// Attribute Ȱ��ȭ

	return { VAO, static_cast<int>(data.size()) };
}

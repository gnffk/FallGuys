#pragma once

class CGameObject;
class CScene
{
private:
	int& w_width;
	int& w_height;

	CGameObject* m_Cube;

	glm::vec3 cameraPos;
	glm::vec3 cameraLook;

	glm::vec3 lightPos;
	glm::vec3 lightColor;

public:
	CScene(int& width, int& height);
	~CScene();

	void Initialize();				//������ �� �� ��
	void Update(float ElapsedTime);					//Ÿ�̸ӿ��� �� ��
	void FixedUpdate();				//�浹ó�� ��
	void Render();					//��ο�
	void Release();					//�Ҹ�� �� �� ��

	void MouseEvent(int button, int state, int x, int y);
	void KeyboardEvent(int state, unsigned char key);
	void SpecialKeyEvent(int state, int key);

	std::pair<GLuint, GLsizei> InitCube(GLuint shader);
};

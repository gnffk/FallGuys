#pragma once
#include "stdafx.h"

class CGameObject
{
protected:
	GLuint m_shader;
	GLuint m_vao;

	int m_vertexCount;

	bool isInitialized;

	glm::vec3 m_pos;

	glm::mat4 modelMat;
	glm::mat4 cameraMat;
	glm::mat4 projectMat;
	
	glm::mat4 scaleMat;

public:
	CGameObject();
	virtual ~CGameObject();

	virtual void SetShader(GLuint shader) final;
	virtual void SetVao(GLuint vao, int vertexCount) final;

	virtual void Initialize();				//������ �� �� ��
	virtual void Update(float ElapsedTime);					//Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate();				//�浹ó�� ��
	virtual void Render();					//��ο�
	virtual void Release();					//�Ҹ�� �� �� ��

	void SetCameraMat(glm::mat4 camera);
	void SetProjectMat(glm::mat4 project);

	void SetCameraPos(glm::vec3 cameraPos);
	void SetLightPos(glm::vec3 lightPos);
	void SetLightColor(glm::vec3 lightColor);

	void SetPos(float x, float y, float z);
	void SetPos(glm::vec3 pos);

	void SetScale(float x, float y, float z);
	void SetScale(glm::vec3 scale);

	void SetModelMat(glm::mat4 modelMat);
};


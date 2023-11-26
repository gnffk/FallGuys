#include "CubeObject.h"
#include <iostream>

CCubeObject::CCubeObject() : CGameObject()
{
	Initialize();
}

CCubeObject::~CCubeObject()
{
	Release();
}

void CCubeObject::Initialize()
{
	m_angle = 0.f;
}

void CCubeObject::Update(float ElapsedTime)
{
	m_angle += 90.f * ElapsedTime;
	glm::mat4 rot = glm::rotate(glm::mat4(1.f), glm::radians(m_angle), glm::vec3(0.f, 1.f, 0.f));
	modelMat = rot;
	CGameObject::Update(ElapsedTime);
}

void CCubeObject::FixedUpdate()
{
	CGameObject::FixedUpdate();
}

void CCubeObject::Render()
{
	CGameObject::Render();
}

void CCubeObject::Release()
{
	CGameObject::Release();
}

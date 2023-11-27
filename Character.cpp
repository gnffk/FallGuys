#include "Character.h"
#include <iostream>

CCharacter::CCharacter()
{
	face = new CGameObject;
	body = new CGameObject;
	left_arm = new CGameObject;
	right_arm = new CGameObject;
	left_leg = new CGameObject;
	right_leg = new CGameObject;
}

CCharacter::~CCharacter()
{

}

void CCharacter::Render()
{
	face->Render();
	body->Render();
	left_arm->Render();
	right_arm->Render();
	left_leg->Render();
	right_leg->Render();
}

void CCharacter::Update(float ElapsedTime)
{
	auto final_tr = glm::translate(glm::mat4(1.f), m_pos);
	glm::mat4 tr;
	glm::mat4 sc;
	glm::mat4 rot;

	rot = glm::rotate(glm::mat4(1.f), glm::radians(45.f), glm::vec3(0.f, 0.f, 1.f));
	tr = glm::translate(glm::mat4(1.f), glm::vec3(-0.1f, 0.f, 1.4f));
	//sc = glm::scale(glm::mat4(1.f), glm::vec3(1.f, 0.3f, 1.f));
	face->SetModelMat(final_tr  * tr);
	



	face->Update(ElapsedTime);
}


void CCharacter::SetShader(GLuint shader)
{
	face->SetShader(shader);
	body->SetShader(shader);
	left_arm->SetShader(shader);
	right_arm->SetShader(shader);
	left_leg->SetShader(shader);
	right_leg->SetShader(shader);
}

void CCharacter::SetVao_face(GLuint vao, int vertexCount)
{
	face->SetVao(vao, vertexCount);
}

void CCharacter::SetVao_body(GLuint vao, int vertexCount)
{
	body->SetVao(vao, vertexCount);
}

void CCharacter::SetVao_left_arm(GLuint vao, int vertexCount)
{
	left_arm->SetVao(vao, vertexCount);
}

void CCharacter::SetVao_right_arm(GLuint vao, int vertexCount)
{
	right_arm->SetVao(vao, vertexCount);
}

void CCharacter::SetVao_left_leg(GLuint vao, int vertexCount)
{
	left_leg->SetVao(vao, vertexCount);
}

void CCharacter::SetVao_right_leg(GLuint vao, int vertexCount)
{
	right_leg->SetVao(vao, vertexCount);
}



void CCharacter::SetCameraMat(glm::mat4 cameraMat)
{
	face->SetCameraMat(cameraMat);
	body->SetCameraMat(cameraMat);
	left_arm->SetCameraMat(cameraMat);
	right_arm->SetCameraMat(cameraMat);
	left_leg->SetCameraMat(cameraMat);
	right_leg->SetCameraMat(cameraMat);
}

void CCharacter::SetProjectMat(glm::mat4 projectMat)
{
	face->SetProjectMat(projectMat);
	body->SetProjectMat(projectMat);
	left_arm->SetProjectMat(projectMat);
	right_arm->SetProjectMat(projectMat);
	left_leg->SetProjectMat(projectMat);
	right_leg->SetProjectMat(projectMat);
}

void CCharacter::SetCameraPos(glm::vec3 cameraPos)
{
	face->SetCameraPos(cameraPos);
	body->SetCameraPos(cameraPos);
	left_arm->SetCameraPos(cameraPos);
	right_arm->SetCameraPos(cameraPos);
	left_leg->SetCameraPos(cameraPos);
	right_leg->SetCameraPos(cameraPos);
}

void CCharacter::SetLightPos(glm::vec3 lightPos)
{
	face->SetLightPos(lightPos);
	body->SetLightPos(lightPos);
	left_arm->SetLightPos(lightPos);
	right_arm->SetLightPos(lightPos);
	left_leg->SetLightPos(lightPos);
	right_leg->SetLightPos(lightPos);
}

void CCharacter::SetLightColor(glm::vec3 lightColor)
{
	face->SetLightColor(lightColor);
	body->SetLightColor(lightColor);
	left_arm->SetLightColor(lightColor);
	right_arm->SetLightColor(lightColor);
	left_leg->SetLightColor(lightColor);
	right_leg->SetLightColor(lightColor);
}
#pragma once
#include "GameObject.h"

class CCubeObject : public CGameObject
{
private:
	float m_angle;

public:
	CCubeObject();
	virtual ~CCubeObject();

	virtual void Initialize() override;				//������ �� �� ��
	virtual void Update(float ElapsedTime) override;					//Ÿ�̸ӿ��� �� ��
	virtual void FixedUpdate() override;			//�浹ó�� ��
	virtual void Render() override;					//��ο�
	virtual void Release() override;				//�Ҹ�� �� �� ��
};


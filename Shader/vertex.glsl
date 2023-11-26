#version 330 core

in vec3 vPos;		// ���� ���α׷����� �޾ƿ� ���� ��ǥ��
in vec3 vColor;		// ���� ����
in vec3 vNormal;	// ���� ��������

out vec3 FragPos;
out vec3 outColor;
out vec3 outNormal;

uniform mat4 modelMat;
uniform mat4 cameraMat;
uniform mat4 projectMat;

void main()
{
	FragPos = vec3(modelMat * vec4(vPos, 1.0));
	outColor = vColor;
	outNormal = vec3(modelMat * vec4(vNormal, 1.0));
	gl_Position = projectMat * cameraMat * vec4(FragPos, 1.0);
}

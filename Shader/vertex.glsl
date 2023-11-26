#version 330 core

in vec3 vPos;		// 응용 프로그램에서 받아온 도형 좌표값
in vec3 vColor;		// 점의 색상
in vec3 vNormal;	// 점의 법선벡터

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

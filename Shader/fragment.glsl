#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 outColor;
in vec3 outNormal;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 cameraPos;

void main()
{
	float ambientLight = 0.3;										//--- 주변 조명 계수
	vec3 ambient = ambientLight * lightColor;						//--- 주변 조명 값

	vec3 normalVector = normalize(outNormal);						//--- 노말값을 정규화한다.
	vec3 lightDir = normalize(lightPos - FragPos);					//--- 표면과 조명의 위치로 조명의 방향을 결정한다.
	float diffuseLight = max(dot(normalVector, lightDir), 0.0);		//--- N과 L의 내적 값으로 강도 조절 (음의 값을 가질 수 없게 한다.)
	vec3 diffuse = diffuseLight * lightColor;						//--- 산란 반사 조명값 = 산란 반사값 * 조명 색상값

	int shininess = 128;											//--- 광택 계수
	vec3 cameraDir = normalize (cameraPos - FragPos);				//--- 관찰자의 방향
	vec3 reflectDir = reflect (-lightDir, normalVector);			//--- 반사 방향 = reflect 함수 - 입사 벡터의 반사 방향 계산
	float specularLight = max (dot(cameraDir, reflectDir), 0.0);	//--- V와 R의 내적 값으로 강도 조절 (음수 방지)
	specularLight = pow(specularLight, shininess);					//--- shininess 승을 해주어 하이라이트를 만들어준다.
	vec3 specular = specularLight * lightColor;						//--- 거울 반사 조명값 = 거울 반사값 * 조명 색상값

	vec3 result = (ambient + diffuse + specular) * outColor;		//--- 최종 조명 설정된 픽셀 색상 = (주변조명 + 산란반사조명 + 거울반사조명) * 객체 색상
	FragColor = vec4(result, 1.0);
}

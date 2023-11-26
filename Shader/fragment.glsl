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
	float ambientLight = 0.3;										//--- �ֺ� ���� ���
	vec3 ambient = ambientLight * lightColor;						//--- �ֺ� ���� ��

	vec3 normalVector = normalize(outNormal);						//--- �븻���� ����ȭ�Ѵ�.
	vec3 lightDir = normalize(lightPos - FragPos);					//--- ǥ��� ������ ��ġ�� ������ ������ �����Ѵ�.
	float diffuseLight = max(dot(normalVector, lightDir), 0.0);		//--- N�� L�� ���� ������ ���� ���� (���� ���� ���� �� ���� �Ѵ�.)
	vec3 diffuse = diffuseLight * lightColor;						//--- ��� �ݻ� ���� = ��� �ݻ簪 * ���� ����

	int shininess = 128;											//--- ���� ���
	vec3 cameraDir = normalize (cameraPos - FragPos);				//--- �������� ����
	vec3 reflectDir = reflect (-lightDir, normalVector);			//--- �ݻ� ���� = reflect �Լ� - �Ի� ������ �ݻ� ���� ���
	float specularLight = max (dot(cameraDir, reflectDir), 0.0);	//--- V�� R�� ���� ������ ���� ���� (���� ����)
	specularLight = pow(specularLight, shininess);					//--- shininess ���� ���־� ���̶���Ʈ�� ������ش�.
	vec3 specular = specularLight * lightColor;						//--- �ſ� �ݻ� ���� = �ſ� �ݻ簪 * ���� ����

	vec3 result = (ambient + diffuse + specular) * outColor;		//--- ���� ���� ������ �ȼ� ���� = (�ֺ����� + ����ݻ����� + �ſ�ݻ�����) * ��ü ����
	FragColor = vec4(result, 1.0);
}

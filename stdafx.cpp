#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include<string>
std::string ReadFile(std::string fileName)
{
	std::ifstream in{ fileName };
	if (!in) {
		std::cerr << "파일 읽기 실패" << std::endl;
		return std::string{};
	}
	std::string str{ std::istreambuf_iterator<char>{ in }, {} };
	return str;
}

GLuint CreateShaderProgram(std::string vertexFile, std::string fragmentFile)
{
	GLuint ShaderProgram = glCreateProgram(); //빈 쉐이더 프로그램 생성

	if (ShaderProgram == 0) { //쉐이더 프로그램이 만들어졌는지 확인
		std::cerr << "Error: shader program 생성 실패" << std::endl;
		return 0;
	}

	GLuint vertexShader = CompileShader(vertexFile, GL_VERTEX_SHADER);
	GLuint fragmentShader = CompileShader(fragmentFile, GL_FRAGMENT_SHADER);

	glAttachShader(ShaderProgram, vertexShader);	//--- 세이더 프로그램에 버텍스 세이더 붙이기
	glAttachShader(ShaderProgram, fragmentShader);	//--- 세이더 프로그램에 프래그먼트 세이더 붙이기
	glLinkProgram(ShaderProgram);					//--- 세이더 프로그램 링크하기
	glDeleteShader(vertexShader);					//--- 세이더 객체를 세이더 프로그램에 링크했음으로, 세이더 객체 자체는 삭제 가능
	glDeleteShader(fragmentShader);

	GLint result;
	//링크가 성공했는지 확인
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &result);
	if (!result) {
		GLchar InfoLog[1024];

		// shader program 로그를 받아옴
		glGetProgramInfoLog(ShaderProgram, 1024, nullptr, InfoLog);
		std::cerr << "Error: shader program 연결 실패\n" << InfoLog << std::endl;
	}
	else {
		std::cout << vertexFile << ", " << fragmentFile << " shader 컴파일 성공." << std::endl;
	}

	glUseProgram(ShaderProgram);		//--- 만들어진 세이더 프로그램 사용하기
	//--- 여러 개의 세이더프로그램 만들 수 있고, 그 중 한개의 프로그램을 사용하려면
	//--- glUseProgram 함수를 호출하여 사용 할 특정 프로그램을 지정한다.
	//--- 사용하기 직전에 호출할 수 있다.
	return ShaderProgram;
}

GLuint CompileShader(std::string fileName, GLenum shaderType)
{
	std::string typeName = shaderType == GL_VERTEX_SHADER ? "vertex shader" : shaderType == GL_FRAGMENT_SHADER ? "fragment shader" : "Error Type";

	//쉐이더 오브젝트 생성
	GLuint ShaderObj = glCreateShader(shaderType);

	if (ShaderObj == 0) {
		std::cerr << "Error: shader 생성 실패: type - " << typeName << std::endl;
	}

	// 파일을 읽는다.
	std::string shaderStrs = ReadFile(fileName);
	const char* shaderTexts[1]{ shaderStrs.c_str() };

	//쉐이더 코드를 쉐이더 오브젝트에 할당
	glShaderSource(ShaderObj, 1, shaderTexts, nullptr);

	//할당된 쉐이더 코드를 컴파일
	glCompileShader(ShaderObj);

	GLint result;
	// ShaderObj 가 성공적으로 컴파일 되었는지 확인
	glGetShaderiv(ShaderObj, GL_COMPILE_STATUS, &result);
	if (!result) {
		GLchar InfoLog[1024];

		//OpenGL 의 shader log 데이터를 가져옴
		glGetShaderInfoLog(ShaderObj, 1024, nullptr, InfoLog);
		std::cerr << "Error: shader 컴파일 실패: type - " << typeName << std::endl;
		std::cerr << InfoLog << std::endl;
		std::cout << shaderTexts[0] << std::endl;
	}

	return ShaderObj;
}

std::vector<glm::vec3> ReadObjWithRColorNormal(std::string fileName, glm::vec3 fixedColor)
{
	std::ifstream in{ fileName };
	if (!in) {
		std::cerr << fileName << " Open Failed." << std::endl;
		return {};
	}
	std::vector<glm::vec3> vertex;
	std::vector<glm::vec3> color;
	std::vector<glm::vec3> normal;
	std::vector<glm::ivec3> vindex;
	std::vector<glm::ivec3> cindex;
	std::vector<glm::ivec3> nindex;
	while (in) {
		std::string line;
		std::getline(in, line);
		std::stringstream ss{ line };
		std::string str;
		ss >> str;
		if (str == "v") {
			glm::vec3 v;
			for (int i = 0; i < 3; ++i) {
				std::string substr;
				ss >> substr;
				v[i] = std::stof(substr);
			}
			vertex.push_back(v);
			color.push_back(fixedColor);  // 랜덤 색상 대신 지정된 색상 사용

		}
		else if (str == "vn") {
			glm::vec3 n;
			for (int i = 0; i < 3; ++i) {
				std::string substr;
				ss >> substr;
				n[i] = std::stof(substr);
			}
			normal.push_back(n);
		}
		else if (str == "f") {
			glm::ivec3 fv;
			glm::ivec3 fn;
			for (int i = 0; i < 3; ++i) {
				std::string substr;
				ss >> substr;
				std::stringstream subss{ substr };
				std::string vIdx;
				std::getline(subss, vIdx, '/');
				fv[i] = std::stoi(vIdx) - 1;
				std::getline(subss, vIdx, '/');
				// 텍스처 건너뛰기
				std::getline(subss, vIdx, '/');
				fn[i] = std::stoi(vIdx) - 1;
			}
			vindex.push_back(fv);
			cindex.push_back(fv);
			nindex.push_back(fn);
		}
	}
	std::vector<glm::vec3> data;
	data.reserve(vindex.size() * 9);
	for (int i = 0; i < vindex.size(); ++i) {
		data.push_back(vertex[vindex[i][0]]);
		data.push_back(color[cindex[i][0]]);
		data.push_back(normal[nindex[i][0]]);
		data.push_back(vertex[vindex[i][1]]);
		data.push_back(color[cindex[i][1]]);
		data.push_back(normal[nindex[i][1]]);
		data.push_back(vertex[vindex[i][2]]);
		data.push_back(color[cindex[i][2]]);
		data.push_back(normal[nindex[i][2]]);
	}
	std::cout << fileName << " File Read, " << data.size() / 3 << " Vertices Exists." << std::endl;
	return data;
}


#include <iostream>
#include "Shader.h"

std::string ReadFile(const char* path) {
	std::string code;
	std::fstream fileStream(path, std::ios::in);

	if (!fileStream.is_open()) {
		std::cout << "File not found!" << std::endl;
	}

	std::string line;
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		code.append(line + "\n");
	}

	fileStream.close();
	return code;
}

Shader::Shader() {
	shaderId = uniformModel = uniformProjection = 0;
}

Shader::~Shader() {
	if (shaderId != 0)
		glDeleteProgram(shaderId);
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode) {
	Compile(vertexCode, fragmentCode);
}

void Shader::CreateFromFile(const char* vertexCodePath, const char* fragmentCodePath) {
	std::string vertexCode = ReadFile(vertexCodePath);
	std::string fragmentCode = ReadFile(fragmentCodePath);
	Compile(vertexCode.c_str(), fragmentCode.c_str());
}

void Shader::Compile(const char* vertexCode, const char* fragmentCode) {
	Shader::shaderId = glCreateProgram(); // Cria um programa
	GLuint _vShader = glCreateShader(GL_VERTEX_SHADER); // Cria um shader
	GLuint _fShader = glCreateShader(GL_FRAGMENT_SHADER); // Cria um shader

	// Gambiarra para converter char em GLchar
	const GLchar* vCode[1];
	const GLchar* fCode[1];

	vCode[0] = vertexCode; // Código do shader
	fCode[0] = fragmentCode; // Código do shader

	glShaderSource(_vShader, 1, vCode, NULL); // Associa o shader ao código
	glShaderSource(_fShader, 1, fCode, NULL); // Associa o shader ao código

	glCompileShader(_vShader); // Compila o shader
	glCompileShader(_fShader); // Compila o shader

	glAttachShader(Shader::shaderId, _vShader); // Adiciona o shader ao programa
	glAttachShader(Shader::shaderId, _fShader); // Adiciona o shader ao programa

	glLinkProgram(Shader::shaderId); // Adiciona ao programa

	Shader::uniformModel = glGetUniformLocation(shaderId, "model");
	Shader::uniformProjection = glGetUniformLocation(shaderId, "projection");

}

void Shader::UseProgram() {
	glUseProgram(shaderId);
}
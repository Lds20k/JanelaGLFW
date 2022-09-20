#pragma once
#include <GL/glew.h>

class Shader
{
public:
	Shader();
	~Shader();
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFile(const char* vertexCodePath, const char* fragmentCodePath);
	void UseProgram();
	GLuint getUniformModel() { return uniformModel; };
	GLuint getUniformProjection() { return uniformProjection; };
private:
	GLuint shaderId;
	GLuint uniformModel, uniformProjection;

	void Compile(const char* vertexCode, const char* fragmentCode);
};


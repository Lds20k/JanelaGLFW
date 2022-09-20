#pragma once
#include <stdint.h>
#include "GL/glew.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	void create_mash(GLfloat* vertices, uint64_t numOfVertices, GLuint* indices, uint64_t numOfIndices);
	void render_mash();
private:
	GLuint VAO, VBO, VBI;
	uint64_t numOfIndices;
};


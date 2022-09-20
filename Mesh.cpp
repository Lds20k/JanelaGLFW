#include "mesh.h"

Mesh::Mesh() {
	VAO = VBO = VBI = 0;
}

Mesh::~Mesh() {
	if (VBO != 0) glDeleteBuffers(1, &VBO);
	if (VBI != 0) glDeleteBuffers(1, &VBI);
	if (VAO != 0) glDeleteBuffers(1, &VAO);
}

void Mesh::create_mash(GLfloat* vertices, uint64_t numOfVertices, GLuint* indices, uint64_t numOfIndices) {
	Mesh::numOfIndices = numOfIndices;

	glGenVertexArrays(1, &VAO); // Cria o VAO
	glBindVertexArray(VAO); // Coloca o VAO em contexto
		glGenBuffers(1, &VBI); // Cria o VBI
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBI); // Coloca o VBI em contexto
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfIndices, indices, GL_STATIC_DRAW);
		glGenBuffers(1, &VBO); // Cria o VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO); // Coloca o VBO em contexto
			glBufferData(GL_ARRAY_BUFFER, numOfVertices, vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Explica os valores do vertex
			glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0); // Remove do contexto o VBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // Remove do contexto o VBI
	glBindVertexArray(0); // Remove do contexto o VAO
}

void Mesh::render_mash() {
	glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBI);
			glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
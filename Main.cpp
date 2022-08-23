#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

# define M_PI 3.1415

GLuint VAO, VBO, shaderPrograma;

// Vertex Array
static const char* vShader = "                 \n\
#version 330                                   \n\
                                               \n\
layout(location=0) in vec2 pos;                \n\
                                               \n\
void main(){                                   \n\
	gl_Position = vec4(pos.x, pos.y, 0.0, 1.0);\n\
}\n";

// Responsavel por mudar a cor
static const char* fShader = "                 \n\
#version 330                                   \n\
                                               \n\
out vec4 color;                                \n\
                                               \n\
void main(){                                   \n\
	color = vec4(1.0, 1.0, 1.0, 1.0);          \n\
}";

void criaTriangulo() {
	GLfloat vertex[] =
	{
		 0.0f,  1.0f,
		-1.0f, -1.0f,
		 1.0f, -1.0f
	};

	glGenVertexArrays(1, &VAO); // Cria o VAO
	glBindVertexArray(VAO); // Coloca o VAO em contexto
		glGenBuffers(1, &VBO); // Cria o VBO
		glBindBuffer(GL_ARRAY_BUFFER, VBO); // Coloca o VBO em contexto
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW); // 
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0); // Explica os valores do vertex
		glBindBuffer(GL_ARRAY_BUFFER, 0); // Remove do contexto o VBO
	glBindVertexArray(0); // Remove do contexto o VAO
}

void compilaShader() {
	shaderPrograma = glCreateProgram(); // Cria um programa
	GLuint _vShader = glCreateShader(GL_VERTEX_SHADER); // Cria um shader
	GLuint _fShader = glCreateShader(GL_FRAGMENT_SHADER); // Cria um shader

	// Gambiarra para converter char em GLchar
	const GLchar* vCode[1];
	const GLchar* fCode[1];

	vCode[0] = vShader; // Código do shader
	fCode[0] = fShader; // Código do shader

	glShaderSource(_vShader, 1, vCode, NULL); // Associa o shader ao código
	glShaderSource(_fShader, 1, fCode, NULL); // Associa o shader ao código

	glCompileShader(_vShader); // Compila o shader
	glCompileShader(_fShader); // Compila o shader

	glAttachShader(shaderPrograma, _vShader); // Adiciona o shader ao programa
	glAttachShader(shaderPrograma, _fShader); // Adiciona o shader ao programa

	glLinkProgram(shaderPrograma); // Adiciona ao programa
}

int main() {
	if (!glfwInit()) { 
		std::cout << "[GLFW] Nao foi possivel iniciar!";
		return 1; 
	}
	
	GLFWwindow* main_window = glfwCreateWindow(800, 400, "Ola Mundo!", NULL, NULL);
	if (main_window == NULL) {
		std::cout << "[GLFW] Não foi possivel criar janela!";
		glfwTerminate();
		return 1;
	}

	int buffer_width, buffer_height;
	glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height);
	glfwMakeContextCurrent(main_window);


	if (glewInit() != GLEW_OK) {
		std::cout << "[GLEW] Nao foi possivel iniciar!";
		glfwDestroyWindow(main_window);
		glfwTerminate();
		return 1;
	}

	glViewport(0, 0, buffer_width, buffer_height);

	criaTriangulo();
	compilaShader();

	while (!glfwWindowShouldClose(main_window)) {
		// Habilita os eventos
		glfwPollEvents();		
		
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Desenha o triangulo
		glUseProgram(shaderPrograma);
			glBindVertexArray(VAO);
				glDrawArrays(GL_TRIANGLES, 0, 3);
			glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(main_window);
	}

	glfwDestroyWindow(main_window);
	glfwTerminate();
	return 0;
}
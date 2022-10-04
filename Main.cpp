#include <iostream>
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

std::vector<Mesh*> mesh_list;
std::vector<Shader*> list_shader;

Window* window;

// Vertex Array
static const char* vShaderPath = "vertex.glsl";

// Responsavel por mudar a cor
static const char* fShaderPath = "fragment.glsl";


void CriarShader() {
	Shader* shader = new Shader();
	shader->CreateFromFile(vShaderPath, fShaderPath);
	list_shader.push_back(shader);
}


void criaPiramide() {
	GLfloat vertex[] =
	{
		 0.0f,  1.0f,  0.0f, // Vertice 0 (Verde)
		-1.0f, -1.0f,  0.0f, // Vertice 1 (Preto)
		 1.0f, -1.0f,  0.0f, // Vertice 2 (Vermelho)
		 0.0f, -1.0f,  1.0f  // Vertice 3 (Azul)
	};

	GLfloat vertex2[] =
	{
		 0.0f,  1.0f,  0.0f, // Vertice 0 (Verde)
		-1.0f, -1.0f,  0.0f, // Vertice 1 (Preto)
		 1.0f, -1.0f,  0.0f, // Vertice 2 (Vermelho)
		 0.0f, -1.0f,  -1.0f  // Vertice 3 (Azul)
	};

	GLuint indice[] = {
		0, 1, 3,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	Mesh* obj1 = new Mesh();
	obj1->create_mash(vertex, sizeof(vertex), indice, sizeof(indice));
	mesh_list.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->create_mash(vertex2, sizeof(vertex), indice, sizeof(indice));
	mesh_list.push_back(obj2);
}


int main() {
	window = new Window();
	criaPiramide();
	CriarShader();
	float trianguloOffset = 0.0f, maxOffset = 0.7f, minOffset = -0.7f, incOffset = 0.0f;
	bool diretion = true;

	float rotationOffset = 0.0f, maxRotation = 360.0f, minRotation = 0.0f, incRotation = 0.5f;
	bool rotation = true;

	float scaleOffset = 0.4f, maxScale = 0.7f, minScale = 0.4f, incScale = 0.0f;
	bool scale = true;

	float z = 0;
	float x = 0;
	while (!window->ShouldClose()) {
		// Habilita os eventos
		glfwPollEvents();		
		
		// Limpa a tela
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*int state_w = glfwGetKey(window, GLFW_KEY_W);
		if (state_w == GLFW_PRESS){
			z += 0.01;
		}

		int state_s = glfwGetKey(main_window, GLFW_KEY_S);
		if (state_s == GLFW_PRESS){
			z -= 0.01;
		}

		int state_a = glfwGetKey(main_window, GLFW_KEY_A);
		if (state_a == GLFW_PRESS) {
			x += 0.01;
		}

		int state_d = glfwGetKey(main_window, GLFW_KEY_D);
		if (state_d == GLFW_PRESS) {
			x -= 0.01;
		}*/



		// Coloca o programa na memoria
		Shader* shader = list_shader[0];
		shader->UseProgram();
			// Mover o triangulo
			trianguloOffset += diretion ? incOffset : incOffset * -1;
			if (trianguloOffset >= maxOffset || trianguloOffset <= minOffset)
				diretion = !diretion;
			// Rotação do triangulo
			rotationOffset += rotation ? incRotation : incRotation * -1;
			/*if (rotationOffset >= maxRotation || rotationOffset <= minRotation)
				rotation = !rotation;*/
			// Escala do triangulo
			scaleOffset += scale ? incScale : incScale * -1;
			if (scaleOffset >= maxScale || scaleOffset <= minScale)
				scale = !scale;
			
			// Triangulo 1
			// Renderiza a lista de mash
			mesh_list[0]->render_mash();
			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 2.0f, -5.0f));
			model = glm::rotate(model, glm::radians(rotationOffset), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(scaleOffset, scaleOffset, scaleOffset));

			glUniformMatrix4fv(shader->getUniformModel(), 1, GL_FALSE, glm::value_ptr(model));

			// Triangulo 2
			// Renderiza a lista de mash
			mesh_list[1]->render_mash();
			// Cria a matrix com 4 posições com valor 1.0f
			model = glm::mat4(1.0f);
			model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));
			model = glm::rotate(model, glm::radians(rotationOffset), glm::vec3(0.0f, 1.0f, 0.0f));
			model = glm::scale(model, glm::vec3(scaleOffset, scaleOffset, scaleOffset));

			glUniformMatrix4fv(shader->getUniformModel(), 1, GL_FALSE, glm::value_ptr(model));

			// Projeção de perspectiva 3D
			glm::mat4 projection = glm::perspective(1.0f, window->GetBufferWidth() / window->GetBufferHeight(), 0.1f, 100.0f);
			projection = glm::translate(projection, glm::vec3(x, 0.0f, z));
			glUniformMatrix4fv(shader->getUniformProjection(), 1, GL_FALSE, glm::value_ptr(projection));
		glUseProgram(0);

		window->SwapBuffer();
	}

	window->~Window();
	glfwTerminate();
	return 0;
}
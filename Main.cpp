#include <iostream>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

# define M_PI 3.1415

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


	int x = 0;
	int y = 0;
	float p1x = 0;
	float p1y = 0;

	float hip = 10;
	float angle = 0;
	while (!glfwWindowShouldClose(main_window)) {
		// Habilita os eventos
		glfwPollEvents();		
		
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		glEnableClientState(GL_VERTEX_ARRAY);

		float radians = angle * (M_PI / 180);
		x += cos(radians) * hip;
		y += sin(radians) * hip;

		float line_vertex[] =
		{
			p1x, p1y, x, y
		};

		glVertexPointer(2, GL_FLOAT, 0, line_vertex);

		glDrawArrays(GL_LINES, 0, 2);
		glfwSwapBuffers(main_window);

		angle++;
	}

	glfwDestroyWindow(main_window);
	glfwTerminate();
	return 0;
}
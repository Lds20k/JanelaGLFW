#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

class Window
{
public:
	Window();
	Window(GLint width, GLint height);
	~Window();
	bool ShouldClose() { return glfwWindowShouldClose(window); }
	GLfloat GetBufferWidth() { return (GLfloat)buffer_width; }
	GLfloat GetBufferHeight() { return (GLfloat)buffer_height; }
	void SwapBuffer() { glfwSwapBuffers(window); }
	bool Initialize();
private:
	GLFWwindow* window;
	GLint width, height;
	int buffer_width, buffer_height;

	// Callbacks
	void CreateCallBacks();

	// Teclas
	bool keys[1024];
	static void handleKeys(GLFWwindow* window,int key, int code, int action, int mode);
};

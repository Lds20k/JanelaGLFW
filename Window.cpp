#include "Window.h"

Window::Window(){
	this->width = 800;
	this->height = 400;
	Initialize();
}

Window::Window(GLint width, GLint height) {
	this->width = width;
	this->height = height;
	Initialize();
}

Window::~Window() {
	glfwDestroyWindow(window);
}

bool Window::Initialize() {
	memset(keys, false, 1024);

	if (!glfwInit()) {
		std::cout << "[GLFW] Nao foi possivel iniciar!" << std::endl;
		return false;
	}

	window = glfwCreateWindow(400, 400, "Ola Mundo!", NULL, NULL);
	if (window == NULL) {
		std::cout << "[GLFW] Não foi possivel criar janela!" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwGetFramebufferSize(window, &buffer_width, &buffer_height);
	glfwMakeContextCurrent(window);


	if (glewInit() != GLEW_OK) {
		std::cout << "[GLEW] Nao foi possivel iniciar!" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return false;
	}

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, buffer_width, buffer_height);
	glfwSetWindowUserPointer(window, this);
	CreateCallBacks();

	return true;
}

void Window::CreateCallBacks() {
	glfwSetKeyCallback(window, handleKeys);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode) {
	Window* window_p = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
		std::cout << "ESC" << std::endl;
	}

	if (key >= 0 && key <= 1024){
		if (action == GLFW_PRESS) {
			window_p->keys[key] = true;
			std::cout << "Key: " << key << std::endl;
		}
		else if (action == GLFW_RELEASE) {
			window_p->keys[key] = true;
			std::cout << "Key exit: " << key << std::endl;
		}
	}

}
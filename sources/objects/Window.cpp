#include "scop.hpp"

Window::Window(): ptr(NULL), width(0), height(0) {}

Window::~Window() {
	glfwDestroyWindow(this->ptr);
	glfwTerminate();
}

Window::Window(std::string title, const unsigned int width, const unsigned int height): width(width), height(height) {
	this->ptr = NULL;
	if (!glfwInit()) {
		std::cerr << "[\e[31mERROR\e[39m] GLFW cannot be initialized !" << std::endl;
		exit(1);
	}

	this->ptr = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!this->getWindow()) {
		std::cerr << "[\e[31mERROR\e[39m] Window creation failed !" << std::endl;
		exit(1);
	}
	glfwMakeContextCurrent(this->getWindow());

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "[\e[31mERROR\e[39m] GLEW cannot be initialized !" << std::endl;
		exit(1);
	}
}

Window::Window(const Window &window) {
	*this = window;
}

Window &Window::operator=(const Window &window) {
	this->ptr = window.ptr;
	this->width = window.width;
	this->height = window.height;
	return (*this);
}

GLFWwindow* Window::getWindow() const {
	return (this->ptr);
}

void Window::draw(Program *program) const {
	(void) program;
	while (!glfwWindowShouldClose(this->getWindow())) {
	}
}

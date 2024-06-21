#include "Window.hpp"
#include<unistd.h>

Window::Window(): ptr(NULL), width(0), height(0) {}

Window::~Window()
{
	glfwDestroyWindow(this->ptr);
	glfwTerminate();
}

Window::Window(const std::string path, const unsigned int width, const unsigned int height): width(width), height(height)
{
	this->ptr = NULL;
	if (!glfwInit()) {
		std::cerr << "[\e[31mERROR\e[39m] GLFW cannot be initialized !" << std::endl;
		return;
	}
	this->ptr = glfwCreateWindow(width, height, path.c_str(), NULL, NULL);
	if (!this->getWindow()) {
		std::cerr << "[\e[31mERROR\e[39m] Window creation failed !" << std::endl;
		return;
	}
	glfwMakeContextCurrent(this->getWindow());
	while (!glfwWindowShouldClose(this->getWindow())) {
		glClear(GL_COLOR_BUFFER_BIT);

		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glPointSize(5);

		glBegin(GL_POINTS);
		glColor3f (0.0f, 1.0f, 0.0f);
		glVertex3f (-0.5, -0.5, 0.5);
		glVertex3f (0.5, -0.5, 0.5);
		glVertex3f (-0.5, 0.5, 0.5);
		glVertex3f (0.5, 0.5, 0.5);
		glVertex3f (-0.5, 0.5, -0.5);
		glVertex3f (0.5, 0.5, -0.5);
		glVertex3f (-0.5, -0.5, -0.5);
		glVertex3f (0.5, -0.5, -0.5);
		glEnd();

		sleep(120);

		glfwSwapBuffers(this->getWindow());
		glfwPollEvents();
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

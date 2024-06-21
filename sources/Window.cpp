#include "Window.hpp"

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

	std::string title;
    size_t lastSlashPos = path.find_last_of('/');
    if (lastSlashPos == std::string::npos) {
        title = path;
    } else {
    	size_t dotPos = path.find_last_of('.');
		if (dotPos == std::string::npos) {
			std::cerr << "[\e[31mERROR\e[39m] File OBJ error !" << std::endl;
        	return;
   		}
		title = path.substr(lastSlashPos + 1, dotPos - lastSlashPos - 1);
	}

	this->ptr = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!this->getWindow()) {
		std::cerr << "[\e[31mERROR\e[39m] Window creation failed !" << std::endl;
		return;
	}
	glfwMakeContextCurrent(this->getWindow());
	while (!glfwWindowShouldClose(this->getWindow())) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glPointSize(2);
		glBegin(GL_POINTS);
		glColor3f (1.0f, 1.0f, 1.0f);
		glVertex3f (-0.5, -0.5, 0.5);
		glVertex3f (0.5, -0.5, 0.5);
		glVertex3f (-0.5, 0.5, 0.5);
		glVertex3f (0.5, 0.5, 0.5);
		glVertex3f (-0.5, 0.5, -0.5);
		glVertex3f (0.5, 0.5, -0.5);
		glVertex3f (-0.5, -0.5, -0.5);
		glVertex3f (0.5, -0.5, -0.5);
		glEnd();
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

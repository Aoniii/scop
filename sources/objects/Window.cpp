#include "scop.hpp"

Window::Window(): ptr(NULL), camera(NULL), width(0), height(0) {}

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

	this->camera = new Camera();
	glfwMakeContextCurrent(this->getWindow());

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cerr << "[\e[31mERROR\e[39m] GLEW cannot be initialized !" << std::endl;
		exit(1);
	}

	callback();
}

Window::Window(const Window &window) {
	*this = window;
}

Window &Window::operator=(const Window &window) {
	this->ptr = window.ptr;
	this->camera = window.camera;
	this->width = window.width;
	this->height = window.height;
	return (*this);
}

GLFWwindow* Window::getWindow() const {
	return (this->ptr);
}

Camera* Window::getCamera() {
	return (this->camera);
}

void Window::draw(Program *program) const {
	this->camera->initCoord(program->getObjects());

	while (!glfwWindowShouldClose(this->getWindow())) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

		glm::mat4 view = this->camera->getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)this->width / (float)this->height, 0.1f, 1000.0f);
		glm::mat4 model = glm::mat4(1.0f);
		glm::vec3 center = program->calculateCenter();

		model = glm::translate(model, center);
		model = glm::rotate(model, glm::radians(this->camera->getAngleX()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->camera->getAngleY()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->camera->getAngleZ()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, -center);
		
		glm::mat4 mvp = projection * view * model;

		glMatrixMode(GL_MODELVIEW);
    	glLoadMatrixf(&mvp[0][0]);

		//drawPoint(program);
		//drawLine(program);
		drawTriangle(program);

		glfwSwapBuffers(this->getWindow());
		glfwPollEvents();
	}
}

void Window::callback() {
	glfwSetWindowUserPointer(this->ptr, this);
	glfwSetKeyCallback(this->ptr, [](GLFWwindow* window, int key, int scancode, int action, int mods){
		(void) window;
		(void) scancode;
		(void) mods;

		Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
		if (!win)
			return;

		if (action == GLFW_PRESS || action == GLFW_REPEAT) {
			switch (key) {
				case GLFW_KEY_W:
					win->camera->addAngleZ(1.0f);
					break;
				case GLFW_KEY_S:
					win->camera->addAngleZ(-1.0f);
					break;
				case GLFW_KEY_D:
					win->camera->addAngleY(1.0f);
					break;
				case GLFW_KEY_A:
					win->camera->addAngleY(-1.0f);
					break;
				case GLFW_KEY_E:
					win->camera->addAngleX(1.0f);
					break;
				case GLFW_KEY_Q:
					win->camera->addAngleX(-1.0f);
					break;
			}
		}
	});
}

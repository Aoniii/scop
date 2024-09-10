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
	Shader *shader = new Shader();

	while (!glfwWindowShouldClose(this->getWindow())) {
		if (this->camera->getReset()) {
			this->camera->setYaw(180.0f);
			this->camera->setPitch(0.0f);
			this->camera->setAngleX(0.0f);
			this->camera->setAngleY(0.0f);
			this->camera->setAngleZ(0.0f);
			this->camera->initCoord(program->getObjects());
			this->camera->setReset(0.0f);
			this->camera->setRotate(false);
			this->camera->setType(4);
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glEnable(GL_DEPTH_TEST);

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

		if (this->camera->getType() == 1) {
			shader->disable();
			drawPoint(program);
		} else if (this->camera->getType() == 2) {
			shader->disable();
			drawLine(program);
		} else if (this->camera->getType() == 3) {
			shader->disable();
			for (Object* objects : program->getObjects())
				objects->draw();
		} else if (this->camera->getType() == 4) {
			shader->use();
			shader->setMat4("model", model);
			shader->setMat4("view", view);
			shader->setMat4("projection", projection);
			shader->setVec3("viewPos", this->camera->getPos());
			shader->setVec3("lightPos", this->camera->getPos());
			for (Object* objects : program->getObjects())
				objects->drawWithMaterial(program, shader);
		} else if (this->camera->getType() == 5) {
			shader->disable();
			for (Object* objects : program->getObjects())
				objects->drawRGB();
		}

		if (this->camera->getRotate())
			this->camera->addAngleY(0.25f);

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
				case GLFW_KEY_Z:
					win->camera->addYaw(-5.0f);
					break;
				case GLFW_KEY_X:
					win->camera->addYaw(5.0f);
					break;
				case GLFW_KEY_C:
					win->camera->addPitch(-5.0f);
					break;
				case GLFW_KEY_V:
					win->camera->addPitch(5.0f);
					break;
				case GLFW_KEY_T:
					win->camera->addPos(win->camera->getFront());
					break;
				case GLFW_KEY_G:
					win->camera->addPos(-(win->camera->getFront()));
					break;
				case GLFW_KEY_H:
					win->camera->addPos(win->camera->getRight());
					break;
				case GLFW_KEY_F:
					win->camera->addPos(-(win->camera->getRight()));
					break;
				case GLFW_KEY_R:
					win->camera->addPos(win->camera->getUp());
					break;
				case GLFW_KEY_Y:
					win->camera->addPos(-(win->camera->getUp()));
					break;
				case GLFW_KEY_B:
					win->camera->setReset(true);
					break;
				case GLFW_KEY_N:
					win->camera->toggleRotate();
					break;
				case GLFW_KEY_1:
					win->camera->setType(1);
					break;
				case GLFW_KEY_2:
					win->camera->setType(2);
					break;
				case GLFW_KEY_3:
					win->camera->setType(3);
					break;
				case GLFW_KEY_4:
					win->camera->setType(4);
					break;
				case GLFW_KEY_5:
					win->camera->setType(5);
					break;
			}
		}
	});
}

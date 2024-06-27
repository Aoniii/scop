#include "scop.hpp"

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
	callback();
}

Window::Window(const Window &window) {
	*this = window;
}

Window &Window::operator=(const Window &window) {
	this->ptr = window.ptr;
	this->width = window.width;
	this->height = window.height;
	this->camera = window.camera;
	return (*this);
}

GLFWwindow* Window::getWindow() const {
	return (this->ptr);
}

void Window::draw(std::vector<OBJModel*> &models, std::map<std::string, Material*> &materials) const {
	(void) materials;
	this->camera->initCoord(models);
	while (!glfwWindowShouldClose(this->getWindow())) {
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glPointSize(2);

		glm::mat4 view = this->camera->getView();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
		glm::mat4 model = glm::mat4(1.0f);

		glm::vec3 center(0.0f);
		if (!models.empty() && !models[0]->vertices.empty())
			center = calculateCenter(models[0]->vertices);

		model = glm::translate(model, center);
		model = glm::rotate(model, glm::radians(this->camera->getAngleX()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->camera->getAngleY()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->camera->getAngleZ()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, -center);
		glm::mat4 mvp = projection * view * model;

		glBegin(GL_POINTS);
		glColor3f (1.0f, 1.0f, 1.0f);

		for (OBJModel* obj : models) {
			for (Vertex vertex : obj->vertices) {
				glm::vec4 pos = glm::vec4(vertex.x, vertex.y, vertex.z, vertex.w);
				pos = mvp * pos;
				glVertex4f(pos.x, pos.y, pos.z, pos.w);
			}
		}

		glEnd();
		glfwSwapBuffers(this->getWindow());
		glfwPollEvents();
	}
}

void Window::callback() {
	glfwSetWindowUserPointer(this->ptr, this);
	glfwSetKeyCallback(this->ptr,
		[](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			(void) window;
			(void) scancode;
			(void) mods;
			Window* win = static_cast<Window*>(glfwGetWindowUserPointer(window));
			if (!win)
				return;
			if (action == GLFW_PRESS || action == GLFW_REPEAT) {
				switch (key) {
					case GLFW_KEY_W:
						win->camera->addAngleX(-ANGLE);
						break;
					case GLFW_KEY_S:
						win->camera->addAngleX(ANGLE);
						break;
					case GLFW_KEY_A:
						win->camera->addAngleY(-ANGLE);
						break;
					case GLFW_KEY_D:
						win->camera->addAngleY(ANGLE);
						break;
					case GLFW_KEY_Q:
						win->camera->addAngleZ(-ANGLE);
						break;
					case GLFW_KEY_E:
						win->camera->addAngleZ(ANGLE);
						break;
				}
	   		}
		}
	);
}

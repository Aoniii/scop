#include "scop.hpp"

Window::Window(): ptr(NULL), camera(NULL), width(0), height(0) {}

Window::~Window() {
	ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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
	glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    //ImGuiIO& io = ImGui::GetIO();
    
    ImGui_ImplGlfw_InitForOpenGL(this->getWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 130");

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

void Window::draw(Program *program) {
	this->camera->initCoord(program->getObjects());
	Shader *shader = new Shader();
	glm::vec3 center = program->calculateCenter();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, program->getTexture());
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

		updateFPS();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glEnable(GL_DEPTH_TEST);

		glm::mat4 view = this->camera->getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)this->width / (float)this->height, 0.1f, 1000.0f);
		glm::mat4 model = glm::mat4(1.0f);

		model = glm::translate(model, center);
		model = glm::rotate(model, glm::radians(this->camera->getAngleX()), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->camera->getAngleY()), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(this->camera->getAngleZ()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::translate(model, -center);
		
		glm::mat4 mvp = projection * view * model;

		glMatrixMode(GL_MODELVIEW);
		glLoadMatrixf(&mvp[0][0]);

		if (this->camera->getType() == 4 || this->camera->getType() == 6) {
			shader->use();
			shader->setMat4("model", model);
			shader->setMat4("view", view);
			shader->setMat4("projection", projection);
			shader->setVec3("viewPos", this->camera->getPos());
			shader->setVec3("lightPos", this->camera->getPos());
			shader->setInt("texture1", 0);
		} else
			shader->disable();

		if (this->camera->getType() == 1) {
			drawPoint(program);
		} else if (this->camera->getType() == 2) {
			drawLine(program);
		} else if (this->camera->getType() == 3) {
			for (Object* objects : program->getObjects())
				objects->draw();
		} else if (this->camera->getType() == 4) {
			shader->setBool("isTexture", false);
			for (Object* objects : program->getObjects())
				objects->drawWithMaterial(program, shader);
		} else if (this->camera->getType() == 5) {
			for (Object* objects : program->getObjects())
				objects->drawGreyMode();
		} else if (this->camera->getType() == 6) {
			shader->setBool("isTexture", true);
			for (Object* objects : program->getObjects())
				objects->draw();
		}

		if (this->camera->getRotate())
			this->camera->addAngleY(0.25f);

		glfwPollEvents();
		imgui(program);
		glfwSwapBuffers(this->getWindow());
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
				case GLFW_KEY_6:
					win->camera->setType(6);
					break;
			}
		}
	});
}

void Window::imgui(Program *program) {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::SetNextWindowPos(ImVec2(540, 10), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(250, 135), ImGuiCond_Once);
	ImGui::SetNextWindowCollapsed(true, ImGuiCond_Once);
	ImGui::Begin("Binds", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
	ImGui::Text("1 2 3 4 5 6: Display type");
	ImGui::Text("Q W E A S D: Rotate objects");
	ImGui::Text("R T Y F G H: Move camera");
	ImGui::Text("Z X C V: Orient view");
	ImGui::Text("B: Reset");
	ImGui::Text("N: Automatic rotation");
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(540, 655), ImGuiCond_Once);
	ImGui::SetNextWindowSize(ImVec2(250, 135), ImGuiCond_Once);
	ImGui::Begin("Informations", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
	ImGui::Text("FPS: %.1f", this->fps);
	ImGui::Text("Vertex: %li", program->vertexSize());
	ImGui::Text("Faces: %li", program->faceSize());
	ImGui::Text("Camera: X:%.1f, Y:%.1f, Z:%.1f", this->camera->getPos().x, this->camera->getPos().y, this->camera->getPos().z);
	ImGui::Text("Yaw: %.f", this->camera->getYaw());
	ImGui::Text("Pitch: %.f", this->camera->getPitch());
	ImGui::End();

	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(this->getWindow(), &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Window::updateFPS() {
	double currentTime = glfwGetTime();
	double deltaTime = currentTime - lastTime;
	fps = 1.0f / deltaTime;
	lastTime = currentTime;
}

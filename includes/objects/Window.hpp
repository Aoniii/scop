#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
#include <string>

class Program;

class Camera;

class Window {
	private:
		GLFWwindow *ptr;
		Camera *camera;
		unsigned int width;
		unsigned int height;
		double lastTime = 0.0;
		float fps = 0.0f;

	public:
		Window();
		~Window();
		Window(std::string title, const unsigned int width, const unsigned int height);
		Window(const Window &window);
		Window &operator=(const Window &window);

		GLFWwindow*	getWindow() const;
		Camera* getCamera();
		unsigned int getWidth() const;
		unsigned int getHeight() const;

		void draw(Program *program);
		void callback();
		void imgui(Program *program);
		void updateFPS();
};

#endif

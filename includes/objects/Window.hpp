#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
#include <string>

class Program;

class Window {
	private:
		GLFWwindow *ptr;
		unsigned int width;
		unsigned int height;

	public:
		Window();
		~Window();
		Window(std::string title, const unsigned int width, const unsigned int height);
		Window(const Window &window);
		Window &operator=(const Window &window);

		GLFWwindow*	getWindow() const;

		void draw(Program *program) const;
};

#endif

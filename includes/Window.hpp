#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
#include <string>

class Window {
	private:
		GLFWwindow*		ptr;
		unsigned int	width;
		unsigned int	height;
	public:
		Window();
		~Window();
		Window(const char *title, const unsigned int width, const unsigned int height);
		Window(const Window &window);
		Window &operator=(const Window &window);

		GLFWwindow*	getWindow() const;
};

#endif

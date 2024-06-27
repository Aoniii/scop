#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include <map>
#include <GLFW/glfw3.h>
#include "Camera.hpp"

struct Material;

struct OBJModel;

class Window {
	private:
		GLFWwindow* ptr;
		unsigned int width;
		unsigned int height;
		Camera* camera = new Camera();

	public:
		Window();
		~Window();
		Window(const std::string path, const unsigned int width, const unsigned int height);
		Window(const Window &window);
		Window &operator=(const Window &window);

		GLFWwindow*	getWindow() const;
		void draw(std::vector<OBJModel*> &models, std::map<std::string, Material*> &materials) const;
		void callback();
};

#endif

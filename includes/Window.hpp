#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <vector>
#include <map>
#include <GLFW/glfw3.h>
#include "Camera.hpp"
#include "Shader.hpp"

struct Material;

struct OBJModel;

class Window {
	private:
		GLFWwindow* ptr;
		unsigned int width;
		unsigned int height;
		unsigned int type = 2;
		Camera* camera = new Camera();
		Shader* shader = NULL;

	public:
		Window();
		~Window();
		Window(const std::string path, const unsigned int width, const unsigned int height);
		Window(const Window &window);
		Window &operator=(const Window &window);

		GLFWwindow*	getWindow() const;
		void draw(const std::vector<OBJModel*> &models, const std::map<std::string, Material*> &materials) const;
		void callback();

		void setType(float f);
};

#endif

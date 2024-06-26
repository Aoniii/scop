#include "scop.hpp"

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "[\e[31mERROR\e[39m] Usage: ./scop <file>" << std::endl;
		return (1);
	}

	std::string filename(av[1]);
	if (!extensionChecker(filename, ".obj")) {
		std::cerr << "[\e[31mERROR\e[39m] The specified file isn't an file.obj" << std::endl;
		return (1);
	}

	std::vector<OBJModel*> models;
	std::map<std::string, Material*> materials;
	if (parseOBJ(filename, models, materials) < 0) {
		clean(models, materials);
		return (1);
	}

	Window* window = new Window(filename, 800, 800);
	if (!window->getWindow()) {
		clean(models, materials);
		delete window;
		return (1);
	}

	window->draw(models, materials);
	clean(models, materials);
	delete window;
	return (0);
}

#include "scop.hpp"

int main(int ac, char** av) {
	if (!(ac == 2 || (ac == 3 && std::string(av[2]) == "PARSING"))) {
		std::cerr << "[\e[31mERROR\e[39m] Usage: ./scop <file>" << std::endl;
		return (1);
	}

	std::string filename(av[1]);
	if (filename.length() < 5 || filename.substr(filename.length() - 4) != ".obj") {
		std::cerr << "[\e[31mERROR\e[39m] Invalid object file." << std::endl;
		return (1);
	}

	Program *program = parse(filename);
	if (ac == 3 && std::string(av[2]) == "PARSING") {
		parsingChecker(program);
		return (0);
	}

	program->setWindow(new Window(program->getName(), 800, 800));
	program->loadTexture("./ressources/chaton.bmp");
	for (Object* objects : program->getObjects()) objects->setupBuffers();
	program->getWindow()->draw(program);
	for (Object* objects : program->getObjects()) objects->clearBuffers();

	return (0);
}

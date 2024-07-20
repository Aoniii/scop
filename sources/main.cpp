#include "scop.hpp"

int main(int ac, char** av) {
	if (ac != 2) {
		std::cerr << "[\e[31mERROR\e[39m] Usage: ./scop <file>" << std::endl;
		return (1);
	}

	std::string filename(av[1]);
	if (filename.length() < 5 || filename.substr(filename.length() - 4) != ".obj") {
		std::cerr << "[\e[31mERROR\e[39m] Invalid object file." << std::endl;
		return (1);
	}

	return (0);
}

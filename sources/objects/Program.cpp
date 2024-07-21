#include "Program.hpp"

Program::Program(): objects(), materials() {}

Program::~Program() {}

Program::Program(const Program &program) {
	*this = program;
}

Program &Program::operator=(const Program &program) {
	this->objects = program.objects;
	this->materials = program.materials;
	return (*this);
}

std::vector<Object> Program::getObjects() const {
	return (this->objects);
}

std::vector<Material> Program::getMaterials() const {
	return (this->materials);
}

void Program::setObjects(std::vector<Object> objects) {
	this->objects = objects;
}

void Program::setMaterials(std::vector<Material> materials) {
	this->materials = materials;
}

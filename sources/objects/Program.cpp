#include "Program.hpp"

Program::Program(): name(""), objects(), materials() {}

Program::~Program() {}

Program::Program(const Program &program) {
	*this = program;
}

Program &Program::operator=(const Program &program) {
	this->name = program.name;
	this->objects = program.objects;
	this->materials = program.materials;
	return (*this);
}

std::string Program::getName() const {
	return (this->name);
}

std::vector<Object*> Program::getObjects() const {
	return (this->objects);
}

std::vector<Material*> Program::getMaterials() const {
	return (this->materials);
}

void Program::setName(std::string name) {
	this->name = name;
}

void Program::setObjects(std::vector<Object*> objects) {
	this->objects = objects;
}

void Program::setMaterials(std::vector<Material*> materials) {
	this->materials = materials;
}

void Program::setFile(std::string filename) {
	int i = filename.find_last_of('/');
	this->name = filename.substr(i + 1, filename.find_last_of('.') - i - 1);
}

void Program::addObject(Object *object) {
	this->objects.push_back(object);
}

void Program::addMaterial(Material *material) {
	this->materials.push_back(material);
}

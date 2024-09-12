#include "scop.hpp"

Program::Program(): name(""), objects(), materials(), window(NULL) {
	this->blank = new Material();
	this->blank->setName("blank");
	this->blank->setKa({1.0f, 1.0f, 1.0f});
	this->blank->setKd({1.0f, 1.0f, 1.0f});
	this->blank->setKs({1.0f, 1.0f, 1.0f});
	this->blank->setNs(0);
	this->blank->setD(0);
	this->blank->setNi(0);
	this->blank->setIllum(0);
}

Program::~Program() {}

Program::Program(const Program &program) {
	*this = program;
}

Program &Program::operator=(const Program &program) {
	this->name = program.name;
	this->objects = program.objects;
	this->materials = program.materials;
	this->window = program.window;
	this->texture = program.texture;
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

Window *Program::getWindow() const {
	return(this->window);
}

Material *Program::getMaterial(std::string name) const {
	for (Material *mat : this->materials) {
		if (mat->getName() == name)
			return (mat);
	}
	return (NULL);
}

Material *Program::getBlank() const {
	return (this->blank);
}

unsigned int Program::getTexture() const {
	return (this->texture);
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

void Program::setWindow(Window *window) {
	this->window = window;
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

void Program::loadTexture(const char* path) {
	this->texture = createTextureFromBMP(path);
}

glm::vec3 Program::calculateCenter() const {
	glm::vec3 center(0.0f);
	float f = 0;

	for (Object *objects : this->objects) {
		for (Vertex vertex : objects->getVertices()) {
			center += glm::vec3(vertex.getX(), vertex.getY(), vertex.getZ());
			f++;
		}
	}
	center /= f;

	return (center);
}

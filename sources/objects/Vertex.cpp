#include "Vertex.hpp"

Vertex::Vertex(): x(0.0f), y(0.0f), z(0.0f), w(0.0f) {}

Vertex::~Vertex() {}

Vertex::Vertex(const Vertex &vertex) {
	*this = vertex;
}

Vertex &Vertex::operator=(const Vertex &vertex) {
	this->x = vertex.x;
	this->y = vertex.y;
	this->z = vertex.z;
	this->w = vertex.w;
	return (*this);
}

Vertex::Vertex(float x, float y, float z): x(x), y(y), z(z), w(1.0f) {}

Vertex::Vertex(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}

float Vertex::getX() const {
	return (this->x);
}

float Vertex::getY() const {
	return (this->y);
}

float Vertex::getZ() const {
	return (this->z);
}

float Vertex::getW() const {
	return (this->w);
}

void Vertex::setX(float x) {
	this->x = x;
}

void Vertex::setY(float y) {
	this->y = y;
}

void Vertex::setZ(float z) {
	this->z = z;
}

void Vertex::setW(float w) {
	this->w = w;
}

glm::vec3 Vertex::getPos() const {
	return (glm::vec3(x, y, z));
}

#include "Object.hpp"

Object::Object(): name(""), vertices(), textures(), normals(), faces() {}

Object::~Object() {}

Object::Object(const Object &object) {
	*this = object;
}
Object &Object::operator=(const Object &object) {
	this->name = object.name;
	this->vertices = object.vertices;
	this->textures = object.textures;
	this->normals = object.normals;
	this->faces = object.faces;
	return (*this);
}

std::string Object::getName() const {
	return (this->name);
}

std::vector<Vertex> Object::getVertices() const {
	return (this->vertices);
}

std::vector<TextureCoord> Object::getTextures() const {
	return (this->textures);
}

std::vector<Normal> Object::getNormals() const {
	return (this->normals);
}

std::vector<Face> Object::getFaces() const {
	return (this->faces);
}

void Object::setName(std::string name) {
	this->name = name;
}

void Object::setVertices(std::vector<Vertex> vertices) {
	this->vertices = vertices;
}

void Object::setTextures(std::vector<TextureCoord> textures) {
	this->textures = textures;
}

void Object::setNormals(std::vector<Normal> normals) {
	this->normals = normals;
}

void Object::setFaces(std::vector<Face> faces) {
	this->faces = faces;
}

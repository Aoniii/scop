#include "Face.hpp"

Face::Face(): vertexIndices(), textureIndices(), normalIndices(), materialName(""), smoothing(false) {}

Face::~Face() {}

Face::Face(const Face &face) {
	*this = face;
}

Face &Face::operator=(const Face &face) {
	this->vertexIndices = face.vertexIndices;
	this->textureIndices = face.textureIndices;
	this->normalIndices = face.normalIndices;
	this->materialName = face.materialName;
	this->smoothing = face.smoothing;
	return (*this);
}

Face::Face(std::vector<int> vertexIndices, std::vector<int> textureIndices, std::vector<int> normalIndices, std::string materialName, bool smoothing):
	vertexIndices(vertexIndices), textureIndices(textureIndices), normalIndices(normalIndices), materialName(materialName), smoothing(smoothing) {}

std::vector<int> Face::getVertexIndices() const {
	return (this->vertexIndices);
}

std::vector<int> Face::getTextureIndices() const {
	return (this->textureIndices);
}

std::vector<int> Face::getNormalIndices() const {
	return (this->normalIndices);
}

std::string Face::getMaterialName() const {
	return (this->materialName);
}

bool Face::isSmoothing() const {
	return (this->smoothing);
}

void Face::setVertexIndices(std::vector<int> v) {
	this->vertexIndices = v;
}

void Face::setTextureIndices(std::vector<int> v) {
	this->textureIndices = v;
}

void Face::setNormalIndices(std::vector<int> v) {
	this->normalIndices = v;
}

void Face::setMaterialName(std::string s) {
	this->materialName = s;
}

void Face::setSmoothing(bool b) {
	this->smoothing = b;
}

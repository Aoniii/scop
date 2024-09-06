#include "scop.hpp"

Object::Object(): name(""), VAO(0), VBO_vertices(0), VBO_textures(0), VBO_normals(0), EBO(0) {}

Object::~Object() {
	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO_vertices);
	glDeleteBuffers(1, &this->VBO_textures);
	glDeleteBuffers(1, &this->VBO_normals);
	glDeleteBuffers(1, &this->EBO);
}

Object::Object(const Object &object) {
	*this = object;
}
Object &Object::operator=(const Object &object) {
	this->name = object.name;
	this->vertices = object.vertices;
	this->textures = object.textures;
	this->normals = object.normals;
	this->faces = object.faces;
	this->VAO = object.VAO;
	this->VBO_vertices = object.VBO_vertices;
	this->VBO_textures = object.VBO_textures;
	this->VBO_normals = object.VBO_normals;
	this->EBO = object.EBO;
	this->nbIndices = object.nbIndices;
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

void Object::addVertex(Vertex v) {
	this->vertices.push_back(v);
}

void Object::addTexture(TextureCoord t) {
	this->textures.push_back(t);
}

void Object::addNormal(Normal n) {
	this->normals.push_back(n);
}

void Object::addFace(Face f) {
	this->faces.push_back(f);
}

void Object::setupBuffers() {
	glGenVertexArrays(1, &this->VAO);
	glBindVertexArray(this->VAO);
	
	glGenBuffers(1, &this->VBO_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO_vertices);
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex), this->vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	if (!this->textures.empty()) {
		glGenBuffers(1, &this->VBO_textures);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO_textures);
		glBufferData(GL_ARRAY_BUFFER, this->textures.size() * sizeof(TextureCoord), this->textures.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(TextureCoord), (void*)0);
		glEnableVertexAttribArray(1);
	}

	if (!this->normals.empty()) {
		glGenBuffers(1, &this->VBO_normals);
		glBindBuffer(GL_ARRAY_BUFFER, this->VBO_normals);
		glBufferData(GL_ARRAY_BUFFER, this->normals.size() * sizeof(Normal), this->normals.data(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Normal), (void*)0);
		glEnableVertexAttribArray(2);
	}

	std::vector<GLuint> indices;
	for (const Face& face : this->faces) {
		std::vector<int> vertexIndices = face.getVertexIndices();

		if (vertexIndices.size() < 3) {
			std::cerr << "Face with fewer than 3 vertices detected!" << std::endl;
			continue;
		}

		for (size_t i = 0; i < vertexIndices.size() - 1; i++) {
			indices.push_back(vertexIndices[i] - 1);
			indices.push_back(vertexIndices[i + 1] - 1);
			indices.push_back(vertexIndices[(i + 2) % vertexIndices.size()] - 1);
		}
	}

	glGenBuffers(1, &this->EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint),indices.data(), GL_STATIC_DRAW);
	this->nbIndices = indices.size();

	glBindVertexArray(0);
}

void Object::draw() {
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->nbIndices, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Object::drawWithMaterial(Program* program, Shader* shader) {
	glBindVertexArray(this->VAO);
	size_t i = 0;
	for (const Face& face : this->faces) {
		Material *material = program->getMaterial(face.getMaterialName());
		if (material)
			shader->setMaterial(*material);
		else
			shader->setMaterial(*program->getBlank());
		for (size_t j = 1; j < face.getVertexIndices().size(); j++) {
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)((i * 3) * sizeof(GLuint)));
			i++;
		}
	}
	glBindVertexArray(0);
}

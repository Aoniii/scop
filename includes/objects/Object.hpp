#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>
#include <string>
#include "Vertex.hpp"
#include "TextureCoord.hpp"
#include "Normal.hpp"
#include "Face.hpp"

class Object {
	private:
		std::string name;
		std::vector<Vertex> vertices;
		std::vector<TextureCoord> textures;
		std::vector<Normal> normals;
		std::vector<Face> faces;

	public:
		Object();
		~Object();
		Object(const Object &object);
		Object &operator=(const Object &object);

		std::string getName() const;
		std::vector<Vertex> getVertices() const;
		std::vector<TextureCoord> getTextures() const;
		std::vector<Normal> getNormals() const;
		std::vector<Face> getFaces() const;

		void setName(std::string name);
		void setVertices(std::vector<Vertex> vertices);
		void setTextures(std::vector<TextureCoord> textures);
		void setNormals(std::vector<Normal> normals);
		void setFaces(std::vector<Face> faces);
};

#endif

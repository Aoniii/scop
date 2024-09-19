#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>

class Vertex {
	private:
		float x;
		float y;
		float z;
		float w;

	public:
		Vertex();
		~Vertex();
		Vertex(const Vertex &vertex);
		Vertex &operator=(const Vertex &vertex);

		Vertex(float x, float y, float z);
		Vertex(float x, float y, float z, float w);

		float getX() const;
		float getY() const;
		float getZ() const;
		float getW() const;

		void setX(float x);
		void setY(float y);
		void setZ(float z);
		void setW(float w);

		glm::vec3 getPos() const;
};

#endif

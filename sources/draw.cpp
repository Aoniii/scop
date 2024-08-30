#include "scop.hpp"

void drawPoint(Program *program) {
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (Object* objects : program->getObjects())
		for (Vertex vertex : objects->getVertices())
			glVertex4f(vertex.getX(), vertex.getY(), vertex.getZ(), vertex.getW());

	glEnd();
}

void drawLine(Program *program) {
	glBegin(GL_LINES);
	glColor3f(1.0f, 1.0f, 1.0f);

	for (Object* objects : program->getObjects()) {
		std::vector<Vertex> vertices = objects->getVertices();
		for (Face face : objects->getFaces()) {
			std::vector<int> vertexIndices = face.getVertexIndices();
			for (size_t i = 0; i < vertexIndices.size(); i++) {
				int currentIndex = vertexIndices[i] - 1;
				int nextIndex = vertexIndices[(i + 1) % vertexIndices.size()] - 1;
				glVertex4f(vertices[currentIndex].getX(), vertices[currentIndex].getY(), vertices[currentIndex].getZ(), vertices[currentIndex].getW());
				glVertex4f(vertices[nextIndex].getX(), vertices[nextIndex].getY(), vertices[nextIndex].getZ(), vertices[nextIndex].getW());
			}
		}
	}
	glEnd();
}

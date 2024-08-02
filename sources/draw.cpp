#include "scop.hpp"

void drawPoint(Program *program) {
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (Object* objects : program->getObjects()) {
		for (Vertex vertex : objects->getVertices()) {
			glVertex4f(vertex.getX(), vertex.getY(), vertex.getZ(), vertex.getW());
		}
	}
	glEnd();
}

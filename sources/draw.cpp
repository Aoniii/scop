#include "scop.hpp"

void drawPoint(const std::vector<OBJModel*> &models) {
	glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    for (const OBJModel* obj : models) {
        for (const Vertex& vertex : obj->vertices) {
            glVertex3f(vertex.x, vertex.y, vertex.z);
        }
    }
    glEnd();
}

void drawFace(const std::vector<OBJModel*> &models) {
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (const OBJModel* obj : models) {
		for (const Face& face : obj->faces) {
			for (size_t i = 0; i < face.vertexIndices.size(); ++i) {
				int vertexIndex = face.vertexIndices[i];
				const Vertex& vertex = obj->vertices[vertexIndex];
				if (!face.normalIndices.empty()) {
					int normalIndex = face.normalIndices[i];
					const Normal& normal = obj->normals[normalIndex];
					glNormal3f(normal.i, normal.j, normal.k);
				}
				if (!face.textureIndices.empty()) {
					int textureIndex = face.textureIndices[i];
					const TextureCoord& texCoord = obj->textureCoords[textureIndex];
					glTexCoord2f(texCoord.u, texCoord.v);
				}
				glVertex3f(vertex.x, vertex.y, vertex.z);
			}
		}
	}
	glEnd();
}

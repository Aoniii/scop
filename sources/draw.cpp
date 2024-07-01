#include "scop.hpp"

void drawPoint(const std::vector<OBJModel*> &models) {
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 1.0f, 1.0f);
	for (const OBJModel* obj : models) {
		for (const Vertex& vertex : obj->vertices) {
			glVertex3f(vertex.x, vertex.y, vertex.z);
		}
	}
	glEnd();
}

void applyMaterial(const Material &material) {
	GLfloat ambient[] = { material.Ka[0], material.Ka[1], material.Ka[2], 1.0f };
	GLfloat diffuse[] = { material.Kd[0], material.Kd[1], material.Kd[2], 1.0f };
	GLfloat specular[] = { material.Ks[0], material.Ks[1], material.Ks[2], 1.0f };
	GLfloat shininess = material.Ns;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
}


void drawFace(const std::vector<OBJModel*> &models, const std::map<std::string, Material*> &materials) {
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	
	for (const OBJModel* obj : models) {
		for (const Face& face : obj->faces) {
			if (!face.materialName.empty()) {
				auto it = materials.find(face.materialName);
				if (it != materials.end()) {
					applyMaterial(*(it->second));
				}
			}
			
			glBegin(GL_TRIANGLES);
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
			glEnd();
		}
	}
}

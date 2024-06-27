#include "scop.hpp"

glm::vec3 calculateCenter(const std::vector<Vertex>& vertices) {
	glm::vec3 center(0.0f);
	for (const Vertex& vertex : vertices)
		center += glm::vec3(vertex.x, vertex.y, vertex.z);
	center /= static_cast<float>(vertices.size());
	return (center);
}

void calculateBoundingBox(const std::vector<OBJModel*>& models, glm::vec3& center, float& maxDimension) {
	if (models.empty()) return;

	glm::vec3 min(std::numeric_limits<float>::max());
	glm::vec3 max(std::numeric_limits<float>::lowest());

	for (const OBJModel* model : models) {
		for (const Vertex& vertex : model->vertices) {
			if (vertex.x < min.x) min.x = vertex.x;
			if (vertex.y < min.y) min.y = vertex.y;
			if (vertex.z < min.z) min.z = vertex.z;

			if (vertex.x > max.x) max.x = vertex.x;
			if (vertex.y > max.y) max.y = vertex.y;
			if (vertex.z > max.z) max.z = vertex.z;
		}
	}

	center = (min + max) / 2.0f;
	maxDimension = glm::length(max - min);
}

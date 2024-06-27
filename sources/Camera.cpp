#include "scop.hpp"

Camera::Camera() {}

Camera::~Camera() {}

Camera::Camera(const Camera &camera) {
	*this = camera;
}

Camera &Camera::operator=(const Camera &camera) {
	this->x = camera.x;
	this->y = camera.y;
	this->z = camera.z;
	this->angleX = camera.angleX;
	this->angleY = camera.angleY;
	this->angleZ = camera.angleZ;
	return (*this);
}

float Camera::getAngleX() const {
	return (this->angleX);
}

float Camera::getAngleY() const {
	return (this->angleY);
}

float Camera::getAngleZ() const {
	return (this->angleZ);
}

void Camera::addAngleX(float f) {
	this->angleX += f;
}

void Camera::addAngleY(float f) {
	this->angleY += f;
}

void Camera::addAngleZ(float f) {
	this->angleZ += f;
}

glm::mat4 Camera::getView() const {
	glm::vec3 pos = glm::vec3(this->x, this->y, this->z);
	return (glm::lookAt(pos, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
}


void Camera::initCoord(const std::vector<OBJModel*> &models) {
	glm::vec3 center;
	float maxDimension;
	calculateBoundingBox(models, center, maxDimension);

	this->x = center.x;
	this->y = center.y;
	this->z = center.z + maxDimension * 1.5f;
	glm::vec3 direction = center - glm::vec3(this->x, this->y, this->z);
	this->yaw = glm::degrees(atan2(direction.z, direction.x)) - 90.0f;
	this->pitch = glm::degrees(atan2(direction.y, sqrt(direction.x * direction.x + direction.z * direction.z)));
}

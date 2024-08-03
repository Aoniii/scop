#include "scop.hpp"

Camera::Camera() {
	updateCameraVectors();
}

Camera::~Camera() {}

Camera::Camera(const Camera &camera) {
	*this = camera;
}

Camera &Camera::operator=(const Camera &camera) {
	this->pos = camera.pos;
	this->front = camera.front;
	this->up = camera.up;
	this->right = camera.right;
	this->worldUp = camera.worldUp;
	this->yaw = camera.yaw;
	this->pitch = camera.pitch;
	this->zoom = camera.zoom;
	return (*this);
}

glm::vec3 Camera::getPos() const {
	return (this->pos);
}

glm::vec3 Camera::getFront() const {
	return (this->front);
}

glm::vec3 Camera::getUp() const {
	return (this->up);
}

glm::vec3 Camera::getRight() const {
	return (this->right);
}

glm::vec3 Camera::getWorldUp() const {
	return (this->worldUp);
}

float Camera::getYaw() const {
	return (this->yaw);
}

float Camera::getPitch() const {
	return (this->pitch);
}

float Camera::getZoom() const {
	return (this->zoom);
}

void Camera::setPos(glm::vec3 pos) {
	this->pos = pos;
}

void Camera::setFront(glm::vec3 front) {
	this->front = front;
}

void Camera::setUp(glm::vec3 up) {
	this->up = up;
}

void Camera::setRight(glm::vec3 right) {
	this->right = right;
}

void Camera::setWorldUp(glm::vec3 worldUp) {
	this->worldUp = worldUp;
}

void Camera::setYaw(float yaw) {
	this->yaw = yaw;
}

void Camera::setPitch(float pitch) {
	this->pitch = pitch;
}

void Camera::setZoom(float zoom) {
	this->zoom = zoom;
}

glm::mat4 Camera::getViewMatrix() {
    return (glm::lookAt(this->pos, this->pos + this->front, this->up));
}

void Camera::updateCameraVectors() {
	glm::vec3 f;
	f.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	f.y = sin(glm::radians(this->pitch));
	f.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	this->front = glm::normalize(f);
	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

void Camera::initPos(Program *program) {
	bool first = true;
	float maxX, minX, maxY, minY, maxZ, minZ;

	for (Object* objects : program->getObjects()) {
		for (Vertex vertex : objects->getVertices()) {
			if (first) {
				maxX = minX = vertex.getX();
				maxY = minY = vertex.getY();
				maxZ = minZ = vertex.getZ();
				first = false;
				continue;
			}

			if (vertex.getX() > maxX)
				maxX = vertex.getX();
			if (vertex.getX() < minX)
				minX = vertex.getX();
			if (vertex.getY() > maxY)
				maxY = vertex.getY();
			if (vertex.getY() < minY)
				minY = vertex.getY();
			if (vertex.getZ() > maxZ)
				maxZ = vertex.getZ();
			if (vertex.getZ() < minZ)
				minZ = vertex.getZ();
		}
	}

	this->pos = glm::vec3((minX + maxX) / 2.0f, (maxY + maxY) / 2.0f, ((minZ + maxZ) / 2.0f) + (minX - maxX));
}

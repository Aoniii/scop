#include "Camera.hpp"

Camera::Camera() {}

Camera::~Camera() {}

Camera::Camera(const Camera &camera) {
	*this = camera;
}

Camera &Camera::operator=(const Camera &camera) {
	this->pos = camera.pos;
	this->target = camera.target;
	this->direction = camera.direction;
	this->right = camera.right;
	this->up = camera.up;
	return (*this);
}

glm::vec3 Camera::getPos() const {
	return (this->pos);
}

glm::vec3 Camera::getTarget() const {
	return (this->target);
}

glm::vec3 Camera::getDirection() const {
	return (this->direction);
}

glm::vec3 Camera::getRight() const {
	return (this->right);
}

glm::vec3 Camera::getUp() const {
	return (this->up);
}

void Camera::setPos(glm::vec3 pos) {
	this->pos = pos;
}

void Camera::setTarget(glm::vec3 target) {
	this->target = target;
}

void Camera::setDirection(glm::vec3 direction) {
	this->direction = direction;
}

void Camera::setRight(glm::vec3 right) {
	this->right = right;
}

void Camera::setUp(glm::vec3 up) {
	this->up = up;
}

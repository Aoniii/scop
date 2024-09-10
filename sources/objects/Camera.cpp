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

float Camera::getAngleX() const {
	return (this->angleX);
}

float Camera::getAngleY() const {
	return (this->angleY);
}

float Camera::getAngleZ() const {
	return (this->angleZ);
}

unsigned int Camera::getType() const {
	return (this->type);
}

bool Camera::getRotate() const {
	return (this->rotate);
}

bool Camera::getReset() const {
	return (this->reset);
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

void Camera::setAngleX(float f) {
	this->angleX = f;
}

void Camera::setAngleY(float f) {
	this->angleY = f;
}

void Camera::setAngleZ(float f) {
	this->angleZ = f;
}

void Camera::setType(unsigned int type) {
	this->type = type;
}

void Camera::setRotate(bool b) {
	this->rotate = b;
}

void Camera::setReset(bool b) {
	this->reset = b;
}

void Camera::addPos(glm::vec3 pos) {
	this->pos.x += pos.x;
	this->pos.y += pos.y;
	this->pos.z += pos.z;
	updateCameraVectors();
}

void Camera::addAngleX(float f) {
	this->angleX += f;
	if (this->angleX < 0)
		this->angleX += 360.0f;
	else if (this->angleX > 360.0f)
		this->angleX -= 360.0f;
}

void Camera::addAngleY(float f) {
	this->angleY += f;
	if (this->angleY < 0)
		this->angleY += 360.0f;
	else if (this->angleY > 360.0f)
		this->angleY -= 360.0f;
}

void Camera::addAngleZ(float f) {
	this->angleZ += f;
	if (this->angleZ < 0)
		this->angleZ += 360.0f;
	else if (this->angleZ > 360.0f)
		this->angleZ -= 360.0f;
}

void Camera::addYaw(float f) {
	this->yaw += f;
	if (this->yaw < -180.0f)
		this->yaw += 360.0f;
	else if (this->yaw > 180.0f)
		this->yaw -= 360.0f;
	updateCameraVectors();
}

void Camera::addPitch(float f) {
	this->pitch += f;
	if (this->pitch < -180.0f)
		this->pitch += 360.0f;
	else if (this->pitch > 180.0f)
		this->pitch -= 360.0f;
	updateCameraVectors();
}

void Camera::toggleRotate() {
	this->rotate = !this->rotate;
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

void calculateBoundingBox(std::vector<Object*> objects, glm::vec3& center, float& maxDimension) {
	glm::vec3 min(std::numeric_limits<float>::max());
	glm::vec3 max(std::numeric_limits<float>::lowest());

	for (const Object* object : objects) {
		for (const Vertex& vertex : object->getVertices()) {
			if (vertex.getX() < min.x) min.x = vertex.getX();
			if (vertex.getY() < min.y) min.y = vertex.getY();
			if (vertex.getZ() < min.z) min.z = vertex.getZ();

			if (vertex.getX() > max.x) max.x = vertex.getX();
			if (vertex.getY() > max.y) max.y = vertex.getY();
			if (vertex.getZ() > max.z) max.z = vertex.getZ();
		}
	}

	center = (min + max) / 2.0f;
	maxDimension = glm::length(max - min);
}

void Camera::initCoord(std::vector<Object*> objects) {
	glm::vec3 center;
	float maxDimension;
	calculateBoundingBox(objects, center, maxDimension);

	this->pos.x = center.x + maxDimension * 1.5f;;
	this->pos.y = center.y;
	this->pos.z = center.z;
	updateCameraVectors();
}

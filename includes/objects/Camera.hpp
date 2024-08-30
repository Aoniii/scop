#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Program;

class Camera {
	private:
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 right = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
		float yaw = 180.0f;
		float pitch = 0.0f;
		float angleX = 0.0f;
		float angleY = 0.0f;
		float angleZ = 0.0f;

	public:
		Camera();
		~Camera();
		Camera(const Camera &camera);
		Camera &operator=(const Camera &camera);

		glm::vec3 getPos() const;
		glm::vec3 getFront() const;
		glm::vec3 getUp() const;
		glm::vec3 getRight() const;
		glm::vec3 getWorldUp() const;
		float getYaw() const;
		float getPitch() const;
		float getAngleX() const;
		float getAngleY() const;
		float getAngleZ() const;

		void setPos(glm::vec3 pos);
		void setFront(glm::vec3 front);
		void setUp(glm::vec3 up);
		void setRight(glm::vec3 right);
		void setWorldUp(glm::vec3 worldUp);
		void setYaw(float yaw);
		void setPitch(float pitch);
		void setAngleX(float f);
		void setAngleY(float f);
		void setAngleZ(float f);

		void addPos(glm::vec3 pos);
		void addAngleX(float f);
		void addAngleY(float f);
		void addAngleZ(float f);

		glm::mat4 getViewMatrix();
		void updateCameraVectors();
		void initCoord(std::vector<Object*> objects);
};

#endif
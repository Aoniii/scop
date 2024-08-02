#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
	private:
		glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);		//glm::normalize(pos - target);
		glm::vec3 right = glm::vec3(0.0f, 0.0f, 0.0f);			//glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), direction));
		glm::vec3 up = glm::vec3(0.0f, 0.0f, 0.0f);				//glm::cross(direction, right);

	public:
		Camera();
		~Camera();
		Camera(const Camera &camera);
		Camera &operator=(const Camera &camera);

		glm::vec3 getPos() const;
		glm::vec3 getTarget() const;
		glm::vec3 getDirection() const;
		glm::vec3 getRight() const;
		glm::vec3 getUp() const;

		void setPos(glm::vec3 pos);
		void setTarget(glm::vec3 target);
		void setDirection(glm::vec3 direction);
		void setRight(glm::vec3 right);
		void setUp(glm::vec3 up);
};

#endif

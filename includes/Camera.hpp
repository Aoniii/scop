#ifndef CAMERA_HPP
#define CAMERA_HPP

struct OBJModel;

class Camera {
	private:
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float angleX = 0.0f;
		float angleY = 0.0f;
		float angleZ = 0.0f;
		float yaw = 0.0f;
		float pitch = 0.0f;

	public:
		Camera();
		~Camera();
		Camera(const Camera &camera);
		Camera &operator=(const Camera &camera);

		float getAngleX() const;
		float getAngleY() const;
		float getAngleZ() const;

		void addAngleX(float f);
		void addAngleY(float f);
		void addAngleZ(float f);

		glm::mat4 getView() const;
		void updateCameraVectors();
		void initCoord(const std::vector<OBJModel*> &models);
};

#endif

#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "Object.hpp"
#include "Material.hpp"
#include "Window.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Program {
	private:
		std::string name;
		std::vector<Object*> objects;
		std::vector<Material*> materials;
		Window *window;
		Material *blank;
		unsigned int texture;
		float color[3] = {1.0f, 1.0f, 1.0f};

	public:
		Program();
		~Program();
		Program(const Program &program);
		Program &operator=(const Program &program);

		std::string getName() const;
		std::vector<Object*> getObjects() const;
		std::vector<Material*> getMaterials() const;
		Window *getWindow() const;
		Material *getMaterial(std::string name) const;
		Material *getBlank() const;
		unsigned int getTexture() const;
		float *getColor() const;

		void setName(std::string name);
		void setObjects(std::vector<Object*> objects);
		void setMaterials(std::vector<Material*> materials);
		void setWindow(Window *window);
		void setTexture(unsigned int textureID);
		void setColor(float color[3]);

		void setFile(std::string filename);
		void addObject(Object *object);
		void addMaterial(Material *material);
		void loadTexture(const char* path);

		glm::vec3 calculateCenter() const;

		size_t vertexSize() const;
		size_t faceSize() const;
};

#endif

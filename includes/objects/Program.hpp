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

	public:
		Program();
		~Program();
		Program(const Program &program);
		Program &operator=(const Program &program);

		std::string getName() const;
		std::vector<Object*> getObjects() const;
		std::vector<Material*> getMaterials() const;
		Window *getWindow() const;

		void setName(std::string name);
		void setObjects(std::vector<Object*> objects);
		void setMaterials(std::vector<Material*> materials);
		void setWindow(Window *window);

		void setFile(std::string filename);
		void addObject(Object *object);
		void addMaterial(Material *material);

		glm::vec3 calculateCenter() const;
};

#endif

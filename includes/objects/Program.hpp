#ifndef PROGRAM_HPP
#define PROGRAM_HPP

#include "Object.hpp"
#include "Material.hpp"

class Program {
	private:
		std::vector<Object> objects;
		std::vector<Material> materials;

	public:
		Program();
		~Program();
		Program(const Program &program);
		Program &operator=(const Program &program);

		std::vector<Object> getObjects() const;
		std::vector<Material> getMaterials() const;

		void setObjects(std::vector<Object> objects);
		void setMaterials(std::vector<Material> materials);
};

#endif

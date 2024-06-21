#include "scop.hpp"

void clean(std::vector<OBJModel*> &models, std::map<std::string, Material*> &materials) {
	for (OBJModel* ptr : models)
        delete ptr;
	for (auto& pair : materials)
        delete pair.second;

	models.clear();
	materials.clear();
}

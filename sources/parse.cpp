#include "scop.hpp"

int parseMTL(const std::string filename, std::map<std::string, Material*> &materials) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "[\e[31mERROR\e[39m] File MTL cannot be opened !" << std::endl;
		return (-1);
	}
	std::string line;
	Material *currentMaterial = new Material();
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string command;
		iss >> command;

		if (command == "newmtl") {
			if (!currentMaterial->name.empty()) {
				materials.insert(std::pair<std::string, Material*>(currentMaterial->name, currentMaterial));
				currentMaterial = new Material();
			}
			iss >> currentMaterial->name;
		} else if (command == "Ka") {
			iss >> currentMaterial->Ka[0] >> currentMaterial->Ka[1] >> currentMaterial->Ka[2];
		} else if (command == "Kd") {
			iss >> currentMaterial->Kd[0] >> currentMaterial->Kd[1] >> currentMaterial->Kd[2];
		} else if (command == "Ks") {
			iss >> currentMaterial->Ks[0] >> currentMaterial->Ks[1] >> currentMaterial->Ks[2];
		} else if (command == "Ns") {
			iss >> currentMaterial->Ns;
		} else if (command == "d" || command == "Tr") {
			iss >> currentMaterial->d;
		} else if (command == "Ni") {
			iss >> currentMaterial->Ni;
		} else if (command == "illum") {
			iss >> currentMaterial->illum;
		}
	}

	if (!currentMaterial->name.empty())
		materials.insert(std::pair<std::string, Material*>(currentMaterial->name, currentMaterial));
	file.close();
	return (0);
}

int parseOBJ(const std::string filename, std::vector<OBJModel*> &models, std::map<std::string, Material*> &materials) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "[\e[31mERROR\e[39m] File OBJ cannot be opened !" << std::endl;
		return (-1);
	}

	std::string line;
	std::string	currentMaterial = "";
	int currentSmoothing = 0;
	OBJModel *currentModel = new OBJModel();
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string command;
		iss >> command;

		if (command == "o") {
			if (!currentModel->vertices.empty()) {
				models.push_back(currentModel);
				currentModel = new OBJModel();
			}
			iss >> currentModel->name;
		} else if (command == "v") {
			Vertex vertex;
			iss >> vertex.x >> vertex.y >> vertex.z >> vertex.w;
			currentModel->vertices.push_back(vertex);
		} else if (command == "vt") {
			TextureCoord textureCoord;
			iss >> textureCoord.u >> textureCoord.v >> textureCoord.w;
			currentModel->textureCoords.push_back(textureCoord);
		} else if (command == "vn") {
			Normal normal;
			iss >> normal.i >> normal.j >> normal.k;
			currentModel->normals.push_back(normal);
		} else if (command == "f") {
			Face face;
			std::string vertexData;

			face.materialName = currentMaterial;
			face.smoothing = currentSmoothing;
			while (iss >> vertexData) {
				std::istringstream viss(vertexData);
				std::string index;
				int vertexIndex, textureIndex, normalIndex;

				std::getline(viss, index, '/');
				vertexIndex = std::stoi(index) - 1;
				face.vertexIndices.push_back(vertexIndex);

				if (std::getline(viss, index, '/')) {
					if (!index.empty()) {
						textureIndex = std::stoi(index) - 1;
						face.textureIndices.push_back(textureIndex);
					}
					if (std::getline(viss, index, '/')) {
						if (!index.empty()) {
							normalIndex = std::stoi(index) - 1;
							face.normalIndices.push_back(normalIndex);
						}
					}
				}
			}
			currentModel->faces.push_back(face);
		} else if (command == "usemtl") {
			iss >> currentMaterial;
		} else if (command == "s") {
			std::string smoothing;
			iss >> smoothing;
			if (smoothing == "off")
				currentSmoothing = 0;
			else
				currentSmoothing = std::stoi(smoothing);
		} else if (command == "mtllib") {
			std::string mtlFilename;
			iss >> mtlFilename;
			std::filesystem::path path(filename);
			if (path.parent_path().string().size() > 0)
				mtlFilename = path.parent_path().string() + "/" + mtlFilename;
			if (!extensionChecker(mtlFilename, ".mtl")) {
				std::cerr << "[\e[31mERROR\e[39m] The material file isn't an file.mtl" << std::endl;
				return (-1);
			}
			if (parseMTL(mtlFilename, materials) < 0)
				return (-1);
		}
	}

	if (!currentModel->vertices.empty())
		models.push_back(currentModel);
	file.close();
	return (0);
}

bool extensionChecker(const std::string file, const std::string extension) {
	if (extension.size() > file.size())
        return (false);
	return (file.compare(file.size() - extension.size(), extension.size(), extension) == 0);
}

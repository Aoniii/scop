#include "scop.hpp"

void parseMTL(std::string filename, Program *program);

Program *parse(const std::string filename) {
	Program *program = new Program();
	program->setFile(filename);

	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "[\e[31mERROR\e[39m] File OBJ cannot be opened !" << std::endl;
		exit(1);
	}

	std::string line;
	int nbLine = 0;
	Object *object = NULL;
	std::string mat = "";
	int smoothing = 0;
	while (std::getline(file, line)) {
		nbLine++;
		std::istringstream iss(line);
		std::string command;
		iss >> command;

		if (command == "o") {
			std::string name;
			iss >> name;
			object = new Object();
			object->setName(name);
			program->addObject(object);
		} else if (command == "mtllib") {
			std::string path = "", mtl;
			iss >> mtl;
			size_t i = filename.find_last_of('/');
			if (i != std::string::npos)
				path = filename.substr(0, i + 1);
			parseMTL(path + mtl, program);
		} else if (command[0] && command[0] != '#' && command[0] != ' ') {
			if (command == "v" || command == "vt" || command == "vn" || command == "f" || command == "usemtl" || command == "s") {
				if (object == NULL) {
					object = new Object();
					object->setName("Unnamed");
					program->addObject(object);
				}
			} else {
				std::cerr << "[\e[31mERROR\e[39m] File OBJ contains an error ! (line: " << nbLine << ")" << std::endl;
				exit(1);
			}
		}
		
		if (command == "v") {
			float x = 0, y = 0, z = 0, w = 0;
			iss >> x >> y >> z >> w;
			if (w != 0)
				object->addVertex(Vertex(x, y, z, w));
			else
				object->addVertex(Vertex(x, y, z));
		} else if (command == "vt") {
			float u = 0, v = 0, w = 0;
			iss >> u >> v >> w;
			if (w != 0)
				object->addTexture(TextureCoord(u, v, w));
			else if (v != 0)
				object->addTexture(TextureCoord(u, v));
			else
				object->addTexture(TextureCoord(u));
		} else if (command == "vn") {
			float i = 0, j = 0, k = 0;
			iss >> i >> j >> k;
			object->addNormal(Normal(i, j, k));
		} else if (command == "f") {
			std::vector<int> vertexIndices;
			std::vector<int> textureIndices;
			std::vector<int> normalIndices;

			std::string data;
			while (iss >> data) {
				std::istringstream viss(data);
				std::string index;
				int v = -1, t = -1, n = -1;

				std::getline(viss, index, '/');
				v = std::stoi(index);
				if (std::getline(viss, index, '/')) {
					if (!index.empty())
						t = std::stoi(index);
					if (std::getline(viss, index, '/'))
						if (!index.empty())
							n = std::stoi(index);
				}
				vertexIndices.push_back(v);
				textureIndices.push_back(t);
				normalIndices.push_back(n);
			}
			object->addFace(Face(vertexIndices, textureIndices, normalIndices, mat, smoothing));
		} else if (command == "usemtl") {
			iss >> mat;
		} else if (command == "s") {
			std::string s;
			iss >> s;
			if (s == "off")
				smoothing = 0;
			else
				smoothing = std::stoi(s);
		}
	}

	file.close();
	return (program);
}

void parseMTL(std::string filename, Program *program) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "[\e[31mERROR\e[39m] File MTL cannot be opened !" << std::endl;
		exit(1);
	}

	std::string line;
	int nbLine = 0;
	Material *material = NULL;
	while (std::getline(file, line)) {
		nbLine++;
		std::istringstream iss(line);
		std::string command;
		iss >> command;

		if (command == "newmtl") {
			std::string name;
			iss >> name;
			material = new Material();
			material->setName(name);
			program->addMaterial(material);
		} else if (command[0] && command[0] != '#' && command[0] != ' ' && material == NULL) {
			std::cerr << "[\e[31mERROR\e[39m] File MTL contains an error ! (line: " << nbLine << ")" << std::endl;
			exit(1);
		} else if (command == "Ka") {
			float i = 0, j = 0, k = 0;
			iss >> i >> j >> k;
			material->setKa({i, j, k});
		} else if (command == "Kd") {
			float i = 0, j = 0, k = 0;
			iss >> i >> j >> k;
			material->setKd({i, j, k});
		} else if (command == "Ks") {
			float i = 0, j = 0, k = 0;
			iss >> i >> j >> k;
			material->setKs({i, j, k});
		} else if (command == "Ns") {
			float i = 0;
			iss >> i;
			material->setNs(i);
		} else if (command == "d" || command == "Tr") {
			float i = 0;
			iss >> i;
			material->setD(i);
		} else if (command == "Ni") {
			float i = 0;
			iss >> i;
			material->setNi(i);
		} else if (command == "illum") {
			int i = 0;
			iss >> i;
			material->setIllum(i);
		}
	}

	file.close();
}

void parsingChecker(Program *program) {
	std::filesystem::create_directory("parsingChecker");
	std::ofstream materialFile("parsingChecker/" + program->getName() + ".mtl");

	if (!materialFile) {
        std::cerr << "[\e[31mERROR\e[39m] File MTL cannot be created !" << std::endl;
        exit(1);
    }

	materialFile << "# Material Count: " << program->getMaterials().size() << std::endl;
	for (Material *material : program->getMaterials()) {
		materialFile << std::endl;
		materialFile << "newmtl " << material->getName() << std::endl;
		materialFile << "Ns " << material->getNs() << std::endl;
		materialFile << "Ka " << material->getKa()[0] << " " << material->getKa()[1] << " " << material->getKa()[2] << std::endl;
		materialFile << "Kd " << material->getKd()[0] << " " << material->getKd()[1] << " " << material->getKd()[2] << std::endl;
		materialFile << "Ks " << material->getKs()[0] << " " << material->getKs()[1] << " " << material->getKs()[2] << std::endl;
		materialFile << "Ni " << material->getNi() << std::endl;
		materialFile << "d " << material->getD() << std::endl;
		materialFile << "illum " << material->getIllum() << std::endl;
	}

	materialFile.close();

	std::ofstream objectFile("parsingChecker/" + program->getName() + ".obj");

	if (!objectFile) {
        std::cerr << "[\e[31mERROR\e[39m] File MTL cannot be created !" << std::endl;
        exit(1);
    }

	objectFile << "mtllib " << program->getName() << ".mtl" << std::endl;
	for (Object *object : program->getObjects()) {
		objectFile << "o " << object->getName() << std::endl;
		for (Vertex vertex : object->getVertices()) {
			if (vertex.getW() != 1)
				objectFile << "v " << vertex.getX() << " " << vertex.getY() << " " << vertex.getZ() << " " << vertex.getW() << std::endl;
			else
				objectFile << "v " << vertex.getX() << " " << vertex.getY() << " " << vertex.getZ() << std::endl;
		}
		for (TextureCoord texture : object->getTextures()) {
			if (texture.getW() != 0)
				objectFile << "vt " << texture.getU() << " " << texture.getV() << " " << texture.getW() << std::endl;
			else if (texture.getV() != 0)
				objectFile << "vt " << texture.getU() << " " << texture.getV() << std::endl;
			else
				objectFile << "vt " << texture.getU() << std::endl;
		}
		for (Normal normal : object->getNormals()) {
				objectFile << "vn " << normal.getI() << " " << normal.getJ() << " " << normal.getK() << std::endl;
		}
		std::string mat = "";
		int smoothing = -1;
		for (Face face : object->getFaces()) {
			if (mat != face.getMaterialName()) {
				mat = face.getMaterialName();
				objectFile << "usemtl " << mat << std::endl;
			}
			if (smoothing != face.getSmoothing()) {
				smoothing = face.getSmoothing();
				if (smoothing == 0)
					objectFile << "s off" << std::endl;
				else
					objectFile << "s " << smoothing << std::endl;
			}
			objectFile << "f ";
			for (size_t i = 0; i < face.getVertexIndices().size(); i++) {
				objectFile << face.getVertexIndices().at(i);
				if (face.getTextureIndices().at(i) != -1)
					objectFile << "/" << face.getTextureIndices().at(i);
				if (face.getTextureIndices().at(i) == -1 && face.getNormalIndices().at(i) != -1)
					objectFile << "/";
				if (face.getNormalIndices().at(i) != -1)
					objectFile << "/" << face.getNormalIndices().at(i);
				objectFile << " ";
			}
			objectFile << std::endl;
		}
	}

	objectFile.close();
}

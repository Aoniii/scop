#ifndef SCOP_HPP
#define SCOP_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include <vector>
#include <map>
#include <GLFW/glfw3.h>
#include "Window.hpp"

struct Vertex {
	float x;
	float y;
	float z;
	float w = 1.0f;
};

struct TextureCoord {
	float u;
	float v = 0.0f;
	float w = 0.0f;
};

struct Normal {
	float i;
	float j;
	float k;
};

struct Face {
	std::vector<int> vertexIndices;
	std::vector<int> textureIndices;
	std::vector<int> normalIndices;
	std::string materialName;
	int smoothing;
};

struct Material {
	std::string name;
	float Ka[3];
	float Kd[3];
	float Ks[3];
	float Ns;
	float d;
	float Ni;
	int illum;
};

struct OBJModel {
	std::string name;
	std::vector<Vertex> vertices;
	std::vector<Normal> normals;
	std::vector<TextureCoord> textureCoords;
	std::vector<Face> faces;
};

int parseMTL(const std::string filename, std::map<std::string, Material*> &materials);
int parseOBJ(const std::string filename, std::vector<OBJModel*> &models, std::map<std::string, Material*> &materials);
void clean(std::vector<OBJModel*> &models, std::map<std::string, Material*> &materials);
bool extensionChecker(const std::string file, const std::string extension);

#endif

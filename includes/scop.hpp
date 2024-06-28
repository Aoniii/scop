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
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Window.hpp"
#include "Camera.hpp"

#define ANGLE 0.5f

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
glm::vec3 calculateCenter(const std::vector<Vertex> &vertices);
void calculateBoundingBox(const std::vector<OBJModel*> &models, glm::vec3 &center, float &maxDimension);
void drawPoint(const std::vector<OBJModel*> &models);
void drawFace(const std::vector<OBJModel*> &models);

#endif

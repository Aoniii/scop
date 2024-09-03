#ifndef SCOP_HPP
#define SCOP_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include "Vertex.hpp"
#include "TextureCoord.hpp"
#include "Normal.hpp"
#include "Face.hpp"
#include "Material.hpp"
#include "Object.hpp"
#include "Program.hpp"
#include "Window.hpp"
#include "Camera.hpp"

Program *parse(const std::string filename);
void parsingChecker(Program *program);

void drawPoint(Program *program);
void drawLine(Program *program);

#endif

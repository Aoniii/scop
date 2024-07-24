#ifndef SCOP_HPP
#define SCOP_HPP

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

Program *parse(const std::string filename);
void parsingChecker(Program *program);

#endif

#include "scop.hpp"

Shader::Shader(): programID(0) {}

Shader::~Shader() {}

Shader::Shader(const std::string vertex_shader, const std::string fragment_shader) {
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_shader, std::ios::in);
    if (VertexShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    } else {
        std::cerr << "[\e[31mERROR\e[39m] Failed to open " << vertex_shader << std::endl;
        exit(1);
    }

    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_shader, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    } else {
        std::cerr << "[\e[31mERROR\e[39m] Failed to open " << fragment_shader << std::endl;
        exit(1);
    }

    const char* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);
    checkCompileErrors(VertexShaderID, "VERTEX");

    const char* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);
    checkCompileErrors(FragmentShaderID, "FRAGMENT");

    this->programID = glCreateProgram();
    glAttachShader(this->programID, VertexShaderID);
    glAttachShader(this->programID, FragmentShaderID);
    glLinkProgram(this->programID);
    checkCompileErrors(this->programID, "PROGRAM");

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
}

Shader::Shader(const Shader &shader) {
	*this = shader;
}

Shader &Shader::operator=(const Shader &shader) {
	this->programID = shader.programID;
	return (*this);
}

void Shader::use() const {
	glUseProgram(this->programID);
}

void Shader::checkCompileErrors(GLuint shader, const std::string &type) {
    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "[\e[31mERROR\e[39m] SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "[\e[31mERROR\e[39m] PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

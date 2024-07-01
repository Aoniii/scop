#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

class Shader {
	private:
		GLuint programID;

		void checkCompileErrors(GLuint shader, const std::string &type);

	public:
		Shader();
		~Shader();
		Shader(const std::string vertex_shader, const std::string fragment_shader);
		Shader(const Shader &shader);
		Shader &operator=(const Shader &shader);

		void use() const;
};

#endif

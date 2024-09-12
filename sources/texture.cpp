#include "scop.hpp"

unsigned char* loadBMP(const char* path, int& width, int& height) {
	std::ifstream file(path, std::ios::binary);
	if (!file.is_open()) {
		std::cout << "[\e[31mERROR\e[39m] File BMP cannot be opened !" << std::endl;
		return (nullptr);
	}

	unsigned char header[54];
	file.read(reinterpret_cast<char*>(header), 54);

	if (header[0] != 'B' || header[1] != 'M') {
		std::cout << "[\e[31mERROR\e[39m] Invalid file BMP !" << std::endl;
		return (nullptr);
	}

	width = header[18] + (header[19] << 8) + (header[20] << 16) + (header[21] << 24);
	height = header[22] + (header[23] << 8) + (header[24] << 16) + (header[25] << 24);

	if (width < 0)
		width = -width;
	if (height < 0)
		height = -height;

	int imageSize = 3 * width * height;

	unsigned char* data = new(std::nothrow) unsigned char[imageSize];
	file.seekg(54);
	file.read(reinterpret_cast<char*>(data), imageSize);
	file.close();

	for (int i = 0; i < imageSize; i += 3)
		std::swap(data[i], data[i + 2]);

	return (data);
}

unsigned int createTextureFromBMP(const char* path) {
	int width, height;
	unsigned char* data = loadBMP(path, width, height);
	if (!data) {
		std::cout << "[\e[31mERROR\e[39m] Loading error !" << std::endl;
		return (0);
	}

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	
	delete[] data;
	return (textureID);
}

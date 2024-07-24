#ifndef FACE_HPP
#define FACE_HPP

#include <vector>
#include <string>

class Face {
	private:
		std::vector<int> vertexIndices;
		std::vector<int> textureIndices;
		std::vector<int> normalIndices;
		std::string materialName;
		int smoothing;

	public:
		Face();
		~Face();
		Face(const Face &face);
		Face &operator=(const Face &face);

		Face(std::vector<int> vertexIndices, std::vector<int> textureIndices, std::vector<int> normalIndices, std::string materialName, int smoothing);

		std::vector<int> getVertexIndices() const;
		std::vector<int> getTextureIndices() const;
		std::vector<int> getNormalIndices() const;
		std::string getMaterialName() const;
		int getSmoothing() const;

		void setVertexIndices(std::vector<int> v);
		void setTextureIndices(std::vector<int> v);
		void setNormalIndices(std::vector<int> v);
		void setMaterialName(std::string s);
		void setSmoothing(int i);
};

#endif

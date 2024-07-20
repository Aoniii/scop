#ifndef TEXTURECOORD_HPP
#define TEXTURECOORD_HPP

class TextureCoord {
	private:
		float u;
		float v;
		float w;

	public:
		TextureCoord();
		~TextureCoord();
		TextureCoord(const TextureCoord &textureCoord);
		TextureCoord &operator=(const TextureCoord &textureCoord);

		TextureCoord(float u);
		TextureCoord(float u, float v);
		TextureCoord(float u, float v, float w);

		float getU() const;
		float getV() const;
		float getW() const;

		void setU(float u);
		void setV(float v);
		void setW(float w);
}

#endif

#include "TextureCoord.hpp"

TextureCoord::TextureCoord(): u(0.0f), v(0.0f), w(0.0f) {}

TextureCoord::~TextureCoord() {}

TextureCoord::TextureCoord(const TextureCoord &textureCoord) {
	*this = textureCoord;
}

TextureCoord &TextureCoord::operator=(const TextureCoord &textureCoord) {
	this->u = textureCoord.u;
	this->v = textureCoord.v;
	this->w = textureCoord.w;
	return (*this);
}

TextureCoord::TextureCoord(float u): u(u), v(0.0f), w(0.0f) {}

TextureCoord::TextureCoord(float u, float v): u(u), v(v), w(0.0f) {}

TextureCoord::TextureCoord(float u, float v, float w): u(u), v(v), w(w) {}

float TextureCoord::getU() const {
	return (this->u);
}

float TextureCoord::getV() const {
	return (this->V);
}

float TextureCoord::getW() const {
	return (this->w);
}

void TextureCoord::setU(float u) {
	this->u = u;
}

void TextureCoord::setV(float v) {
	this->v = v;
}

void TextureCoord::setW(float w) {
	this->w = w;
}

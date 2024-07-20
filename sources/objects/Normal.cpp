#include "Normal.hpp"

Normal::Normal(): i(0.0f), j(0.0f), k(0.0f) {}

Normal::~Normal() {}

Normal::Normal(const Normal &normal) {
	*this = normal;
}

Normal &Normal::operator=(const Normal &normal) {
	this->i = normal.i;
	this->j = normal.j;
	this->k = normal.k;
	return (*this);
}

Normal::Normal(float i, float j, float k): i(i), j(j), k(k) {}

float Normal::getI() const {
	return (this->i);
}

float Normal::getJ() const {
	return (this->j);
}

float Normal::getK() const {
	return (this->k);
}

void Normal::setI(float i) {
	this->i = i;
}

void Normal::setJ(float j) {
	this->j = j;
}

void Normal::setK(float k) {
	this->k = k;
}

#include "Material.hpp"

Material::Material(): name(""), Ns(0.0f), d(0.0f), Ni(0.0f), illum(0) {
	Ka[0] = Ka[1] = Ka[2] = 0.0f;
	Kd[0] = Kd[1] = Kd[2] = 0.0f;
	Ks[0] = Ks[1] = Ks[2] = 0.0f;
}

Material::~Material() {}

Material::Material(const Material &material) {
	*this = material;
}

Material &Material::operator=(const Material &material) {
	if (this != &material) {
		this->name = material.name;
		std::memcpy(this->Ka, material.Ka, sizeof(this->Ka));
		std::memcpy(this->Kd, material.Kd, sizeof(this->Kd));
		std::memcpy(this->Ks, material.Ks, sizeof(this->Ks));
		this->Ns = material.Ns;
		this->d = material.d;
		this->Ni = material.Ni;
		this->illum = material.illum;
	}
	return (*this);
}

std::string Material::getName() const {
	return this->name;
}

const float *Material::getKa() const {
	return this->Ka;
}

const float *Material::getKd() const {
	return this->Kd;
}

const float *Material::getKs() const {
	return this->Ks;
}

float Material::getNs() const {
	return this->Ns;
}

float Material::getD() const {
	return this->d;
}

float Material::getNi() const {
	return this->Ni;
}

int Material::getIllum() const {
	return this->illum;
}

void Material::setName(const std::string &name) {
	this->name = name;
}

void Material::setKa(const float (&Ka)[3]) {
	std::memcpy(this->Ka, Ka, sizeof(this->Ka));
}

void Material::setKd(const float (&Kd)[3]) {
	std::memcpy(this->Kd, Kd, sizeof(this->Kd));
}

void Material::setKs(const float (&Ks)[3]) {
	std::memcpy(this->Ks, Ks, sizeof(this->Ks));
}

void Material::setNs(float f) {
	this->Ns = f;
}

void Material::setD(float f) {
	this->d = f;
}

void Material::setNi(float f) {
	this->Ni = f;
}

void Material::setIllum(int i) {
	this->illum = i;
}

#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <string>
#include <cstring>

class Material {
	private:
		std::string name;
		float Ka[3];
		float Kd[3];
		float Ks[3];
		float Ns;
		float d;
		float Ni;
		int illum;

	public:
		Material();
		~Material();
		Material(const Material &material);
		Material &operator=(const Material &material);

		std::string getName() const;
		const float *getKa() const;
		const float *getKd() const;
		const float *getKs() const;
		float getNs() const;
		float getD() const;
		float getNi() const;
		int getIllum() const;

		void setName(const std::string &name);
		void setKa(const float (&Ka)[3]);
		void setKd(const float (&Kd)[3]);
		void setKs(const float (&Ks)[3]);
		void setNs(float f);
		void setD(float f);
		void setNi(float f);
		void setIllum(int i);
};

#endif

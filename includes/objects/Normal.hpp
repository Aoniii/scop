#ifndef NORMAL_HPP
#define NORMAL_HPP

class Normal {
	private:
		float i;
		float j;
		float k;

	public:
		Normal();
		~Normal();
		Normal(const Normal &normal);
		Normal &operator=(const Normal &normal);

		Normal(float i, float j, float k);

		float getI() const;
		float getJ() const;
		float getK() const;

		void setI(float i);
		void setJ(float j);
		void setK(float k);
}

#endif

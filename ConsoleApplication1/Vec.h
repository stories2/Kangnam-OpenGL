#ifndef VEC_H
#define VEC_H

class Vec {
public:
	float x;
	float y;

	Vec() : x(0), y(0) {};
	Vec(float _x, float _y) : x(_x), y(_y) {};

	Vec operator+(Vec &ref);

	Vec operator/(float val);

	float getNorm();
};

#endif // VEC_H

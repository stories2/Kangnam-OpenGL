#include "Vec.h"

Vec Vec::operator+(Vec &ref) {
	return Vec(ref.x + x, ref.y + y);
}

Vec Vec::operator/(float val) {
	return Vec(x / val, y / val);
}

float Vec::getNorm() {
	return x + y;
}
#include "Vec.h"
#include <math.h>
#include "global.h"

class Particle {
public:
	Vec position;
	Vec direction;
	Vec gravity = Vec(0, -0.1);
	float velocity;
	float viscosity;
	float density;

	Particle() :
		position(Vec(0, 0)), direction(Vec(0, 0)), velocity(0), density(0), viscosity(0.25)
	{};
	Particle(Vec _direction, float _velocity, float _viscosity, float _density) :
		direction{ _direction }, velocity(_velocity), viscosity(_viscosity), density(_density) {};

	Vec EffectDirection();

	float GetDegree(Vec dir);

	Vec Degree2Grid(float degree);

	void CalcEffectGrid(Particle grid[][SIZE], int size);

	float SpreadEffectToGrid(Particle grid[][SIZE], int size, Vec direction, float amount);
};
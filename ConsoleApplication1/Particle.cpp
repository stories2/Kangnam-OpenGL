#ifndef PARTICLE_H

#include "Vec.h"
#include "Particle.h"

#define PARTICLE_H

Vec Particle::EffectDirection() {
	Vec dir = direction + gravity;
	if (dir.x < -1)
		dir.x = -1;
	if (dir.x > 1)
		dir.x = 1;
	if (dir.y < -1)
		dir.y = -1;
	if (dir.y > 1)
		dir.y = 1;
	return dir;
}

float Particle::GetDegree(Vec dir) {
	float c = sqrt(pow(dir.x, 2) + pow(dir.y, 2));
	return acos(dir.x / c) * (180 / PI);
}

Vec Particle::Degree2Grid(float degree) {
	float degreeGap = 360.0 / 16;
	degree = degree + degreeGap;
	float degreeCnt = degreeGap;
	for (int i = 0; i < 8; i++) {
		if (degreeCnt <= degree && degree < degreeCnt + degreeGap * 2) {
			switch (i) {
			case 0:
				return Vec(1, 0);
			case 1:
				return Vec(1, -1);
			case 2:
				return Vec(0, -1);
			case 3:
				return Vec(-1, -1);
			case 4:
				return Vec(-1, 0);
			case 5:
				return Vec(-1, 1);
			case 6:
				return Vec(0, 1);
			case 7:
				return Vec(1, 1);
			}
		}
		degreeCnt += degreeGap * 2;
	}
}

void Particle::CalcEffectGrid(Particle grid[][SIZE], int size) {
	float degree = GetDegree(EffectDirection());
	for (int i = 0; i < 5; i++) {

		if (density <= 0) {
			return;
		}

		float originDensity = density;

		Vec ccw = Degree2Grid(degree + i * 360 / 8);
		float density_ccw = density * viscosity;

		density_ccw = SpreadEffectToGrid(grid, size, ccw, density_ccw);

		Vec cw = Degree2Grid(degree - i * 360 / 8);
		float density_cw = density * viscosity;

		density_cw = SpreadEffectToGrid(grid, size, cw, density_cw);

		density = density_ccw + density_cw + (originDensity - density * viscosity * 2);
	}
}

float Particle::SpreadEffectToGrid(Particle grid[][SIZE], int size, Vec direction, float amount) {
	if (direction.x + position.x < 0 || direction.x + position.x >= size
		|| direction.y + position.y < 0 || direction.y + position.y >= size) {
		return amount;
	}

	Vec newDir = grid[(int)(position.y + direction.y)][(int)(position.x + direction.x)].direction;
	grid[(int)(position.y + direction.y)][(int)(position.x + direction.x)].direction = (newDir + direction) / 2;

	grid[(int)(position.y + direction.y)][(int)(position.x + direction.x)].density += amount;
	if (grid[(int)(position.y + direction.y)][(int)(position.x + direction.x)].density > 1) {
		float overflowAmount = grid[(int)(position.y + direction.y)][(int)(position.x + direction.x)].density - 1;
		grid[(int)(position.y + direction.y)][(int)(position.x + direction.x)].density = 1;
		return overflowAmount;
	}
	return 0;
}

#endif
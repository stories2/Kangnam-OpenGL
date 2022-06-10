#pragma once

#include "Vec.h"
#include "Particle.h"
#include "global.h"

class SimulationGrid {
public:
	int size = SIZE;
	Particle grid[SIZE][SIZE];
	SimulationGrid();

	void Update();
	void Render();
};

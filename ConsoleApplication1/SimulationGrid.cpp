#ifndef SIMULATION_GRID_H

#include "SimulationGrid.h"
#include <iostream>

#define SIMULATION_GRID_H

void SimulationGrid::Update() {
	for (int i = 0; i < size; i++) {
		for (int t = 0; t < size; t++) {
			if (i == 0 && t == 2) {
				printf("debug");
			}
			if (i == 1 && t == 2) {
				printf("debug");
			}
			if (i == 2 && t == 2) {
				printf("debug");
			}
			//grid[i][t].CalcEffectGrid(grid, size);
			grid[i][t].CalcSandEffectGrid(grid, size);
		}
	}
}

void SimulationGrid::Render() {
	Update();
	Update();
	Update();
	Update();
}

SimulationGrid::SimulationGrid() {
	for (int i = 0; i < size; i++) {
		for (int t = 0; t < size; t++) {
			grid[i][t] = Particle();
			grid[i][t].position = Vec(t, i);
		}
	}
	/*
	for (int t = 0; t < size; t++) {
		grid[4][t].density = 1;
	}*/

	//grid[3][3].density = 1;
}

#endif // !SIMULATION_GRID_H

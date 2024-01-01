// ConwayGameOfLifeCpp.cpp : Defines the entry point for the application.
//

#include <ctype.h>
#include <chrono>
#include <thread>

#include "Grid.h"
#include "Life.h"
#include "Render.h"

#include "Examples.h"

constexpr Index_t WIDTH = 25;
constexpr Index_t HEIGHT = 20;

void sleep(int millis) {
	std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

int main() {
	GameOfLife<WIDTH, HEIGHT> life;
	ConsoleGridWriter<WIDTH, HEIGHT> grid;

	life.setFromObject(2, 2, ex::block);
	life.setFromObject(2, 6, ex::blinker);
	life.setFromObject(2, 12, ex::spaceship_light);

	while (true) {
		// Tick
		life.tick();

		// Update grid
		for (Index_t x = 0; x < WIDTH; x++) {
			for (Index_t y = 0; y < HEIGHT; y++) {
				grid.set(x, y, life.getState(x, y));
			}
		}

		// Render grid
		grid.render();

		sleep(100);
	}

	return 0;
}

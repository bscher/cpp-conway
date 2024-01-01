#pragma once

#include <array>
#include <iostream>

#include "Grid.h"

template<Index_t WIDTH, Index_t HEIGHT>
class ConsoleGridWriter
{
public:
	constexpr ConsoleGridWriter() {
		_grid = {};
	}

	void blank() const {
		for (int i = 0; i < HEIGHT; i++) {
			std::cout << '\n';
		}
	}

	void set(Index_t x, Index_t y, bool state) {
		if (isValidIndex(x, y))
			_grid[x][y] = state;
	}

	void render() const {
		blank();
		for (Index_t y = 0; y < HEIGHT; y++) {
			for (Index_t x = 0; x < WIDTH; x++) {
				std::cout << (_grid[x][y] ? 'X' : '.');
			}
			std::cout << '\n';
		}
		std::cout.flush();
	}

private:
	static constexpr bool isValidIndex(Index_t x, Index_t y) {
		return (
			x >= 0 && x < WIDTH &&
			y >= 0 && y < HEIGHT
		);
	}

	Grid_t<WIDTH, HEIGHT> _grid;
};
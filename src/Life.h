#pragma once

#include <array>
#include <cstddef>

#include "Grid.h"

template<Index_t WIDTH, Index_t HEIGHT>
class GameOfLife {
private:
	using Board_t = std::array<std::array<bool, HEIGHT>, WIDTH>;

	static constexpr bool isValidIndex(Index_t x, Index_t y) {
		return (
			x >= 0 && x < WIDTH &&
			y >= 0 && y < HEIGHT
		);
	}

public:
	constexpr GameOfLife() {
		_board = _boardNext = { 0 };
		_modifyNextBoardInstead = false;
	}

	template<typename TwoDimensionalArray_t>
	void setFromObject(Index_t x, Index_t y, const TwoDimensionalArray_t& obj, bool inverseDimensions = false) {
		for (Index_t ix = 0; ix < (sizeof(obj) / sizeof(obj[0])); ix++) {
			for (Index_t iy = 0; iy < (sizeof(obj[0]) / sizeof(obj[0][0])); iy++) {
				if (inverseDimensions) {
					setState(x + ix, y + iy, obj[ix][iy]);
				}
				else {
					setState(x + ix, y + iy, obj[iy][ix]);
				}
			}
		}
	}

	void tick() {
		_modifyNextBoardInstead = true;
		_boardNext = _board;
		for (Index_t x = 0; x < WIDTH; x++) {
			for (Index_t y = 0; y < HEIGHT; y++) {

				const bool isAlive = getState(x, y);
				const Count_t numLivingNeighbors = countLivingNeighbors(x, y);

				if (isAlive) {
					//1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
					if (numLivingNeighbors < 2)
						kill(x, y);

					//2. Any live cell with two or three live neighbours lives on to the next generation.
					if (numLivingNeighbors == 2 || numLivingNeighbors == 3)
						continue;

					//3. Any live cell with more than three live neighbours dies, as if by overpopulation.
					if (numLivingNeighbors > 3)
						kill(x, y);
				}
				else { // (!isAlive(x, y))
				 //4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
					if (numLivingNeighbors == 3)
						populate(x, y);
				}
			}
		}
		_modifyNextBoardInstead = false;
		_board = _boardNext;
	}

	void kill(Index_t x, Index_t y) {
		setState(x, y, false);
	}

	void populate(Index_t x, Index_t y) {
		setState(x, y, true);
	}

	constexpr Count_t countLivingNeighbors(Index_t x, Index_t y) const {
		Count_t livingNeighbors = 0;
		for (Index_t ix = x - 1; ix <= x + 1; ix++) {
			for (Index_t iy = y - 1; iy <= y + 1; iy++) {
				if (ix != x || iy != y) {
					livingNeighbors += (Count_t)getState(ix, iy);
				}
			}
		}
		return livingNeighbors;
	}

	constexpr bool getState(Index_t x, Index_t y) const {
		if (!isValidIndex(x, y))
			return false; // Invalid index, assume not alive
		return _board[x][y];
	}

	void setState(Index_t x, Index_t y, bool alive) {
		if (!isValidIndex(x, y))
			return; // Invalid index, skip
		if (_modifyNextBoardInstead) {
			_boardNext[x][y] = alive;
		} else {
			_board[x][y] = alive;
		}
	}

private:
	bool _modifyNextBoardInstead;
	Board_t _board;
	Board_t _boardNext;
};
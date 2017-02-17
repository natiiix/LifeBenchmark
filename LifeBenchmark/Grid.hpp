#pragma once

#include <stdlib.h>

// Used to store the game field
class Grid
{
public:
	// Initializes a new instance of grid with default size
	Grid(void);
	// Performs an iteration on the grid
	void PerformIteration(void);

private:
	static const unsigned DEFAULT_SIZE = 256;
	bool m_cells[DEFAULT_SIZE][DEFAULT_SIZE];
	// Returns true if the cell [x, y] should live in the next iteration
	bool cellIsViable(const unsigned & x, const unsigned & y) const;
};

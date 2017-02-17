#include "Grid.hpp"

Grid::Grid(void)
{
	for (unsigned iy = 0; iy < DEFAULT_SIZE; iy++)
		for (unsigned ix = 0; ix < DEFAULT_SIZE; ix++)
			m_cells[ix][iy] = ((rand() % 2) == 1);
}

void Grid::PerformIteration(void)
{
	static bool tmpCells[DEFAULT_SIZE][DEFAULT_SIZE];

	for (unsigned iy = 0; iy < DEFAULT_SIZE; iy++)
		for (unsigned ix = 0; ix < DEFAULT_SIZE; ix++)
			tmpCells[ix][iy] = cellIsViable(ix, iy);

	for (unsigned iy = 0; iy < DEFAULT_SIZE; iy++)
		for (unsigned ix = 0; ix < DEFAULT_SIZE; ix++)
			m_cells[ix][iy] = tmpCells[ix][iy];
}

bool Grid::cellIsViable(const unsigned & x, const unsigned & y) const
{
	unsigned livingNeighbors = 0;

	for (unsigned iy = (y == 0 ? y : y - 1); iy < DEFAULT_SIZE && iy < y + 2; iy++)
		for (unsigned ix = (x == 0 ? x : x - 1); ix < DEFAULT_SIZE && ix < x + 2; ix++)
			if ((ix != x || iy != y) && m_cells[ix][iy])
				livingNeighbors++;

	if (livingNeighbors == 3)
		return true;
	else if (livingNeighbors == 2)
		return m_cells[x][y];
	else
		return false;
}

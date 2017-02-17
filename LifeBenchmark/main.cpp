#include "Grid.hpp"

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

static const unsigned HARDWARE_CONCURRENCY = std::thread::hardware_concurrency();
static const unsigned THREAD_MULITPLIER = 4;
static const unsigned ITERATIONS_PER_THREAD = 1024;
static const double SCORE_FACTOR = 1e13;

void GameOfLife(void)
{
	Grid g;

	for (unsigned i = 0; i < ITERATIONS_PER_THREAD; i++)
		g.PerformIteration();
}

int main(void)
{
	std::vector<std::thread> vt;
	std::chrono::steady_clock clock;
	std::chrono::time_point<std::chrono::steady_clock> timeStart;
	std::chrono::time_point<std::chrono::steady_clock> timeEnd;

	std::cout << std::endl << " Press any key to start the benchmark...";

	std::cin.clear();
	std::cin.sync();
	std::cin.get();

#ifdef _WIN32
	system("cls");
#else
	std::cout << std::endl << std::endl;
#endif // _WIN32

	std::cout << std::endl
		<< "  |=-----------------=|" << std::endl
		<< "  |                   |" << std::endl
		<< "  |     Running...    |" << std::endl
		<< "  |                   |" << std::endl
		<< "  |=-----------------=|" << std::endl << std::endl;

	timeStart = clock.now();

	for (unsigned i = 0; i < HARDWARE_CONCURRENCY * THREAD_MULITPLIER; i++)
		vt.push_back(std::thread(GameOfLife));

	while (!vt.empty())
	{
		vt.back().join();
		vt.pop_back();
	}

	timeEnd = clock.now();

	double score = (SCORE_FACTOR * HARDWARE_CONCURRENCY) / (timeEnd - timeStart).count();

#ifdef _WIN32
	system("cls");
#else
	std::cout << std::endl << std::endl;
#endif // _WIN32

	std::cout << std::endl << std::endl << "  ---=> Score: " << score << " <=---"
		<< std::endl << std::endl << std::endl << std::endl << " Press any key to exit...";

	std::cin.clear();
	std::cin.sync();
	std::cin.get();

	return 0;
}

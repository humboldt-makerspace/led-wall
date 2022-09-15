#include "utils/Mapping.hpp"
#include "system/Interface.hpp"

int Mapping::getBlock(int y)
{
	switch (y) {
		case 0 ... 5: return 0;
		case 6 ... 11: return 1;
		case 12 ... 17: return 2;
		default: return -1;
	}
}

int Mapping::getPos(int x, int y)
{
	switch (y) {
		case 0: return x;
		case 1: return 2 * WALL_WIDTH - 1 - x;
		case 2: return 2 * WALL_WIDTH + x;
		case 3: return 4 * WALL_WIDTH - 1 - x;
		case 4: return 4 * WALL_WIDTH + x;
		case 5: return 6 * WALL_WIDTH - 1 - x;
		case 6: return x;
		case 7: return 2 * WALL_WIDTH - 1 - x;
		case 8: return 2 * WALL_WIDTH + x;
		case 9: return 4 * WALL_WIDTH - 1 - x;
		case 10: return 4 * WALL_WIDTH + x;
		case 11: return 6 * WALL_WIDTH - 1 - x;
		case 12: return x;
		case 13: return 2 * WALL_WIDTH - 1 - x;
		case 14: return 2 * WALL_WIDTH + x;
		case 15: return 4 * WALL_WIDTH - 1 - x;
		case 16: return 4 * WALL_WIDTH + x;
		case 17: return 6 * WALL_WIDTH - 1 - x;
		default: return -1;
	}
}

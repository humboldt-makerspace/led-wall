#ifndef GEOM_H
#define GEOM_H

#include "system/Interface.hpp"

typedef struct point {
	int x;
	int y;
} Point;

typedef struct dot {
	Point p;
	Point last[LAST_FIELDS_NUM];
	int outCounter;
	int bufferIndex;
	Side origin;
} Dot;

#endif

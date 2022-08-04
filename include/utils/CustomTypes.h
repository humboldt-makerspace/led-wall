#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

#include "constants.h"

typedef struct point {
	int x;
	int y;
} Point;

typedef struct dot {
	Point p;
	Point last[LAST_FIELDS_NUM];
	int outCounter;
	int bufferIndex;
	Direction dir;
} Dot;

typedef struct msgFormat {
	int endInd1;
	int endInd2;
	int pos1;
	int pos2; 
} Format;

#endif

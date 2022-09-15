#ifndef CUSTOM_TYPES_H
#define CUSTOM_TYPES_H

#include "constants.h"

struct point_t {
	int x;
	int y;
};

struct dot_t {
	point_t p;
	point_t last[LAST_FIELDS_NUM];
	int outCounter;
	int bufferIndex;
	direction_t dir;
};

struct msg_format_t {
	int endInd1;
	int endInd2;
	int pos1;
	int pos2;
};

#endif

#ifndef PGM_H

#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>

struct PGM {
	size_t ncols; //number of columns
	size_t nrows;  //number of rows
	
	//always 0 to 255, so we do not need to read it
	//size_t max_grey; //max greyscale value of a pixel
	
	uint8_t* pixels; // (ncols * nrows) bytes
	
	struct PGM* succ;
	bool is_succ;
};

struct PGM* pgm_ctor(size_t ncols, size_t nrows);

void pgm_dtor(struct PGM* pgm);

struct PGM* pgm_read(FILE* fin);

void pgm_write(FILE* fout, struct PGM* pgm);

bool pgm_rows_match(struct PGM* p1, struct PGM* p2);

#endif

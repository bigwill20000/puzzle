#include <stdlib.h>
#include <string.h>

#include "pgm.h"

struct PGM* pgm_ctor(size_t ncols, size_t nrows){
	
	struct PGM* res = malloc(sizeof(struct PGM));
	res->ncols = ncols;
	res->nrows = nrows;
	
	res->pixels = malloc(sizeof(uint8_t)*nrows*ncols);
	
	res->succ = NULL;
	res->is_succ = false;
	
	return res;
}

void pgm_dtor(struct PGM* pgm){
	
	free(pgm->pixels);
	free(pgm);
}

struct PGM* pgm_read(FILE* fin){
	
	char format[10];
	
	fscanf(fin, "%9s\n", format);
	
	if(strcmp(format, "P2") != 0){
		return NULL;
	}
		
	int ncols; int nrows;
	fscanf(fin, "%d %d\n", &ncols, &nrows);
	
	struct PGM* res = pgm_ctor(ncols, nrows);
	
	fscanf(fin, "255\n");
	
	for(int row=0; row < nrows; row++){
		
		for(int col=0; col < ncols; col++){
			
			fscanf(fin, "%hhd ", &res->pixels[row * ncols + col]);
		}
		
		fscanf(fin,"\n");
	}
	
	return res;
}

void pgm_write(FILE* fout, struct PGM* pgm){
	
	fprintf(fout, "P2\n");
	
	fprintf(fout, "%ld %ld\n", pgm->ncols, pgm->nrows);
	
	fprintf(fout, "255\n");
	
	for(int row=0; row < pgm->nrows; row++){
		
		for(int col=0; col < pgm->ncols; col++){
			
			fprintf(fout, "%d ", pgm->pixels[row * pgm->ncols + col]);
		}
		
		fprintf(fout,"\n");
	}
}

bool pgm_rows_match(struct PGM* p1, struct PGM* p2){

	for(int k=0;k < p1->ncols;k++){
				
		const size_t index = (p1->nrows-1) * p1->ncols;
		
		if(p1->pixels[index+k] != p2->pixels[k]){
			
			return false;
		}
	}
	
	return true;
}

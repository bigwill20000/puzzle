#include <stdbool.h>
#include <stddef.h>
#include <inttypes.h>

#include "pgm.h"
#include "puzzle.h"

struct PGM* puzzle_complete(struct PGM** slices, size_t nslices){
	
	//each slice has at least one of either the top or bottom row matching
	//the top or bottom row of another slice.
	
	//we can find the successor of each slice in O(n) if it exists
	//meaning O(n*n) for the whole thing which is good enough 
	//since runtime gives no points in this course,
	//so i wont waste my time finding optimal solution.
	
	//next problem is to find the first slice. simply the slice s2 which has no
	//slice s1 with s1->succ = s2
	
	//we keep track of that with slice->is_succ which means that
	//it has a successor. later we find first slice in O(n)
	
	puzzle_find_successors(slices, nslices);
	
	struct PGM* top = NULL;
	
	int nrows_total = -(nslices - 1);
	
	for(int i=0;i < nslices; i++){
		
		struct PGM* slice = slices[i];
		
		if(!slice->is_succ)
			top = slice;
			
		nrows_total += slice->nrows;
	}
	
	//make an image with the result
	struct PGM* res = pgm_ctor(slices[0]->ncols, nrows_total);
	
	puzzle_stitch(top, res);
	
	return res;
}

void puzzle_stitch(struct PGM* top, struct PGM* res){
	
	int row_index = 0;
	
	struct PGM* current = top;
	
	while(current != NULL){
		
		const bool is_last = current->succ == NULL;
		
		int nrows = current->nrows;
		
		//if it is not the last slice, we don't write the last row
		if(!is_last) 
			nrows--;
		
		//write the slice to result
		for(int row=0; row < nrows; row++){
			for(int col=0;col < res->ncols; col++){
				
				uint8_t pixel = current->pixels[(current->ncols * row) + col];
				
				size_t index = (res->ncols * row_index) + col;
				
				res->pixels[index] = pixel;
			}
			
			row_index++;
		}
		
		current = current->succ;
	}
}

void puzzle_find_successors(struct PGM** slices, size_t nslices){
	
	for(int i=0;i < nslices; i++){
		
		struct PGM* slice = slices[i];
		
		for(int j=0;j < nslices; j++){
			
			if(j==i) continue;
			
			struct PGM* candidate = slices[j];
			
			//check if slices[i] bottom row matches slices[j] top row
			
			const bool rows_match = pgm_rows_match(slice, candidate);
			
			if(rows_match){
				
				slice->succ = candidate;
				candidate->is_succ = true;
				break;
			}
		}
	}
}

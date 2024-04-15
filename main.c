#include <stdio.h>
#include <stdlib.h>

#include "puzzle.h"
#include "pgm.h"

int main(int argc, char** argv){
	
	if(argc < 3){
		fprintf(stderr, "Ungenuegende Argumente. Mindestens eine Eingabedatei und eine Ausgabedatei erforderlich.\n");
		return EXIT_ERR_INSUFFICIENT_PARAMETERS;
	}
	
	size_t nslices = argc-2;
	
	struct PGM** slices = malloc(sizeof(struct PGM*)*nslices);
	
	//eingabedateien lesen
	for(int i=0;i < nslices;i++){
		
		FILE* fin = fopen(argv[i+1], "r");
		
		if(fin == NULL){
			fprintf(stderr, "konnte die eingabedatei %s nicht lesen\n", argv[i+1]);
			
			//free all slices up to that point
			for(int j=0;j < i;j++){
				pgm_dtor(slices[j]);
			}
			free(slices);
			return EXIT_ERR_FILES;
		}
		
		slices[i] = pgm_read(fin);
		
		if(slices[i] == NULL){
			
			//'P2' was not the first line in the file
			fprintf(stderr, "PGM format nicht eingehalten. 'P2' steht nicht in erster zeile\n");
			fclose(fin);
			
			//free all slices up to that point
			for(int j=0;j < i;j++){
				pgm_dtor(slices[j]);
			}
			free(slices);
			
			return EXIT_ERR_PGM_FORMAT;
		}
		
		fclose(fin);
	}
	
	//bilder zusammenfuegen
	struct PGM* res = puzzle_complete(slices, nslices);
	
	//free all slices
	for(int i=0;i < nslices;i++){
		pgm_dtor(slices[i]);
	}
	free(slices);
	
	//ausgabe schreiben
	FILE* fout = fopen(argv[argc-1],"w");
	
	if(fout == NULL){
		
		pgm_dtor(res);
		fprintf(stderr, "konnte die ausgabedatei %s nicht oeffnen.\n", argv[argc-1]);
		return EXIT_ERR_FILES;
	}
	
	pgm_write(fout, res);
	
	pgm_dtor(res);
	
	fclose(fout);
	
	return EXIT_SUCCESS;
}

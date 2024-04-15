#ifndef PUZZLE_H 

#include <stdbool.h>

#define EXIT_SUCCESS 0
#define EXIT_ERR_INSUFFICIENT_PARAMETERS 1
#define EXIT_ERR_FILES 2
#define EXIT_ERR_PGM_FORMAT 3

struct PGM* puzzle_complete(struct PGM** slices, size_t nslices);

void puzzle_find_successors(struct PGM** slices, size_t nslices);

void puzzle_stitch(struct PGM* top, struct PGM* res);

#endif

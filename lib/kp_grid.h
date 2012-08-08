#ifndef _KP_GRID_H_
#define _KP_GRID_H_

#include <stdbool.h>

extern int kp_grid_lineno; /* from lexer */
extern FILE *kp_grid_in;
extern int kp_grid_parse();
extern int kp_grid_lex();

#endif

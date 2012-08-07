#ifndef _KP_MESH_H_
#define _KP_MESH_H_

#include <stdbool.h>

extern int kp_mesh_lineno; /* from lexer */
extern FILE *kp_mesh_in;
extern int kp_mesh_parse();
extern int kp_mesh_lex();

#endif

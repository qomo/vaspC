#ifndef _KP_LINE_H_
#define _KP_LINE_H_

#include <stdbool.h>

extern int kp_line_lineno; /* from lexer */
extern FILE *kp_line_in;
extern int kp_line_parse();
extern int kp_line_lex();

#endif

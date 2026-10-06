#ifndef PARSER_H
#define PARSER_H

#include "AST.h"
#include "Lexer.h"

void parser_init(void);
ASTNode *parse(void);

#endif

#ifndef AST_H
#define AST_H

typedef enum {
  AST_PROGRAM,
  AST_PRINT,
  AST_STRING,
  AST_NUMBER,
  AST_IDENTIFIER
} ASTType;

typedef struct ASTNode {
  ASTType type;
  char *value;

  struct ASTNode *child;
  struct ASTNode *next;
} ASTNode;

ASTNode *ast_create(ASTType type, const char *value);

void ast_add_child(ASTNode *parent, ASTNode *child);

void ast_print(ASTNode *node, int depth);

void ast_free(ASTNode *node);

#endif

#include "AST.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ASTNode *ast_create(ASTType type, const char *value) {
  ASTNode *node = malloc(sizeof(ASTNode));

  if (node == NULL) {
    return NULL;
  }

  node->type = type;
  node->child = NULL;
  node->next = NULL;
  node->value = NULL;

  if (value != NULL) {
    node->value = malloc(strlen(value) + 1);

    if (node->value == NULL) {
      free(node);
      return NULL;
    }

    strcpy(node->value, value);
  }

  return node;
}

void ast_add_child(ASTNode *parent, ASTNode *child) {
  if (parent == NULL || child == NULL) {
    return;
  }

  if (parent->child == NULL) {
    parent->child = child;
    return;
  }

  ASTNode *current = parent->child;

  while (current->next != NULL) {
    current = current->next;
  }

  current->next = child;
}

static const char *ast_type_name(ASTType type) {
  switch (type) {
  case AST_PROGRAM:
    return "Program";

  case AST_PRINT:
    return "PrintStatement";

  case AST_STRING:
    return "StringLiteral";

  case AST_NUMBER:
    return "NumberLiteral";

  case AST_IDENTIFIER:
    return "Identifier";
  }

  return "Unknown";
}

void ast_print(ASTNode *node, int depth) {
  if (node == NULL) {
    return;
  }

  for (int i = 0; i < depth; i++) {
    printf("    ");
  }

  printf("%s", ast_type_name(node->type));

  if (node->value != NULL) {
    printf(" (%s)", node->value);
  }

  printf("\n");

  ast_print(node->child, depth + 1);
  ast_print(node->next, depth);
}

void ast_free(ASTNode *node) {
  if (node == NULL) {
    return;
  }

  ast_free(node->child);
  ast_free(node->next);

  free(node->value);
  free(node);
}

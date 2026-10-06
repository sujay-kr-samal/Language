#include "Interpreter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void evaluate(ASTNode *node) {
  if (node == NULL) {
    return;
  }

  switch (node->type) {

  case AST_STRING:
    if (node->value != NULL) {
      size_t length = strlen(node->value);

      if (length >= 2 && node->value[0] == '"' &&
          node->value[length - 1] == '"') {

        printf("%.*s", (int)(length - 2), node->value + 1);
      } else {
        printf("%s", node->value);
      }
    }
    break;

  case AST_NUMBER:
    if (node->value != NULL) {
      printf("%s", node->value);
    }
    break;

  case AST_IDENTIFIER:
    fprintf(stderr, "Runtime error: undefined identifier '%s'\n", node->value);
    exit(EXIT_FAILURE);

  default:
    fprintf(stderr, "Runtime error: cannot evaluate this node.\n");
    exit(EXIT_FAILURE);
  }
}

static void execute(ASTNode *node) {
  if (node == NULL) {
    return;
  }

  switch (node->type) {

  case AST_PRINT:
    evaluate(node->child);
    printf("\n");
    break;

  default:
    fprintf(stderr, "Runtime error: unknown statement.\n");
    exit(EXIT_FAILURE);
  }
}

void interpret(ASTNode *program) {
  if (program == NULL) {
    return;
  }

  if (program->type != AST_PROGRAM) {
    fprintf(stderr, "Runtime error: expected program AST.\n");
    exit(EXIT_FAILURE);
  }

  ASTNode *statement = program->child;

  while (statement != NULL) {
    execute(statement);
    statement = statement->next;
  }
}

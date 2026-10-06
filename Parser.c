#include "Parser.h"

#include <stdio.h>
#include <stdlib.h>

static Token current;
static Token previous;

static void advance_parser(void) {
  previous = current;
  current = lexer_next();
}

static int check(TokenType type) { return current.type == type; }

static int match(TokenType type) {
  if (!check(type)) {
    return 0;
  }

  advance_parser();
  return 1;
}

static void error(const char *message) {
  fprintf(stderr, "Parser error at line %d: %s\n", current.line, message);

  exit(EXIT_FAILURE);
}

static void consume(TokenType type, const char *message) {
  if (check(type)) {
    advance_parser();
    return;
  }

  error(message);
}

static ASTNode *expression(void) {
  if (match(TOKEN_STRING)) {
    return ast_create(AST_STRING, previous.lexeme);
  }

  if (match(TOKEN_NUMBER)) {
    return ast_create(AST_NUMBER, previous.lexeme);
  }

  if (match(TOKEN_IDENTIFIER)) {
    return ast_create(AST_IDENTIFIER, previous.lexeme);
  }

  error("Expected expression.");

  return NULL;
}

static ASTNode *print_statement(void) {
  consume(TOKEN_LEFT_PAREN, "Expected '(' after print.");

  ASTNode *value = expression();

  consume(TOKEN_RIGHT_PAREN, "Expected ')' after expression.");

  consume(TOKEN_SEMICOLON, "Expected ';' after print statement.");

  ASTNode *print = ast_create(AST_PRINT, NULL);

  if (print == NULL) {
    fprintf(stderr, "Could not allocate AST node.\n");
    exit(EXIT_FAILURE);
  }

  ast_add_child(print, value);

  return print;
}

void parser_init(void) {
  current.type = TOKEN_ERROR;
  current.lexeme = NULL;
  current.line = 0;

  previous.type = TOKEN_ERROR;
  previous.lexeme = NULL;
  previous.line = 0;

  current = lexer_next();
}

ASTNode *parse(void) {
  ASTNode *program = ast_create(AST_PROGRAM, NULL);

  if (program == NULL) {
    fprintf(stderr, "Could not allocate AST.\n");
    exit(EXIT_FAILURE);
  }

  while (!check(TOKEN_EOF)) {

    if (match(TOKEN_PRINT)) {
      ASTNode *statement = print_statement();

      ast_add_child(program, statement);
    } else {
      error("Expected statement.");
    }
  }

  return program;
}

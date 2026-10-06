#ifndef LEXER_H
#define LEXER_H

typedef enum {
  TOKEN_EOF,

  TOKEN_LEFT_PAREN,
  TOKEN_RIGHT_PAREN,
  TOKEN_LEFT_BRACE,
  TOKEN_RIGHT_BRACE,
  TOKEN_COMMA,
  TOKEN_DOT,
  TOKEN_SEMICOLON,

  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_STAR,
  TOKEN_SLASH,

  TOKEN_EQUAL,
  TOKEN_EQUAL_EQUAL,
  TOKEN_BANG,
  TOKEN_BANG_EQUAL,
  TOKEN_LESS,
  TOKEN_LESS_EQUAL,
  TOKEN_GREATER,
  TOKEN_GREATER_EQUAL,

  TOKEN_IDENTIFIER,
  TOKEN_STRING,
  TOKEN_NUMBER,

  TOKEN_MANIFEST,
  TOKEN_CONSTVESSEL,
  TOKEN_PRINT,

  TOKEN_ERROR
} TokenType;

typedef struct {
  TokenType type;
  char *lexeme;
  int line;
} Token;

void lexer_init(const char *source);
Token lexer_next(void);
void token_free(Token *token);
const char *token_type_name(TokenType type);

#endif

#include "Lexer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *source;
static size_t current;
static size_t start;
static int line;

void lexer_init(const char *input) {
  source = input;
  current = 0;
  start = 0;
  line = 1;
}

static char advance(void) { return source[current++]; }

static char peek(void) { return source[current]; }

static char peek_next(void) {
  if (source[current] == '\0')
    return '\0';

  return source[current + 1];
}

static int is_at_end(void) { return source[current] == '\0'; }

static int match(char expected) {
  if (is_at_end())
    return 0;

  if (source[current] != expected)
    return 0;

  current++;
  return 1;
}

static char *copy_lexeme(void) {
  size_t length = current - start;

  char *text = malloc(length + 1);

  if (text == NULL)
    return NULL;

  memcpy(text, source + start, length);
  text[length] = '\0';

  return text;
}

static Token make_token(TokenType type) {
  Token token;

  token.type = type;
  token.lexeme = copy_lexeme();
  token.line = line;

  return token;
}

static Token error_token(const char *message) {
  Token token;

  token.type = TOKEN_ERROR;
  token.lexeme = malloc(strlen(message) + 1);
  token.line = line;

  if (token.lexeme != NULL)
    strcpy(token.lexeme, message);

  return token;
}

static void skip_whitespace(void) {
  while (!is_at_end()) {
    char c = peek();

    switch (c) {
    case ' ':
    case '\r':
    case '\t':
      advance();
      break;

    case '\n':
      line++;
      advance();
      break;

    case '/':
      if (peek_next() == '/') {
        while (peek() != '\n' && !is_at_end())
          advance();
      } else {
        return;
      }
      break;

    default:
      return;
    }
  }
}

static Token string_token(void) {
  while (peek() != '"' && !is_at_end()) {
    if (peek() == '\n')
      line++;

    advance();
  }

  if (is_at_end())
    return error_token("Unterminated string.");

  advance();

  return make_token(TOKEN_STRING);
}

static int is_identifier_start(char c) {
  return isalpha((unsigned char)c) || c == '_';
}

static int is_identifier_part(char c) {
  return isalnum((unsigned char)c) || c == '_';
}

static TokenType identifier_type(void) {
  size_t length = current - start;

  if (length == 7 && strncmp(source + start, "manifest", 7) == 0)
    return TOKEN_MANIFEST;

  if (length == 10 && strncmp(source + start, "constvessel", 10) == 0)
    return TOKEN_CONSTVESSEL;

  if (length == 5 && strncmp(source + start, "print", 5) == 0)
    return TOKEN_PRINT;

  return TOKEN_IDENTIFIER;
}

static Token identifier_token(void) {
  while (is_identifier_part(peek()))
    advance();

  return make_token(identifier_type());
}

static Token number_token(void) {
  while (isdigit((unsigned char)peek()))
    advance();

  if (peek() == '.' && isdigit((unsigned char)peek_next())) {

    advance();

    while (isdigit((unsigned char)peek()))
      advance();
  }

  return make_token(TOKEN_NUMBER);
}

Token lexer_next(void) {
  skip_whitespace();

  start = current;

  if (is_at_end())
    return make_token(TOKEN_EOF);

  char c = advance();

  if (is_identifier_start(c))
    return identifier_token();

  if (isdigit((unsigned char)c))
    return number_token();

  if (c == '"')
    return string_token();

  switch (c) {
  case '(':
    return make_token(TOKEN_LEFT_PAREN);

  case ')':
    return make_token(TOKEN_RIGHT_PAREN);

  case '{':
    return make_token(TOKEN_LEFT_BRACE);

  case '}':
    return make_token(TOKEN_RIGHT_BRACE);

  case ',':
    return make_token(TOKEN_COMMA);

  case '.':
    return make_token(TOKEN_DOT);

  case ';':
    return make_token(TOKEN_SEMICOLON);

  case '+':
    return make_token(TOKEN_PLUS);

  case '-':
    return make_token(TOKEN_MINUS);

  case '*':
    return make_token(TOKEN_STAR);

  case '/':
    return make_token(TOKEN_SLASH);

  case '=':
    return make_token(match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);

  case '!':
    return make_token(match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);

  case '<':
    return make_token(match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);

  case '>':
    return make_token(match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);

  default:
    return error_token("Unexpected character.");
  }
}

void token_free(Token *token) {
  free(token->lexeme);
  token->lexeme = NULL;
}

const char *token_type_name(TokenType type) {
  switch (type) {
  case TOKEN_EOF:
    return "EOF";

  case TOKEN_LEFT_PAREN:
    return "LEFT_PAREN";
  case TOKEN_RIGHT_PAREN:
    return "RIGHT_PAREN";
  case TOKEN_LEFT_BRACE:
    return "LEFT_BRACE";
  case TOKEN_RIGHT_BRACE:
    return "RIGHT_BRACE";
  case TOKEN_COMMA:
    return "COMMA";
  case TOKEN_DOT:
    return "DOT";
  case TOKEN_SEMICOLON:
    return "SEMICOLON";

  case TOKEN_PLUS:
    return "PLUS";
  case TOKEN_MINUS:
    return "MINUS";
  case TOKEN_STAR:
    return "STAR";
  case TOKEN_SLASH:
    return "SLASH";

  case TOKEN_EQUAL:
    return "EQUAL";
  case TOKEN_EQUAL_EQUAL:
    return "EQUAL_EQUAL";
  case TOKEN_BANG:
    return "BANG";
  case TOKEN_BANG_EQUAL:
    return "BANG_EQUAL";
  case TOKEN_LESS:
    return "LESS";
  case TOKEN_LESS_EQUAL:
    return "LESS_EQUAL";
  case TOKEN_GREATER:
    return "GREATER";
  case TOKEN_GREATER_EQUAL:
    return "GREATER_EQUAL";

  case TOKEN_IDENTIFIER:
    return "IDENTIFIER";
  case TOKEN_STRING:
    return "STRING";
  case TOKEN_NUMBER:
    return "NUMBER";

  case TOKEN_MANIFEST:
    return "MANIFEST";
  case TOKEN_CONSTVESSEL:
    return "CONSTVESSEL";
  case TOKEN_PRINT:
    return "PRINT";

  case TOKEN_ERROR:
    return "ERROR";
  }

  return "UNKNOWN";
}

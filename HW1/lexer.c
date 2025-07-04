#include "compiler.h"

#define TMAX 10000000
#define LMAX 100

char *typeName[6] = {"Id", "Int", "Keyword", "Literal", "Char", "Op"};
char code[TMAX], *p;
char strTable[TMAX], *strTableEnd = strTable;
char *tokens[TMAX], tokenTop = 0, tokenIdx = 0, token[LMAX];

char *scan() {
  while (isspace(*p)) p++;

  char *start = p;
  int type;
  if (*p == '\0') return NULL;
  if (*p == '"') {
    p++;
    while (*p != '"') p++;
    p++;
    type = Literal;
  } else if (*p >= '0' && *p <= '9') {
    while (*p >= '0' && *p <= '9') p++;
    type = Int;
  } else if (isAlpha(*p) || *p == '_') {
    while (isAlpha(*p) || isDigit(*p) || *p == '_') p++;
    type = Id;
  } else if (strchr("+-*/%%&|<>!=", *p) >= 0) {
    char c = *p++;
    if (*p == '=') p++;
    else if (strchr("+-&|", c) >= 0 && *p == c) p++;
    type = Op;
  } else {
    p++;
    type = Char;
  }
  int len = p - start;
  strncpy(token, start, len);
  token[len] = '\0';
  return token;
}

void lex(char *code) {
  printf("========== lex ==============\n");
  p = code;
  tokenTop = 0;
  while (1) {
    char *tok = scan();
    if (tok == NULL) break;
    strcpy(strTableEnd, tok);
    tokens[tokenTop++] = strTableEnd;
    strTableEnd += (strlen(tok) + 1);
    printf("token=%s\n", tok);
  }
}

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct AST AST; // Forward reference

struct AST {
  enum {
    AST_MAIN,
    AST_NUMBER,
    AST_LETTER,
    AST_ADD,
    AST_MUL,
    AST_DIV,  // Adicionando a tag para a divisão
  } tag;
  union {
    struct AST_MAIN { AST *body; } AST_MAIN;
    struct AST_NUMBER { int number; } AST_NUMBER;
    struct AST_LETTER { char letter; } AST_LETTER;
    struct AST_ADD { AST *left; AST *right; } AST_ADD;
    struct AST_MUL { AST *left; AST *right; } AST_MUL;
    struct AST_DIV { AST *left; AST *right; } AST_DIV;  // Adicionando o campo para divisão
  } data;
};

AST *ast_new(AST ast) {
  AST *ptr = malloc(sizeof(AST));
  if (ptr) *ptr = ast;
  return ptr;
}

void ast_free(AST *ptr) {
  AST ast = *ptr;
  switch (ast.tag) {
    case AST_MAIN: {
      struct AST_MAIN data = ast.data.AST_MAIN;
      ast_free(data.body);
      break;
    }
    case AST_NUMBER: {
      struct AST_NUMBER data = ast.data.AST_NUMBER;
      break;
    }
    case AST_LETTER: {
      struct AST_LETTER data = ast.data.AST_LETTER;
      break;
    }
    case AST_ADD: {
      struct AST_ADD data = ast.data.AST_ADD;
      ast_free(data.left);
      ast_free(data.right);
      break;
    }
    case AST_MUL: {
      struct AST_MUL data = ast.data.AST_MUL;
      ast_free(data.left);
      ast_free(data.right);
      break;
    }
    case AST_DIV: {
      struct AST_DIV data = ast.data.AST_DIV;
      ast_free(data.left);
      ast_free(data.right);
      break;
    }
  }
  free(ptr);
}

#define AST_NEW(tag, ...) ast_new((AST){tag, {.tag=(struct tag){__VA_ARGS__}}})

void ast_print_tree(AST *ptr, int depth) {
  if (ptr == NULL) return;

  AST ast = *ptr;
  for (int i = 0; i < depth; ++i) {
    printf("  ");
  }
  
  switch (ast.tag) {
    case AST_MAIN: {
      printf("MAIN\n");
      struct AST_MAIN data = ast.data.AST_MAIN;
      ast_print_tree(data.body, depth + 1);
      break;
    }
    case AST_NUMBER: {
      printf("NUMBER: %d\n", ast.data.AST_NUMBER.number);
      break;
    }
    case AST_LETTER: {
      printf("LETTER: %c\n", ast.data.AST_LETTER.letter);
      break;
    }
    case AST_ADD: {
      printf("ADD\n");
      struct AST_ADD data = ast.data.AST_ADD;
      ast_print_tree(data.left, depth + 1);
      ast_print_tree(data.right, depth + 1);
      break;
    }
    case AST_MUL: {
      printf("MUL\n");
      struct AST_MUL data = ast.data.AST_MUL;
      ast_print_tree(data.left, depth + 1);
      ast_print_tree(data.right, depth + 1);
      break;
    }
    case AST_DIV: {
      printf("DIV\n");
      struct AST_DIV data = ast.data.AST_DIV;
      ast_print_tree(data.left, depth + 1);
      ast_print_tree(data.right, depth + 1);
      break;
    }
  }
}

// Function to parse a single number or letter
AST *parse_primary(const char **expr) {
  while (isspace(**expr)) (*expr)++;
  
  if (isdigit(**expr)) {
    int number = 0;
    while (isdigit(**expr)) {
      number = number * 10 + (**expr - '0');
      (*expr)++;
    }
    return AST_NEW(AST_NUMBER, number);
  }
  
  if (isalpha(**expr)) {
    char letter = **expr;
    (*expr)++;
    return AST_NEW(AST_LETTER, letter);
  }
  
  return NULL;
}

// Function to parse multiplication and division
AST *parse_mul(const char **expr) {
  AST *left = parse_primary(expr);
  
  while (isspace(**expr)) (*expr)++;
  
  if (**expr == '*') {
    (*expr)++;
    AST *right = parse_mul(expr); // Recursive call to parse_mul
    return AST_NEW(AST_MUL, left, right);
  }
  
  if (**expr == '/') {
    (*expr)++;
    AST *right = parse_mul(expr); // Recursive call to parse_mul
    return AST_NEW(AST_DIV, left, right);
  }
  
  return left;
}

// Function to parse addition
AST *parse_expression(const char **expr) {
  AST *left = parse_mul(expr);
  
  while (isspace(**expr)) (*expr)++;
  
  if (**expr == '+') {
    (*expr)++;
    AST *right = parse_expression(expr); // Recursive call to parse_expression
    return AST_NEW(AST_ADD, left, right);
  }
  
  return left;
}

int main() {
  char input[256];
  
  while (1) {
    printf("Digite uma expressão (ou pressione Enter para sair): ");
    fgets(input, sizeof(input), stdin);
    
    // Remover o newline (\n) do final da string
    input[strcspn(input, "\n")] = 0;
    
    // Se a entrada for uma linha vazia, sair do loop
    if (strlen(input) == 0) {
      break;
    }
    
    const char *expr = input;
    AST *ast = AST_NEW(AST_MAIN, parse_expression(&expr));
    
    printf("\n/* AST Tree Representation */\n");
    ast_print_tree(ast, 0);
    
    ast_free(ast);
  }
  
  return 0;
}

#ifndef AST_FILE
#define AST_FILE

#include "estruturas.h"

ARVORE criarNo (char *tipoVariavel, char *valor);
void criarIrmao(ARVORE noActual, ARVORE novoNo);
void imprimirAST(ARVORE noActual);

#endif
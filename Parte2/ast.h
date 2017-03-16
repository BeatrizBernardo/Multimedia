#ifndef AST_FILE
#define AST_FILE

ARVORE criarNo (char *valor, char *tipoVariavel);
void criarIrmao(ARVORE *noActual, ARVORE *novoNo);
void imprimirAST(ARVORE *noActual);

#endif
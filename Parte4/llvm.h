#ifndef LLVM_FILE
#define LLVM_FILE

#include "estruturas.h"
#include "ast.h"
#include "astAnotada.h"

void inicializarLLVM(ARVORE raiz);
char *tipoDeValores(char *tipo);
void llvmPrints(ARVORE noActual);
char *removechar(char *string);
void llvmMethods(ARVORE noActual, CLASSE symTab, CLASSE aux);
CLASSE procurarMethodTabela(ARVORE noActual, CLASSE symTab);
#endif
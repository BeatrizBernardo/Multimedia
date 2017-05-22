#ifndef LLVM_FILE
#define LLVM_FILE

#include "estruturas.h"
#include "ast.h"
#include "astAnotada.h"

void inicializarLLVM(ARVORE raiz);
char *tipoDeValores(char *tipo);
void llvmPrints(ARVORE noActual);

#endif
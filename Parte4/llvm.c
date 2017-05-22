#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas.h"
#include "ast.h"
#include "astAnotada.h"
#include "llvm.h"

CLASSE symTab = NULL;
/*pretende guardar o nome da classe do ficheiro de teste*/
char *classeName; 

void inicializarTabelaSimbolos(ARVORE raiz){
    symTab = getSymbolTabel(raiz);
}

void llvmFile(ARVORE noActual){
    if(noActual != NULL){
        int numero = retornaNumero(noActual->tipoVariavel);
        switch(numero){
            /*FieldDecl*/
            case 1:{
                printf("@%s.%s\n", classeName, "cenas");
            };break;
            /*MethodHeader*/
            case 2:{
                printf("@%s.%s\n", classeName, "cenas");
            };break;
            /*Program*/
            case 3:{
                classeName = strdup(symTab->name);
            };break;
            /*default*/
            case 0:{};
        }

        if(noActual->filho != NULL){
            llvmFile(noActual->filho);
        }

        if(noActual->irmao != NULL){
            llvmFile(noActual->irmao);
        }
    }   
}
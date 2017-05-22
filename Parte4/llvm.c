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

char *tipoDeValores(char *tipo){
    if(strcmp(tipo, "int") == 0){
        return "i32";
    }else if(strcmp(tipo, "boolean") == 0){
        return "i1";
    }else if(strcmp(tipo, "double") == 0){
        return "double";
    }else if(strcmp(tipo, "void") == 0){
        return "void";
    }else if(strcmp(tipo, "String[]") == 0){
        return "i8*";
    }
    return NULL;
}

void inicializarTabelaSimbolos(ARVORE raiz){
    symTab = getSymbolTabel(raiz);

    /*get variables and methods names*/
    classeName = strdup(symTab->name);
    symTab = symTab->proximaClass;
    METHOD methodAux;
    int flagParams = 0;
    while(symTab != NULL){
        flagParams = 0;
        if(symTab->is_variavel == 0){
            printf("declare %s @%s.%s.(", tipoDeValores(symTab->type), classeName, symTab->name);
            methodAux = symTab->proximoMethod;
            while(methodAux != NULL){
                if(methodAux->is_param == 1){
                    printf("%s %%%s", tipoDeValores(methodAux->type), methodAux->name);
                }

                if(flagParams == 1 && methodAux->proximoMethod != NULL && methodAux->proximoMethod->is_param == 1){
                    printf(", ");
                }
                flagParams = 1;

                methodAux = methodAux->proximoMethod;
            }
            printf(")\n");
        }else if(symTab->is_variavel == 1){
            printf("declare %s @%s.%s\n", tipoDeValores(symTab->type), classeName, symTab->name);
        }
        symTab = symTab->proximaClass;
    }

}

void llvmFile(ARVORE noActual){
    if(noActual != NULL){
        int numero = retornaNumero(noActual->tipoVariavel);
        switch(numero){
            
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas.h"
#include "ast.h"
#include "astAnotada.h"

CLASSE tabelaSimbolos;

char *paraMinusculas(char *string){
    char *str = strdup(string);
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
    return str;
}

int retornaNumero(char *tipoVariavel){
    if(strcmp(tipoVariavel, "FieldDecl") == 0){
        return 1;
    }else if(strcmp(tipoVariavel, "VarDecl") == 0){
        return 2;
    }else if(strcmp(tipoVariavel, "MethodDecl") == 0){
        return 3;
    }else if(strcmp(tipoVariavel, "MethodHeader") == 0){
        return 4;
    }else if(strcmp(tipoVariavel, "MethodParams") == 0){
        return 5;
    }else if(strcmp(tipoVariavel, "ParamDecl") == 0){
        return 6;
    }else if(strcmp(tipoVariavel, "MethodBody") == 0){
        return 7;
    }else{
        return 0;
    }
}

void symbolTabel(ARVORE noActual){

    if(noActual != NULL){

        int numero = retornaNumero(noActual->tipoVariavel);
        switch(numero){
            case 1:{
                /*FieldDecl*/
                CLASSE no;
                no = (CLASSE)malloc(sizeof(CLSS));

                if(no != NULL){
                    no->name = strdup(noActual->filho->irmao->valor);
                    no->type = strdup(paraMinusculas(noActual->filho->tipoVariavel));
                    no->proximoMethod = NULL;
                }
                printf("1 %s %s\n",noActual->filho->tipoVariavel, noActual->filho->irmao->valor);
                printf("1 %s %s\n",no->name, no->type);
            };break;
            case 2:{
                /*VarDecl*/
                printf("2\n");
            };break;
            case 3:{
                /*MethodDecl*/
                printf("3\n");
            };break;
            case 4:{
                /*MethodHeader*/
                printf("4\n");
            };break;
            case 5:{
                /*MethodParams*/
                printf("5\n");
            };break;
            case 6:{
                /*ParamDecl*/
                printf("6\n");
            };break;
            case 7:{
                /*MethodBody*/
                printf("7\n");
            };break;
            case 0:{};
        }

        if(noActual->filho != NULL){
            symbolTabel(noActual->filho);
        }

        if(noActual->irmao != NULL){
            symbolTabel(noActual->irmao);
        }
    }
}

void imprimirASTAnotada(ARVORE noActual, int error, int numFilhos, int flagImprimir){
    if(noActual != NULL){
        if(error ==  0 && flagImprimir == 0){
            if(noActual->valor != NULL){
                for(int i=0; i < numFilhos; i++){
                    printf("..");
                }
                printf("%s(%s)\n", noActual->tipoVariavel, noActual->valor);
            }else{
                for(int i=0; i < numFilhos; i++){
                    printf("..");
                }
                printf("%s\n", noActual->tipoVariavel);
            }
        }
            
        if(noActual->filho != NULL){
            numFilhos += 1;
            imprimirAST(noActual->filho, error, numFilhos, flagImprimir);
            numFilhos -= 1;
        }

        if(noActual->irmao != NULL ){
            imprimirAST(noActual->irmao, error, numFilhos, flagImprimir);
        }
        
    
        
        if(noActual->tipoVariavel != NULL){
            free(noActual->tipoVariavel);
        }
        if(noActual->valor != NULL){
            free(noActual->valor);
        }
        free(noActual);
        
    }  
}
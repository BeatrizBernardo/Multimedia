#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas.h"
#include "ast.h"
#include "astAnotada.h"
#define MAX_STR 200 /*Possibility not the best option*/

CLASSE tabelaSimbolos = NULL;

void inicializarTabelaSimbolos(){
    tabelaSimbolos = (CLASSE)malloc(sizeof(CLSS));
    tabelaSimbolos->proximaClass = NULL;
    tabelaSimbolos->proximoMethod = NULL;
}

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
    }else if(strcmp(tipoVariavel, "Program") == 0){
        return 8;
    }else{
        return 0;
    }
}

/*adicionar à estrutura CLASSE em ultimo lugar*/
void ultimoNoClasse(CLASSE tabelaSimbolos, CLASSE noActual){
    /*se a head de CLASSE estiver vazia*/
    if(tabelaSimbolos == NULL){
        tabelaSimbolos = noActual;
    }else{
        /*procura o ultimo*/
        while(tabelaSimbolos->proximaClass != NULL){
            tabelaSimbolos = tabelaSimbolos->proximaClass;
        }
        tabelaSimbolos->proximaClass = noActual;
    }
}

/*adicinar à estrutura METHOD em ultimo lugar*/
void ultimoNoMethod(CLASSE tabelaSimbolos, METHOD noActual){
    METHOD aux;
    if(tabelaSimbolos->proximoMethod != NULL){
        aux = tabelaSimbolos->proximoMethod;

        while(aux->maisMethod != NULL){
            aux = aux->maisMethod;
        }
        aux->maisMethod = noActual;
    }else{
        tabelaSimbolos->proximoMethod = noActual;
    }
}

void imprimirTabelaSimbolos(){
    CLASSE aux = tabelaSimbolos;

    if(aux != NULL){
        if(aux->name != NULL){
            printf("===== Class %s Symbol Table =====\n", aux->name);
        }
        aux = aux->proximaClass;
        while(aux != NULL){
            if(aux->name != NULL){
                if(aux->paramTypes != NULL){
                    printf("%s\t%s\t%s\n",aux->name, aux->paramTypes, aux->type);
                }else{
                    printf("%s\t%s\n",aux->name, aux->type);
                }     
            }
            aux = aux->proximaClass;
        }
    }

    printf("\n");
    imprimirTabelasMethod();
}

void imprimirTabelasMethod(){
    CLASSE aux = tabelaSimbolos;
    METHOD aux2;
    while(aux != NULL){
        if(aux->is_param == 0){
            printf("===== Method %s%s Symbol Table =====\n", aux->name, aux->paramTypes);
            /*por cada classe fazer os METHODs*/
            aux2 = aux->proximoMethod;
            while(aux2 != NULL){
                if(aux2->is_param == 1){
                    printf("%s\t\t%s\tparam\n",aux2->name, aux2->type);
                }else{
                    printf("%s\t\t%s\t\n",aux2->name, aux2->type);
                }
                aux2 = aux2->maisMethod;
            }
            printf("\n");
        }
        aux = aux->proximaClass;
    }
}

void paramDecl(ARVORE noActual, CLASSE tabelaSimbolos){
    METHOD methodAux;
    methodAux = (METHOD)malloc(sizeof(MTHD));

    if(noActual != NULL){
        if(noActual->filho != NULL){
            noActual = noActual->filho;
            if(strcmp(noActual->filho->tipoVariavel, "StringArray") == 0){
                /*tabelaSimbolos->paramTypes = (char*)malloc(strlen("(String[])")+1);
                strcpy(tabelaSimbolos->paramTypes, "(String[])");*/
                tabelaSimbolos->paramTypes = strdup("(String[])");

                /*adicionar ao method*/
                methodAux->name = strdup(noActual->filho->irmao->valor);
                methodAux->type = strdup("String[]");
                methodAux->is_param = 1;
                ultimoNoMethod(tabelaSimbolos, methodAux);

            }else{
                char aux[MAX_STR];
                strcpy(aux, "(");
                while(noActual != NULL){
                    printf("---%s\n", noActual->filho->tipoVariavel);
                    if(noActual->irmao == NULL){
                        strcat(aux, paraMinusculas(noActual->filho->tipoVariavel));
                        /*adicionar ao method*/
                        methodAux->name = strdup(noActual->filho->irmao->valor);
                        methodAux->type = strdup(paraMinusculas(noActual->filho->tipoVariavel));
                        methodAux->is_param = 1;
                        ultimoNoMethod(tabelaSimbolos, methodAux);
                    }else{
                        strcat(aux, paraMinusculas(noActual->filho->tipoVariavel));
                        strcat(aux, ",");
                        /*adicionar ao method*/
                        methodAux->name = strdup(noActual->filho->irmao->valor);
                        methodAux->type = strdup(paraMinusculas(noActual->filho->tipoVariavel));
                        methodAux->is_param = 1;
                        ultimoNoMethod(tabelaSimbolos, methodAux);
                    }
                    
                    noActual = noActual->irmao;
                }
                strcat(aux, ")");
                tabelaSimbolos->paramTypes = strdup(aux);
            }
        }else{
            tabelaSimbolos->paramTypes = NULL;
        }
    }
}

void methodBody(ARVORE noActual, CLASSE tabelaSimbolos){
    printf("%s\n", noActual->tipoVariavel);

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
                    no->is_param = 1;
                    no->proximoMethod = NULL;
                    ultimoNoClasse(tabelaSimbolos, no);
                }
            };break;
            case 2:{
                /*VarDecl*/
                printf("2\n");
            };break;
            case 3:{
                /*MethodDecl*/
            };break;
            case 4:{
                /*MethodHeader*/
                CLASSE no;
                no = (CLASSE)malloc(sizeof(CLSS));

                METHOD noAux;
                noAux = (METHOD)malloc(sizeof(MTHD));

                if(no != NULL){
                    no->name = strdup(noActual->filho->irmao->valor);
                    no->type = strdup(paraMinusculas(noActual->filho->tipoVariavel));
                    no->is_param = 0;
                    ultimoNoClasse(tabelaSimbolos, no);

                    /*adicionar o return - sempre o primeiro no a retornar*/
                    noAux->name = strdup("return");
                    noAux->type = strdup(paraMinusculas(noActual->filho->tipoVariavel));
                    noAux->is_param = 0;

                    no->proximoMethod = noAux;
                }

                ARVORE aux = noActual->filho->irmao->irmao;
                paramDecl(aux, no);

                ARVORE aux2 = noActual->irmao;
                methodBody(aux, no);

            };break;
            case 5:{
                /*MethodParams*/
            };break;
            case 6:{
                /*ParamDecl*/
            };break;
            case 7:{
                /*MethodBody*/
                printf("7\n");
            };break;
            case 8:{
                /*Program*/
                CLASSE no;
                no = (CLASSE)malloc(sizeof(CLSS));

                if(no != NULL){
                    no->name = strdup(noActual->filho->valor);
                    no->is_param = 1;
                    no->proximoMethod = NULL;
                    tabelaSimbolos = no;
                    //ultimoNoClasse(tabelaSimbolos, no);
                }
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
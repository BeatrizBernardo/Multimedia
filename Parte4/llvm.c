#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas.h"
#include "ast.h"
#include "astAnotada.h"
#include "llvm.h"

CLASSE symTab;
/*pretende guardar o nome da classe do ficheiro de teste*/
char *classeName; 
int str = 0;
int flagAtoi = 0;
int flagPrint = 0;
int temporaria = 1;

/*retirada e modificada de http://stackoverflow.com/questions/7821997/c-remove-chars-from-string*/
char *removechar(char *string){
    char t = '"';
    char *str = strdup(string);
    int i,j;
    i = 0;
    while(i<strlen(str))
    {
        if (str[i]==t) 
        { 
            for (j=i; j<strlen(str); j++)
                str[j]=str[j+1];   
        } else i++;
    }
    return str;
}

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

void inicializarLLVM(ARVORE raiz){
    symTab = getSymbolTabel(raiz);
    CLASSE auxSymTab = symTab;

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

    llvmPrints(raiz);
    //llvmMethods(raiz, auxSymTab, NULL);
}

/*retorna prints no inicio de LLVM*/
void llvmPrints(ARVORE noActual){
    if(noActual != NULL){
        int numero = retornaNumero(noActual->tipoVariavel);
        switch(numero){
            /*Print*/
            case 14:{
                if(flagPrint == 0){
                    flagPrint = 1;
                    printf("declare i32 @printf(i8*, ...)\n");
                }
               // printf(" %s  - %s -  %d \n", noActual->filho->tipoVariavel, noActual->filho->valor, str);
                if(strcmp(noActual->filho->tipoVariavel,"Id") == 0 || 
                    strcmp(noActual->filho->tipoVariavel,"Call") == 0){
                    
                    //printf(" . . . .. . . %s\n", noActual->filho->stringAST);
                    //noActual->filho->tamanhoString = strlen(noActual->filho->valor)-1;
                    noActual->filho->pos = str;
                    //printf("####### %s %d\n", removechar(noActual->filho->valor), noActual->filho->tamanhoString);
                    if(str == 0){
                        printf("@.str");
                    }else{
                        printf("@.str.%d", noActual->filho->pos);
                    }

                    if(strcmp(noActual->filho->stringAST, "int") == 0){
                        printf(" = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\"\n");
                    }else if(strcmp(noActual->filho->stringAST, "double") == 0){
                        printf(" = private unnamed_addr constant [4 x i8] c\"%%.16E\\0A\\00\"\n");
                    }else if(strcmp(noActual->filho->stringAST, "boolean") == 0){
                        printf(" = private unnamed_addr constant [4 x i8] c\"%%%s\\0A\\00\"\n", strcmp(noActual->filho->valor, "true") == 0 ? "true":"false") ;
                    }
                    str++;
                }else if(strcmp(noActual->filho->tipoVariavel,"StrLit") == 0){
                    
                    noActual->filho->tamanhoString = strlen(noActual->filho->valor)-1;
                    noActual->filho->pos = str;
                    //printf(" \"%s\\00\"  %d\n", removechar(noActual->filho->valor), noActual->filho->tamanhoString);
                    if(str == 0){
                        printf("@.str");
                    }else{
                        printf("@.str.%d", noActual->filho->pos);
                    }
                    printf(" = private unnamed_addr constant [%d x i8] c\"%s\\00\"\n",noActual->filho->tamanhoString, removechar(noActual->filho->valor));
                    str++;
                }else if(strcmp(noActual->filho->tipoVariavel,"DecLit") == 0){
                    
                    noActual->filho->tamanhoString = strlen(noActual->filho->valor)-1;
                    noActual->filho->pos = str;
                    //printf(" %s %d\n", removechar(noActual->filho->valor), noActual->filho->tamanhoString);
                    if(str == 0){
                        printf("@.str");
                    }else{
                        printf("@.str.%d", noActual->filho->pos);
                    }
                    printf(" = private unnamed_addr constant [4 x i8] c\"%%d\\0A\\00\"\n");
                    str++;
                }else if(strcmp(noActual->filho->tipoVariavel,"RealLit") == 0){
                    
                    noActual->filho->tamanhoString = strlen(noActual->filho->valor)-1;
                    noActual->filho->pos = str;
                    //printf(" \"%s\\00\"  %d\n", removechar(noActual->filho->valor), noActual->filho->tamanhoString);
                    if(str == 0){
                        printf("@.str");
                    }else{
                        printf("@.str.%d", noActual->filho->pos);
                    }
                    printf(" = private unnamed_addr constant [4 x i8] c\"%%.16E\\0A\\00\"\n");
                    str++;
                }else if(strcmp(noActual->filho->tipoVariavel,"BoolLit") == 0){
                    
                    noActual->filho->tamanhoString = strlen(noActual->filho->valor)-1;
                    noActual->filho->pos = str;
                    //printf(" \"%s\\00\"  %d\n", removechar(noActual->filho->valor), noActual->filho->tamanhoString);
                    if(str == 0){
                        printf("@.str");
                    }else{
                        printf("@.str.%d", noActual->filho->pos);
                    }
                    printf(" = private unnamed_addr constant [4 x i8] c\"%%%s\\0A\\00\"\n", strcmp(noActual->filho->valor, "true") == 0 ? "true":"false") ;
                    str++;
                }

            };break;
            /*ParseArgs*/
            case 15:{
                if(flagAtoi == 0){
                    flagAtoi = 1;
                    printf("declare i32 @atoi(i8*)\n");
                }


            };break;
            /*default*/
            case 0:{};
        }

        if(noActual->filho != NULL){
            llvmPrints(noActual->filho);
        }

        if(noActual->irmao != NULL){
            llvmPrints(noActual->irmao);
        }
    }   
}

void llvmMethods(ARVORE noActual, CLASSE symTab, CLASSE aux){
    
    if(noActual != NULL){
        int numero = retornaNumero(noActual->tipoVariavel);
        switch(numero){
            /*MethodHeader*/
            case 2:{
                temporaria = 1;
                aux = procurarMethodTabela(noActual, symTab);
                //printf(" %s %s \n", aux->name, aux->proximoMethod->name);
                METHOD methodAux = aux->proximoMethod;
                METHOD methodAux2 = aux->proximoMethod;
                int flagParams = 0;

                /*definir o metodo*/
                printf("define %s @%s.%s.(", tipoDeValores(aux->type), classeName, aux->name);
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
                printf("){\n");

                /*alocar e armazenar os parametros*/
                while(methodAux2 != NULL){
                    if(methodAux2->is_param == 1){
                        printf("\t%%%d = alloca %s\n",temporaria, tipoDeValores(methodAux2->type));
                        printf("\tstore %s %%%s, %s* %%%d\n", tipoDeValores(methodAux2->type), methodAux2->name, tipoDeValores(methodAux2->type), temporaria);
                        temporaria++;
                    }
                    methodAux2 = methodAux2->proximoMethod;
                }

            };break;
            /*Print*/
            case 14:{
                //printf("@@@@@@@ %s %s\n", noActual->tipoVariavel, noActual->filho->tipoVariavel);
                if(strcmp(noActual->filho->tipoVariavel, "StrLit") == 0){
                    printf("\t%%%d = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([%d x i8], [%d x i8]* @.str", temporaria, noActual->filho->tamanhoString, noActual->filho->tamanhoString);
                    if(noActual->filho->pos > 0){
                        printf(".%d", noActual->filho->pos);
                    }
                    printf(", i32 0, i32 0))\n");
                }/*else if(strcmp(noActual->filho->tipoVariavel, "DecLit") == 0){

                }*/
                
                temporaria++;
            };break;
            /*return*/
            case 16:{
                //printf("@@@@@  %s \n", aux->name);
                printf("\tret %s ", tipoDeValores(aux->proximoMethod->type));
                if((strcmp(noActual->filho->tipoVariavel, "DecLit") == 0) ||
                    (strcmp(noActual->filho->tipoVariavel, "RealLit") == 0) || 
                    (strcmp(noActual->filho->tipoVariavel, "BoolLit") == 0)){
                    printf("%s\n", noActual->filho->valor);
                }else if(strcmp(noActual->filho->tipoVariavel, "Id") == 0){
                    printf("%%%d\n", temporaria);
                }else if(strcmp(noActual->filho->tipoVariavel, "void") == 0){
                    printf("void\n");
                }
                printf("}\n");
            };break;
            /*default*/
            case 0:{};
        }

        if(noActual->filho != NULL){
            llvmMethods(noActual->filho, symTab, aux);
        }

        if(noActual->irmao != NULL){
            llvmMethods(noActual->irmao, symTab, aux);
        }
    }
}

CLASSE procurarMethodTabela(ARVORE noActual, CLASSE symTab){
    if(noActual != NULL){
        while(symTab != NULL){
            if((strcmp(noActual->filho->irmao->valor, symTab->name) == 0) && noActual->filho->irmao->pos == symTab->pos){
                /*para passar o irmao - MethodBody*/
                //symbolTabel2(noActual->irmao, auxClasse, 0);
                return symTab;
                //printf(" - - - %s - - %s - tipo %s\n",noActual->filho->irmao->valor, auxClasse->name, auxClasse->type);
            }
            symTab = symTab->proximaClass;
        }
    }
    return NULL;
}
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
int flagReturnVoid = 0;
int flagIntoReturn = 0;
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
    }
    return NULL;
}

void inicializarLLVM(ARVORE raiz){
    symTab = getSymbolTabel(raiz);
    CLASSE auxSymTab = symTab;

    /*get variables and methods names*/
    classeName = strdup(symTab->name);
    symTab = symTab->proximaClass;
    //METHOD methodAux;
    int flagParams = 0;
    while(symTab != NULL){
        flagParams = 0;
        /*if(symTab->is_variavel == 0){
            printf("declare %s @%s.%s.(", tipoDeValores(symTab->type), classeName, symTab->name);
            methodAux = symTab->proximoMethod;
            while(methodAux != NULL){
                if(methodAux->is_param == 1){
                    if(strcmp(methodAux->type, "String[]") == 0){
                        printf("i32 %%argc, i8** %%argv");
                    }else{
                        printf("%s %%%s", tipoDeValores(methodAux->type), methodAux->name);
                    }
                }

                if(flagParams == 1 && methodAux->proximoMethod != NULL && methodAux->proximoMethod->is_param == 1){
                    printf(", ");
                }
                flagParams = 1;

                methodAux = methodAux->proximoMethod;
            }
            printf(")\n");
        }else */if(symTab->is_variavel == 1){
            printf("@%s.%s = common global %s 0\n", classeName, symTab->name, tipoDeValores(symTab->type));
        }
        symTab = symTab->proximaClass;
    }

    llvmPrints(raiz);

    /*main principal*/
    printf("define i32 @main(i32 %%argc, i8** %%argv){\n");
    printf("\t%%1 = alloca i32\n");
    printf("\t%%2 = alloca i32\n");
    printf("\t%%3 = alloca i8**\n");
    printf("\tstore i32 0, i32* %%1\n");
    printf("\tstore i32 %%argc, i32* %%2\n");
    printf("\tstore i8** %%argv, i8*** %%3\n");
    printf("\t%%4 = load i32, i32* %%2\n");
    printf("\t%%5 = load i8**, i8*** %%3\n");
    printf("\tcall void @%s.main.(i32 %%4, i8** %%5)\n", classeName);
    printf("\tret i32 0\n");
    printf("}\n");

    /*resto das funções*/
    llvmMethods(raiz, auxSymTab, NULL);
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
                if(strcmp(noActual->filho->tipoVariavel,"Id") == 0 || 
                    strcmp(noActual->filho->tipoVariavel,"Call") == 0){
                    
                    noActual->filho->pos = str;
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
                flagIntoReturn = 0;
                aux = procurarMethodTabela(noActual, symTab);
                METHOD methodAux = aux->proximoMethod;
                METHOD methodAux2 = aux->proximoMethod;
                int flagParams = 0;

                /*definir o metodo*/
                printf("define %s @%s.%s.(", tipoDeValores(aux->type), classeName, aux->name);
                if(strcmp(tipoDeValores(aux->type), "void") == 0){
                    flagReturnVoid = 1;
                }
                while(methodAux != NULL){
                    if(methodAux->is_param == 1){
                        if(strcmp(methodAux->type, "String[]") == 0){
                            printf("i32 %%argc, i8** %%argv");
                        }else{
                            printf("%s %%%s", tipoDeValores(methodAux->type), methodAux->name);
                        }
                        
                    }

                    if(flagParams == 1 && methodAux->proximoMethod != NULL && methodAux->proximoMethod->is_param == 1){
                        printf(", ");
                    }
                    flagParams = 1;

                    methodAux = methodAux->proximoMethod;
                }
                printf("){\n");

                /*alocar e armazenar os parametros e outras variaveis locais*/
                methodAux2 = methodAux2->proximoMethod;
                while(methodAux2 != NULL){
                        if(strcmp(methodAux2->type, "String[]") == 0){
                                printf("\t%%1 = alloca i32\n");
                                printf("\t%%2 = alloca i8**\n");
                                printf("\tstore i32 %%argc, i32* %%1\n");
                                printf("\tstore i8** %%argv, i8*** %%2\n");
                                methodAux2->variavelTemporaria = 2;
                                temporaria = 3;
                        }else if(methodAux2->is_param == 1){
                            printf("\t%%%d = alloca %s\n",temporaria, tipoDeValores(methodAux2->type));
                            printf("\tstore %s %%%s, %s* %%%d\n", tipoDeValores(methodAux2->type), methodAux2->name, tipoDeValores(methodAux2->type), temporaria);
                            methodAux2->variavelTemporaria = temporaria;
                            temporaria++;
                        }else{
                            printf("\t%%%s = alloca %s\n",methodAux2->name, tipoDeValores(methodAux2->type));
                        }
                    methodAux2 = methodAux2->proximoMethod;
                }


                if(noActual->filho != NULL){
                    llvmMethods(noActual->filho, symTab, aux);
                }

                if(noActual->irmao != NULL){
                    llvmMethods(noActual->irmao, symTab, aux);
                }

                /*se não houver return explicito*/
                if(flagReturnVoid == 1 && flagIntoReturn == 0){
                    printf("\tret void\n");
                    printf("}\n");
                    flagReturnVoid = 0;
                }
            };break;
            /*Assign*/
            case 10:{
                //store i32 1, i32* %a, align 4
                printf("\tstore %s %s, %s* %%%s\n", tipoDeValores(noActual->stringAST), noActual->filho->irmao->valor, tipoDeValores(noActual->stringAST), noActual->filho->valor);
            };break;
            /*unarios*/
            case 12:{
                
            };break;
            /*Print*/
            case 14:{
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
                if(flagIntoReturn == 0){
                    flagIntoReturn = 1;
                    printf("\tret");
                    if(noActual->filho != NULL){
                        if((strcmp(noActual->filho->tipoVariavel, "DecLit") == 0) ||
                            (strcmp(noActual->filho->tipoVariavel, "RealLit") == 0) || 
                            (strcmp(noActual->filho->tipoVariavel, "BoolLit") == 0)){
                            printf(" %s %s\n", tipoDeValores(aux->proximoMethod->type), noActual->filho->valor);
                        }else if(strcmp(noActual->filho->tipoVariavel, "Id") == 0){
                            printf(" %s %%%d\n", tipoDeValores(aux->proximoMethod->type), temporaria);
                        }
                    }else{
                        printf(" void\n");
                    }
                    printf("}\n");
                }
                
            };break;
            /*default*/
            case 0:{};
        }

        if(noActual->filho != NULL && flagIntoReturn == 0){
            llvmMethods(noActual->filho, symTab, aux);
        }

        if(noActual->irmao != NULL && flagIntoReturn == 0){
            llvmMethods(noActual->irmao, symTab, aux);
        }
    }
}

CLASSE procurarMethodTabela(ARVORE noActual, CLASSE symTab){
    if(noActual != NULL){
        while(symTab != NULL){
            if((strcmp(noActual->filho->irmao->valor, symTab->name) == 0) && noActual->filho->irmao->pos == symTab->pos){
                return symTab;
            }
            symTab = symTab->proximaClass;
        }
    }
    return NULL;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "estruturas.h"
#include "ast.h"
#include "astAnotada.h"
#define MAX_STR 1000 /*Possibility not the best option*/

CLASSE tabelaSimbolos = NULL;

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
    }else if(strcmp(tipoVariavel, "MethodHeader") == 0){
        return 4;
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
    METHOD aux = tabelaSimbolos->proximoMethod;
    //printf("1o no - %s\n", tabelaSimbolos->proximoMethod->name);                        

    
    while(aux->proximoMethod != NULL){
        //printf("----> %s\n", aux->name);
        aux = aux->proximoMethod;
    }
    aux->proximoMethod = noActual;

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
                    printf("%s\t\t%s\n",aux->name, aux->type);
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
        if(aux->is_variavel == 0){
            printf("===== Method %s%s Symbol Table =====\n", aux->name, aux->paramTypes);
            /*por cada classe fazer os METHODs*/
            aux2 = aux->proximoMethod;
            printf("%s\t\t%s\n",aux2->name, aux2->type);
            aux2 = aux2->proximoMethod;
            while(aux2 != NULL){
                if(aux2->is_param == 1){
                    printf("%s\t\t%s\tparam\n",aux2->name, aux2->type);
                }else{
                    printf("%s\t\t%s\n",aux2->name, aux2->type);
                }
                aux2 = aux2->proximoMethod;
            }
            printf("\n");
        }
        aux = aux->proximaClass;
    }
}

void paramDecl(ARVORE noActual, CLASSE tabelaSimbolos, ARVORE nomeFuncao){
    METHOD methodAux;

    if(noActual != NULL){
        if(noActual->filho != NULL){
            noActual = noActual->filho;
            if(strcmp(noActual->filho->tipoVariavel, "StringArray") == 0){
                methodAux = (METHOD)malloc(sizeof(MTHD));
                /*tabelaSimbolos->paramTypes = (char*)malloc(strlen("(String[])")+1);
                strcpy(tabelaSimbolos->paramTypes, "(String[])");*/
                tabelaSimbolos->paramTypes = strdup("(String[])");
                tabelaSimbolos->num_params = 1;

                /*adicionar ao method*/
                methodAux->name = strdup(noActual->filho->irmao->valor);
                methodAux->type = strdup("String[]");
                methodAux->is_param = 1;
                methodAux->proximoMethod = NULL;
                ultimoNoMethod(tabelaSimbolos, methodAux);


            }else{
                char aux[MAX_STR];
                int nParams = 0;
                strcpy(aux, "(");
                while(noActual != NULL){
                    if(noActual->irmao == NULL){
                        methodAux = (METHOD)malloc(sizeof(MTHD));
                        /*adicionar ao method*/
                        methodAux->name = strdup(noActual->filho->irmao->valor);
                        if(strcmp(noActual->filho->tipoVariavel, "Bool") == 0){
                            methodAux->type = strdup("boolean");
                        }else{
                            methodAux->type = strdup(paraMinusculas(noActual->filho->tipoVariavel));
                        }
                        methodAux->is_param = 1;
                        methodAux->proximoMethod = NULL;
                        nParams++;
                        ultimoNoMethod(tabelaSimbolos, methodAux);

                        /*add to string*/
                        strcat(aux, methodAux->type);
                    }else{
                        methodAux = (METHOD)malloc(sizeof(MTHD));
                        /*adicionar ao method*/
                        methodAux->name = strdup(noActual->filho->irmao->valor);
                        if(strcmp(noActual->filho->tipoVariavel, "Bool") == 0){
                            methodAux->type = strdup("boolean");
                        }else{
                            methodAux->type = strdup(paraMinusculas(noActual->filho->tipoVariavel));
                        }
                        methodAux->is_param = 1;
                        methodAux->proximoMethod = NULL;
                        nParams++;
                        ultimoNoMethod(tabelaSimbolos, methodAux);

                        /*add to string*/
                        strcat(aux, methodAux->type);
                        strcat(aux, ",");
                    }
                    
                    noActual = noActual->irmao;
                }
                strcat(aux, ")");
                tabelaSimbolos->paramTypes = strdup(aux);
                tabelaSimbolos->num_params = nParams;
            }
        }else{
            tabelaSimbolos->paramTypes = strdup("()");
            tabelaSimbolos->num_params = 0;
        }
    }
    //polimorfismo(tabelaSimbolos, nomeFuncao);
    
    //free(methodAux);
}

void methodBody(ARVORE noActual, CLASSE tabelaSimbolos){
    METHOD methodAux;

    if(noActual != NULL){
        if(noActual->filho != NULL){
            noActual = noActual->filho;
            while(noActual != NULL){
                /*Se for VARDECL insere na tabela*/
                if(strcmp(noActual->tipoVariavel, "VarDecl") == 0){
                    methodAux = (METHOD)malloc(sizeof(MTHD));
                    methodAux->name = strdup(noActual->filho->irmao->valor);
                    if(strcmp(noActual->filho->tipoVariavel, "Bool") == 0){
                        methodAux->type = strdup("boolean");
                    }else{
                        methodAux->type = strdup(paraMinusculas(noActual->filho->tipoVariavel));
                    }
                    methodAux->is_param = 0;
                    methodAux->proximoMethod = NULL;
                    ultimoNoMethod(tabelaSimbolos, methodAux);
                }
                noActual = noActual->irmao;
            }
        }
    }
}

char *procurarTipoVariavel(char *nome, CLASSE tabela){

    //printf(" - - -- - - -- -- - - - - - - -- - - - - - -- %s\n", nome);
    METHOD aux = tabela->proximoMethod;
    CLASSE auxClasse = tabelaSimbolos;
    /*procura primeiro se é local*/
    while(aux != NULL){
        //printf("aaaaaaaaaaaaa>>>>>>>>>>>>>> %s %s\n", aux->name, aux->type);
        if(strcmp(nome, aux->name) == 0){
            return aux->type;
        }
        aux = aux->proximoMethod;
    }

    /*procura nas globais*/

    while(auxClasse != NULL){
        //printf("zzzzzzzzzzzzzzz %s %s\n", auxClasse->name, auxClasse->paramTypes);
        if(strcmp(nome, auxClasse->name) == 0){
            if(auxClasse->paramTypes != NULL){
                return auxClasse->paramTypes;
            }else{
                return auxClasse->type;
            }
            
        }
        auxClasse = auxClasse->proximaClass;
    }
    return NULL;

}

/*espeficico para procurar metodos declarados no GLOBAL e devolver os parametros do metodo*/
char *procurarTipoParametrosMetodo(ARVORE noActual, char *nome, CLASSE tabela){
    //printf("------>>>>> %s - %s\n", noActual->tipoVariavel, noActual->valor);
    char stringAux[MAX_STR];
    ARVORE aux = noActual->irmao;
    ARVORE aux2 = noActual->irmao;
    strcpy(stringAux, "(");
    while(aux != NULL){
        //printf("--    ->>>>> %s - %s\n", aux->tipoVariavel, aux->valor);
        //printf("--<<<<<>>>>> %s\n", aux->stringAST);
        if(aux->irmao != NULL){
            strcat(stringAux, aux->stringAST);
            strcat(stringAux, ",");
        }else{
            strcat(stringAux, aux->stringAST);
        }
        aux = aux->irmao;
    }
    strcat(stringAux, ")");

    //printf("-<-<-<-<-<-<--<-<-<-< - %s\n", stringAux);

    CLASSE auxClasse = tabela;
    CLASSE auxClasse2 = tabela;
    while(auxClasse != NULL){
        /*verificar se o nome é igual e se é uma função*/
        if((strcmp(nome, auxClasse->name) == 0) && (auxClasse->is_variavel == 0)){
            /*verificar se o tipo de retorno e parametros sao iguais*/
            //printf("-<-<-<-<-<-<--<-<-<-< %s %s - %s\n",auxClasse->name, auxClasse->type, auxClasse->paramTypes);
            if( (strcmp(stringAux, auxClasse->paramTypes) == 0)){
                return auxClasse->paramTypes;           
            }
        }
        auxClasse = auxClasse->proximaClass;
    }

    METHOD auxMethod;

    while(auxClasse2 != NULL){
        /*verificar se o nome é igual e se é uma função*/
        if((strcmp(nome, auxClasse2->name) == 0) && (auxClasse2->is_variavel == 0)){
            auxMethod = auxClasse2->proximoMethod->proximoMethod;
            while(auxMethod != NULL && aux2 != NULL){
                if(auxMethod->is_param == 1){
                    //printf(" - - - %s \n", auxMethod->name);
                    if(strcmp(auxMethod->name, aux2->stringAST) != 0){
                       // printf("-- %s --- %s\n", aux2->stringAST, auxMethod->type);
                        if(strcmp(aux2->stringAST, "int") == 0 && strcmp(auxMethod->type, "double") == 0){
                            return auxClasse2->paramTypes;
                        }
                    }
                }
                auxMethod = auxMethod->proximoMethod;
                aux2 = aux2->irmao;
            }
        }
        auxClasse2 = auxClasse2->proximaClass;
    }
    return NULL;
}

/*devolve o tipo de retorno do metodo*/
char *procurarTipoRetornoMetodo(char *nome, char *parametros, CLASSE tabela){
    CLASSE auxClasse = tabelaSimbolos->proximaClass;
    while(auxClasse != NULL){
       // printf("zzzzzzz %s - - %s %s is: %d\n",nome, auxClasse->name, auxClasse->type, auxClasse->is_variavel);
        if((strcmp(nome, auxClasse->name) == 0) && (auxClasse->is_variavel == 0)){
            if(strcmp(parametros, auxClasse->paramTypes) == 0){
                return auxClasse->type;              
            }    
        }
        auxClasse = auxClasse->proximaClass;
    }
    return NULL;
}

/*função para comparar os tipos de retorno dos operadores numericos*/
char *compararTipos(char *tipo1, char *tipo2){
    if((strcmp(tipo1, "int") == 0) && (strcmp(tipo2, "int") == 0)){
        return "int";
    }else if((strcmp(tipo1, "double") == 0) || (strcmp(tipo2, "double") == 0)){
        return "double";
    }else if((strcmp(tipo1, "boolean") == 0) || (strcmp(tipo2, "boolean") == 0)){
        //return "undef";
        return "int";
    }
    return NULL;
}

void procurarNos(ARVORE noActual, CLASSE noClasse){
    printf(" - - -  %s\n", noClasse->name);
    if(noActual != NULL){
        /*se for inicializada uma funcao*/
        
        if(strcmp(noActual->tipoVariavel, "MethodHeader") == 0){
            /*procurar o no correspondente na tabela*/
            if((strcmp(noActual->filho->irmao->valor, noClasse->name) == 0) && (noClasse->is_variavel == 0)){
                nosAnotadosBasicos(noActual->irmao, noClasse, 0);
                nosAnotadosOperadoresNumericos(noActual->irmao, noClasse);
                nosAnotadosCall(noActual->irmao, noClasse);
            } 
        }
    }
    if(noActual->filho != NULL){
        procurarNos(noActual->filho, noClasse);
    }

    if(noActual->irmao != NULL){
        procurarNos(noActual->irmao, noClasse);
    }
}

/*Verificação dos nós anotados Básicos*/
void nosAnotadosBasicos(ARVORE noActual, CLASSE tabela, int is_Call){
    int flagVarDecl = 0;
    if(noActual != NULL){
        if(strcmp(noActual->tipoVariavel, "VarDecl") == 0){
            //printf("----> %s\n", noActual->tipoVariavel);
            flagVarDecl = 1;            
            is_Call = 0;
            
        }else if(((strcmp(noActual->tipoVariavel, "Eq") == 0) ||
          (strcmp(noActual->tipoVariavel, "Geq") == 0) ||
          (strcmp(noActual->tipoVariavel, "Gt") == 0) ||
          (strcmp(noActual->tipoVariavel, "Leq") == 0) ||
          (strcmp(noActual->tipoVariavel, "Lt") == 0) ||
          (strcmp(noActual->tipoVariavel, "Neq") == 0) ||
          (strcmp(noActual->tipoVariavel, "BoolLit") == 0) ||
          (strcmp(noActual->tipoVariavel, "And") == 0) ||
          (strcmp(noActual->tipoVariavel, "Or") == 0) ||
          (strcmp(noActual->tipoVariavel, "Not") == 0)) && noActual->noAnotado == 0){
            flagVarDecl = 0;
            is_Call = 0;
            noActual->noAnotado = 1;
            noActual->stringAST = strdup("boolean");
        }else if(((strcmp(noActual->tipoVariavel, "Length") == 0) || 
                (strcmp(noActual->tipoVariavel, "DecLit") == 0) ||
                (strcmp(noActual->tipoVariavel, "ParseArgs") == 0)) && noActual->noAnotado == 0){
            flagVarDecl = 0;
            is_Call = 0;
            noActual->noAnotado = 1;
            noActual->stringAST = strdup("int");
        }else if((strcmp(noActual->tipoVariavel, "RealLit") == 0) && noActual->noAnotado == 0){
            flagVarDecl = 0;
            is_Call = 0;
            noActual->noAnotado = 1;
            noActual->stringAST = strdup("double");
        }else if((strcmp(noActual->tipoVariavel, "StrLit") == 0) && noActual->noAnotado == 0){
            flagVarDecl = 0;
            is_Call = 0;
            noActual->noAnotado = 1;
            noActual->stringAST = strdup("String");
        }else if((strcmp(noActual->tipoVariavel, "Id") == 0) && noActual->noAnotado == 0){
            flagVarDecl = 0;
            if(is_Call == 0){
                noActual->noAnotado = 1;
                noActual->stringAST = strdup(procurarTipoVariavel(noActual->valor, tabela));
            }
            is_Call = 0;
        }else if((strcmp(noActual->tipoVariavel, "Assign") == 0) && noActual->noAnotado == 0){
            //printf("-<-<-<-<-<-- %s %s\n", noActual->filho->tipoVariavel, noActual->filho->valor);
            flagVarDecl = 0;
            is_Call = 0;
            noActual->noAnotado = 1;
            noActual->stringAST = strdup(procurarTipoVariavel(noActual->filho->valor, tabela));
        }else if(strcmp(noActual->tipoVariavel, "Call") == 0){
            is_Call = 1;
        }else{
            is_Call = 0;
        }
    }

    if(noActual->filho != NULL && flagVarDecl == 0){
        nosAnotadosBasicos(noActual->filho, tabela, is_Call);
    }

    if(noActual->irmao != NULL){
        is_Call = 0;
        nosAnotadosBasicos(noActual->irmao, tabela, is_Call);
    }
}

/*Verificação dos nós anotados*/
void nosAnotadosOperadoresNumericos(ARVORE noActual, CLASSE tabela){

    ARVORE auxNo;
    if(noActual != NULL){
        if(((strcmp(noActual->tipoVariavel, "Add") == 0) ||
                (strcmp(noActual->tipoVariavel, "Sub") == 0) ||
                (strcmp(noActual->tipoVariavel, "Mul") == 0) ||
                (strcmp(noActual->tipoVariavel, "Div") == 0) ||
                (strcmp(noActual->tipoVariavel, "Mod") == 0)) && noActual->noAnotado == 0){
            auxNo = noActual;

            if(auxNo->noAnotado != 1){
                if(auxNo->filho != NULL){
                    nosAnotadosOperadoresNumericos(auxNo->filho, tabela);
                }

                if(auxNo->irmao != NULL){
                    nosAnotadosOperadoresNumericos(auxNo->irmao, tabela);
                }
            }

            auxNo->noAnotado = 1;
            //printf("@@@--->>->> %s %s --- %d - - %s\n", auxNo->filho->tipoVariavel, auxNo->filho->valor, is_Call, auxNo->filho->stringAST);
            //printf("@@@--->>->> %s %s --- %d - - %s\n", auxNo->filho->irmao->tipoVariavel, auxNo->filho->irmao->valor, is_Call, auxNo->filho->irmao->stringAST);
            auxNo->stringAST = strdup(compararTipos(auxNo->filho->stringAST,auxNo->filho->irmao->stringAST));
                                    
        }else if(((strcmp(noActual->tipoVariavel, "Plus") == 0) ||
                (strcmp(noActual->tipoVariavel, "Minus") == 0)) && noActual->noAnotado == 0){
            noActual->noAnotado = 1;
            noActual->stringAST = strdup(noActual->filho->stringAST);
        }
    }

    if(noActual->filho != NULL){
        nosAnotadosOperadoresNumericos(noActual->filho, tabela);
    }

    if(noActual->irmao != NULL){
        nosAnotadosOperadoresNumericos(noActual->irmao, tabela);
    }
}

char *fazerParametros(ARVORE noActual){
    char stringAux[MAX_STR];
    char *string;
    int flagUndef = 0;
    ARVORE aux = noActual->irmao;
    strcpy(stringAux, "(");
    while(aux != NULL){
        //printf("--    ->>>>> %s - %s\n", aux->tipoVariavel, aux->valor);
        //printf("--<<<<<>>>>> %s\n", aux->stringAST);
        if(aux->irmao != NULL){
            if(strcmp(aux->stringAST, "undef") == 0){
                flagUndef = 1;
            }
            strcat(stringAux, aux->stringAST);
            strcat(stringAux, ",");
        }else{
            if(strcmp(aux->stringAST, "undef") == 0){
                flagUndef = 1;
            }
            strcat(stringAux, aux->stringAST);
        }
        aux = aux->irmao;
    }
    strcat(stringAux, ")");
    //printf("------------- %s\n", stringAux);
    if(flagUndef == 0){
        string = strdup(stringAux);
    }else{
        string = strdup("undef");
    }
    
    return string;
}

void nosAnotadosCall(ARVORE noActual, CLASSE tabela){
    ARVORE auxNo2;
    if(noActual != NULL){
        if(strcmp(noActual->tipoVariavel, "Call") == 0){
            auxNo2 = noActual;

            if(auxNo2->noAnotado != 1){
                if(auxNo2->filho != NULL){
                    nosAnotadosCall(auxNo2->filho, tabela);
                }

                if(auxNo2->irmao != NULL){
                    nosAnotadosCall(auxNo2->irmao, tabela);
                }
            }
            auxNo2->filho->noAnotado = 1;
            //printf("@@@--->>->>  %s - - - %s\n", auxNo2->filho->valor, auxNo2->filho->stringAST);
            char *string = procurarTipoParametrosMetodo(auxNo2->filho, auxNo2->filho->valor, tabela);
            //printf("---- string: %s\n", string);
            if(string != NULL){
                if(strcmp(string, "undef") != 0){
                    auxNo2->filho->stringAST = strdup(string);
                }else{
                    auxNo2->filho->stringAST = strdup("undef");
                }
                
                auxNo2->noAnotado = 1;
                auxNo2->stringAST = strdup(procurarTipoRetornoMetodo(auxNo2->filho->valor, auxNo2->filho->stringAST, tabela));
            }else{
                auxNo2->filho->stringAST = strdup(fazerParametros(noActual->filho));
                auxNo2->noAnotado = 1;
                auxNo2->stringAST = strdup("undef");
            }
            
            //printf("@@@--->>->> %s %s - - - %s\n", auxNo2->tipoVariavel, auxNo2->valor, auxNo2->stringAST);
            
            
        }
    }

    if(noActual->filho != NULL){
        nosAnotadosCall(noActual->filho, tabela);
    }

    if(noActual->irmao != NULL){
        nosAnotadosCall(noActual->irmao, tabela);
    }
}

/*verifica se já existe uma função com o mesmo nome e/ou mesmo parametros*/
void polimorfismo(CLASSE no, ARVORE noArv){
    CLASSE aux = tabelaSimbolos;
    
    while(aux != NULL){
        //printf(">>> %s %s %s\n", aux->name, no->name, noArv->valor);
        /*quando é uma variavel global com o mesmo nome*/
        if((strcmp(aux->name, no->name) == 0) && (aux->is_variavel == 1 && no->is_variavel == 1)){
            //return 1;
            //printf("1\n");
            if(strcmp(aux->type, no->type) == 0){
                printf("Line %d, col %d: Symbol %s already defined\n", noArv->numLinha, noArv->numColuna, no->name);
                exit(0);
            }
        /*quando é uma função com o mesmo nome*/
        }else if((strcmp(aux->name, no->name) == 0) && (aux->is_variavel == 0 && no->is_variavel == 0)){            
            //printf(" ---- %s \n", aux->paramTypes);
            //printf(" ---- %s \n", no->paramTypes);
            /*quando os parametros sao iguais*/
            if(strcmp(aux->paramTypes, no->paramTypes) == 0){
                printf("Line %d, col %d: Symbol %s%s already defined\n", noArv->numLinha, noArv->numColuna, no->name, no->paramTypes);
                exit(0);
            }else{
                //return 3;
                //printf("3\n");
            }

        /*quando não é igual*/
        }else{
            //return 0;
            //printf("0\n");
        }
        aux = aux->proximaClass;
    }
}

void symbolTabel(ARVORE noActual){
    ARVORE raiz = noActual;
    if(noActual != NULL){

        int numero = retornaNumero(noActual->tipoVariavel);
        switch(numero){
            case 1:{
                /*FieldDecl*/
                CLASSE no;
                no = (CLASSE)malloc(sizeof(CLSS));

                if(no != NULL){
                    no->name = strdup(noActual->filho->irmao->valor);
                    no->paramTypes = NULL;
                    if(strcmp(noActual->filho->tipoVariavel, "Bool") == 0){
                        no->type = strdup("boolean");
                    }else{
                        no->type = strdup(paraMinusculas(noActual->filho->tipoVariavel));
                    }
                    no->is_variavel = 1;
                    no->num_params = 0;
                    no->proximaClass = NULL;
                    no->proximoMethod = NULL;

                    //polimorfismo(no, noActual->filho->irmao);
                    ultimoNoClasse(tabelaSimbolos, no);
                }
            };break;
            case 4:{
                /*MethodHeader*/
                CLASSE no;
                no = (CLASSE)malloc(sizeof(CLSS));

                METHOD noAux;
                noAux = (METHOD)malloc(sizeof(MTHD));

                if(no != NULL){
                    no->name = strdup(noActual->filho->irmao->valor);
                    no->paramTypes = NULL;
                    if(strcmp(noActual->filho->tipoVariavel, "Bool") == 0){
                        no->type = strdup("boolean");
                    }else{
                        no->type = strdup(paraMinusculas(noActual->filho->tipoVariavel));
                    }
                    no->is_variavel = 0;
                    no->num_params = 0;
                    no->proximaClass = NULL;
                    no->proximoMethod = NULL;

                    /*adicionar o return - sempre o primeiro no a retornar*/
                    noAux->name = strdup("return");
                    if(strcmp(noActual->filho->tipoVariavel, "Bool") == 0){
                        noAux->type = strdup("boolean");
                    }else{
                        noAux->type = strdup(paraMinusculas(noActual->filho->tipoVariavel));
                    }
                    noAux->is_param = 0;
                    noAux->proximoMethod = NULL;

                    no->proximoMethod = noAux;
                }

                ARVORE aux = noActual->filho->irmao->irmao;
                ARVORE nomeFuncao = noActual->filho->irmao;
                paramDecl(aux, no, nomeFuncao);

                procurarNos(raiz, no);

                ultimoNoClasse(tabelaSimbolos, no);

                ARVORE aux2 = noActual->irmao;
                methodBody(aux2, no);                

            };break;
            case 8:{
                /*Program*/
                CLASSE no;
                no = (CLASSE)malloc(sizeof(CLSS));

                if(no != NULL){
                    no->name = strdup(noActual->filho->valor);
                    no->paramTypes = NULL;
                    no->type = NULL;
                    no->is_variavel = 1;
                    no->num_params = 0;
                    no->proximaClass = NULL;
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
                if(noActual->noAnotado == 1){
                    printf("%s(%s) - %s\n", noActual->tipoVariavel, noActual->valor, noActual->stringAST);    
                }else{
                    printf("%s(%s)\n", noActual->tipoVariavel, noActual->valor);
                }
            }else{
                for(int i=0; i < numFilhos; i++){
                    printf("..");
                }
                if(noActual->noAnotado == 1){
                    printf("%s - %s\n", noActual->tipoVariavel, noActual->stringAST);
                }else{
                    printf("%s\n", noActual->tipoVariavel);
                }
                
            }
        }
            
        if(noActual->filho != NULL){
            numFilhos += 1;
            imprimirASTAnotada(noActual->filho, error, numFilhos, flagImprimir);
            numFilhos -= 1;
        }

        if(noActual->irmao != NULL ){
            imprimirASTAnotada(noActual->irmao, error, numFilhos, flagImprimir);
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
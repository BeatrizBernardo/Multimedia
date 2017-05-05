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
    int i;
    for(i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
    return str;
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

int retornaNumero(char *tipoVariavel){
    if(strcmp(tipoVariavel, "FieldDecl") == 0){
        return 1;
    }else if(strcmp(tipoVariavel, "MethodHeader") == 0){
        return 2;
    }else if(strcmp(tipoVariavel, "Program") == 0){
        return 3;
    }else if(strcmp(tipoVariavel, "VarDecl") == 0){
        return 4;
    }else if((strcmp(tipoVariavel, "Eq") == 0) ||
          (strcmp(tipoVariavel, "Geq") == 0) ||
          (strcmp(tipoVariavel, "Gt") == 0) ||
          (strcmp(tipoVariavel, "Leq") == 0) ||
          (strcmp(tipoVariavel, "Lt") == 0) ||
          (strcmp(tipoVariavel, "Neq") == 0) ||
          (strcmp(tipoVariavel, "BoolLit") == 0) ||
          (strcmp(tipoVariavel, "And") == 0) ||
          (strcmp(tipoVariavel, "Or") == 0) ||
          (strcmp(tipoVariavel, "Not") == 0)){
        return 5;
    }else if((strcmp(tipoVariavel, "Length") == 0) || 
            (strcmp(tipoVariavel, "DecLit") == 0) ||
            (strcmp(tipoVariavel, "ParseArgs") == 0)){
        return 6;
    }else if(strcmp(tipoVariavel, "RealLit") == 0){
        return 7;
    }else if(strcmp(tipoVariavel, "StrLit") == 0){
        return 8;
    }else if(strcmp(tipoVariavel, "Id") == 0){
        return 9;
    }else if(strcmp(tipoVariavel, "Assign") == 0){
        return 10;
    }else if((strcmp(tipoVariavel, "Add") == 0) ||
            (strcmp(tipoVariavel, "Sub") == 0) ||
            (strcmp(tipoVariavel, "Mul") == 0) ||
            (strcmp(tipoVariavel, "Div") == 0) ||
            (strcmp(tipoVariavel, "Mod") == 0)){
        return 11;
    }else if((strcmp(tipoVariavel, "Plus") == 0) ||
            (strcmp(tipoVariavel, "Minus") == 0)){
        return 12;                
    }else if(strcmp(tipoVariavel, "Call") == 0){
        return 13;
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
            case 2:{
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
                ultimoNoClasse(tabelaSimbolos, no);
                /*para passar o irmao - MethodBody*/
                symbolTabel2(noActual->irmao, no, 0);
            };break;
            case 3:{
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

void symbolTabel2(ARVORE noActual, CLASSE tabela, int flagCall){
    int flagVarDecl = 0; //para não fazer os ids do VarDecl
    //flagCall -  para não fazer o id imediato ao Call
    if(noActual != NULL){

        int numero = retornaNumero(noActual->tipoVariavel);
        switch(numero){
            /*VarDecl*/
            case 4:{
                /*adicionar o VarDecl*/

                METHOD methodAux;
                //printf(" - - -  %s \n", noActual->tipoVariavel);

                methodAux = (METHOD)malloc(sizeof(MTHD));
                methodAux->name = strdup(noActual->filho->irmao->valor);
                if(strcmp(noActual->filho->tipoVariavel, "Bool") == 0){
                    methodAux->type = strdup("boolean");
                }else{
                    methodAux->type = strdup(paraMinusculas(noActual->filho->tipoVariavel));
                }
                methodAux->is_param = 0;
                methodAux->proximoMethod = NULL;
                ultimoNoMethod(tabela, methodAux);

                flagVarDecl = 1;
                flagCall = 0;
            };break;
            /*operadores lógicos*/
            case 5:{
                noActual->noAnotado = 1;
                noActual->stringAST = strdup("boolean");
                flagVarDecl = 0;
                flagCall = 0;
            };break;
            /*valores inteiros*/
            case 6:{
                noActual->noAnotado = 1;
                noActual->stringAST = strdup("int");
                flagVarDecl = 0;
                flagCall = 0;
            };break;
            /*valores reais*/
            case 7:{
                noActual->noAnotado = 1;
                noActual->stringAST = strdup("double");
                flagVarDecl = 0;
                flagCall = 0;
            };break;
            /*strings*/
            case 8:{
                noActual->noAnotado = 1;
                noActual->stringAST = strdup("String");
                flagVarDecl = 0;
                flagCall = 0;
            };break;
            /*IDS*/
            case 9:{
                //printf("--- %s %s -- %s\n", noActual->tipoVariavel, noActual->valor, tabela->name);
               // printf(" - ->> %s\n ", procurarTipoVariavel(noActual->valor, tabela));
                /*verificar se existe na tabela local - caso contrario na global*/
                if(flagVarDecl == 0 && flagCall == 0){
                    noActual->noAnotado = 1;
                    noActual->stringAST = strdup(procurarTipoVariavel(noActual->valor, tabela));
                }
                flagCall = 0;
            };break;
            /*Assign*/
            case 10:{
                flagVarDecl = 0;
                flagCall = 0;
                noActual->noAnotado = 1;
                noActual->stringAST = strdup(procurarTipoVariavel(noActual->filho->valor, tabela));
            };break;
            /*Operadores numericos*/
            case 11:{
                flagVarDecl = 0;
                flagCall = 0;
                if(noActual->filho != NULL && flagVarDecl == 0){
                    symbolTabel2(noActual->filho, tabela, flagCall);
                }
                //printf("@@@--->>->> %s %s ---- - %s\n", noActual->filho->tipoVariavel, noActual->filho->valor, noActual->filho->stringAST);
                //printf("@@@--->>->> %s %s ---  - - %s\n", noActual->filho->irmao->tipoVariavel, noActual->filho->irmao->valor, noActual->filho->irmao->stringAST);
                noActual->noAnotado = 1;
                noActual->stringAST = strdup(compararTipos(noActual->filho->stringAST,noActual->filho->irmao->stringAST));
                if(noActual->irmao != NULL){
                    symbolTabel2(noActual->irmao, tabela, flagCall);
                }
            };break;
            /*operadores unários*/
            case 12:{
                flagVarDecl = 0;
                flagCall = 0;
                if(noActual->filho != NULL && flagVarDecl == 0){
                    symbolTabel2(noActual->filho, tabela, flagCall);
                }
                noActual->noAnotado = 1;
                noActual->stringAST = strdup(noActual->filho->stringAST);
                if(noActual->irmao != NULL){
                    symbolTabel2(noActual->irmao, tabela, flagCall);
                }
            };break;
            /*Call*/
            case 13:{
                flagCall = 1;
                printf("@@@@@@ - %s\n", noActual->tipoVariavel);
            };break;
            /*default - outros*/
            case 0:{
                flagVarDecl = 0;
                flagCall = 0;
            };
        }

        if(noActual->filho != NULL && flagVarDecl == 0){
            symbolTabel2(noActual->filho, tabela, flagCall);
        }
        
        if(noActual->irmao != NULL){
            flagCall = 0;
            symbolTabel2(noActual->irmao, tabela, flagCall);
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

void imprimirASTAnotada(ARVORE noActual, int error, int numFilhos, int flagImprimir){
    int i;
    if(noActual != NULL){
        if(error ==  0 && flagImprimir == 0){
            if(noActual->valor != NULL){
                for(i=0; i < numFilhos; i++){
                    printf("..");
                }
                if(noActual->noAnotado == 1){
                    printf("%s(%s) - %s\n", noActual->tipoVariavel, noActual->valor, noActual->stringAST);    
                }else{
                    printf("%s(%s)\n", noActual->tipoVariavel, noActual->valor);
                }
            }else{
                for(i=0; i < numFilhos; i++){
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
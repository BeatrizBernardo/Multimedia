#ifndef ASTANOTADA_FILE
#define ASTANOTADA_FILE

#include "estruturas.h"

typedef struct method *METHOD;
typedef struct method{
    char *name;
    char *type;
    int is_param; /*0 - NO, 1 - YES*/
    METHOD proximoMethod;
}MTHD;

typedef struct classe *CLASSE;
typedef struct classe{
    char *name;
    char *paramTypes;
    char *type;
    int is_variavel; /*0 - não variavel, 1 - variavel*/
    CLASSE proximaClass;
    METHOD proximoMethod;
}CLSS;

void symbolTabel(ARVORE noActual);
int retornaNumero(char *tipoVariavel);
char *paraMinusculas(char *string);
void ultimoNoClasse(CLASSE tabela, CLASSE noActual);
void imprimirTabelaSimbolos();
void paramDecl(ARVORE noActual, CLASSE tabelaSimbolos);
void methodBody(ARVORE noActual, CLASSE tabelaSimbolos);
void imprimirTabelasMethod();
void ultimoNoMethod(CLASSE tabelaSimbolos, METHOD noActual);
#endif
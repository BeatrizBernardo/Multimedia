#ifndef ASTANOTADA_FILE
#define ASTANOTADA_FILE

#include "estruturas.h"

typedef struct method *METHOD;
typedef struct method{
    char *name;
    char *type;
    int is_param; /*0 - NO, 1 - YES*/
    METHOD maisMethod;
}MTHD;

typedef struct classe *CLASSE;
typedef struct classe{
    char *name;
    char *paramTypes;
    char *type;
    int is_param; /*0 - variavel nao global, 1 - global*/
    CLASSE proximaClass;
    METHOD proximoMethod;
}CLSS;

void symbolTabel(ARVORE noActual);
int retornaNumero(char *tipoVariavel);
char *paraMinusculas(char *string);
void ultimoNoClasse(CLASSE tabela, CLASSE noActual);
void imprimirTabelaSimbolos();
void inicializarTabelaSimbolos();
void paramDecl(ARVORE noActual, CLASSE tabelaSimbolos);
void methodBody(ARVORE noActual, CLASSE tabelaSimbolos);
void imprimirTabelasMethod();
void ultimoNoMethod(CLASSE tabelaSimbolos, METHOD noActual);
#endif
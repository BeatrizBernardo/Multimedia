#ifndef ASTANOTADA_FILE
#define ASTANOTADA_FILE

#include "estruturas.h"

typedef struct method *METHOD;
typedef struct method{
    char *name;
    char *type;
    int is_param;
    METHOD maisMethod;
}MTHD;

typedef struct classe *CLASSE;
typedef struct classe{
    char *name;
    char *paramTypes;
    char *type;
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
#endif
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
    char *type;     /*retorno*/
    int is_variavel; /*0 - não variavel, 1 - variavel*/
    int num_params;
    CLASSE proximaClass;
    METHOD proximoMethod;
}CLSS;

void symbolTabel(ARVORE noActual);
int retornaNumero(char *tipoVariavel);
char *paraMinusculas(char *string);
void ultimoNoClasse(CLASSE tabela, CLASSE noActual);
void imprimirTabelaSimbolos();
void paramDecl(ARVORE noActual, CLASSE tabelaSimbolos, ARVORE nomeFuncao);
void methodBody(ARVORE noActual, CLASSE tabelaSimbolos);
void imprimirTabelasMethod();
void ultimoNoMethod(CLASSE tabelaSimbolos, METHOD noActual);
void polimorfismo(CLASSE no, ARVORE noArv);
void imprimirASTAnotada(ARVORE noActual, int error, int numFilhos, int flagImprimir);
void nosAnotados(ARVORE noActual, CLASSE tabela);
char *procurarTipoVariavel(char *nome, CLASSE tabela);
char *procurarTipoParametrosMetodo(char *nome, CLASSE tabela);
char *procurarTipoRetornoMetodo(char *nome, CLASSE tabela);
void procurarNos(ARVORE noActual);
char *compararTipos(char *tipo1, char *tipo2);
#endif
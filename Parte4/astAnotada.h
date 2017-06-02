#ifndef ASTANOTADA_FILE
#define ASTANOTADA_FILE

#include "estruturas.h"

typedef struct method *METHOD;
typedef struct method{
    char *name;
    char *type;
    int is_param; /*0 - NO, 1 - YES*/
    int variavelTemporaria; /*variavel temporaria no LLVM*/
    METHOD proximoMethod; 
}MTHD;

typedef struct classe *CLASSE;
typedef struct classe{
    char *name;
    char *paramTypes;
    char *type;     /*retorno*/
    int is_variavel; /*0 - não variavel, 1 - variavel*/
    int num_params;
    int pos; /*marcar a posição na tabela global*/
    int variavelTemporaria; /*variavel temporaria no LLVM*/
    CLASSE proximaClass;
    METHOD proximoMethod;
}CLSS;

void symbolTabel(ARVORE noActual);
int retornaNumero(char *tipoVariavel);
char *paraMinusculas(char *string);
void ultimoNoClasse(CLASSE tabela, CLASSE noActual);
void imprimirTabelaSimbolos();
void paramDecl(ARVORE noActual, CLASSE tabelaSimbolos, ARVORE nomeFuncao);
void imprimirTabelasMethod();
void ultimoNoMethod(CLASSE tabelaSimbolos, METHOD noActual);
void imprimirASTAnotada(ARVORE noActual, int error, int numFilhos, int flagImprimir);
char *procurarTipoVariavel(char *nome, CLASSE tabela);
char *compararTipos(char *tipo1, char *tipo2);
void analiseAST(ARVORE raiz);
void symbolTabel2(ARVORE noActual, CLASSE tabela, int flagCall);
char *procurarTipoParametrosMetodo(ARVORE noActual, char *nome);
void pesquisarNomeMetodoTabela(ARVORE noActual, CLASSE auxClasse);
char *procurarTipoRetornoMetodo(char *nome, char *parametros);
CLASSE getSymbolTabel(ARVORE raiz);
#endif
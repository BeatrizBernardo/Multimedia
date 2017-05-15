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
    int pos; /*marcar a posição na tabela global*/
    CLASSE proximaClass;
    METHOD proximoMethod;
}CLSS;

void symbolTabel(ARVORE noActual);
int retornaNumero(char *tipoVariavel);
char *paraMinusculas(char *string);
void ultimoNoClasse(CLASSE tabela, CLASSE noActual);
void imprimirTabelaSimbolos();
void paramDecl(ARVORE noActual, CLASSE tabela, ARVORE nomeFuncao);
void methodBody(ARVORE noActual, CLASSE tabelaSimbolos);
void imprimirTabelasMethod();
void ultimoNoMethod(CLASSE tabelaSimbolos, METHOD noActual);
void polimorfismo(CLASSE no, ARVORE noArv);
void imprimirASTAnotada(ARVORE noActual, int error, int numFilhos, int flagImprimir);
void nosAnotadosBasicos(ARVORE noActual, CLASSE tabela, int is_Call);
char *procurarTipoVariavel(char *nome, CLASSE tabela);
void procurarNos(ARVORE noActual, CLASSE noClasse);
char *compararTipos(char *tipo1, char *tipo2);
void nosAnotadosOperadoresNumericos(ARVORE noActual, CLASSE tabela);
void nosAnotadosCall(ARVORE noActual, CLASSE tabela);
char *fazerParametros(ARVORE noActual);



void analiseAST(ARVORE raiz);
void symbolTabel2(ARVORE noActual, CLASSE tabela, int flagCall);
char *procurarTipoParametrosMetodo(ARVORE noActual, char *nome);
void pesquisarNomeMetodoTabela(ARVORE noActual, CLASSE auxClasse);
char *procurarTipoRetornoMetodo(char *nome, char *parametros);
void verificarRepeticaoClasse(CLASSE no, ARVORE noArv);
void verificarRepeticaoMetodo(CLASSE no, ARVORE noArv, METHOD method);
char *removechar(char *string);
void verificarRangeOutBounds(ARVORE noArv);
#endif
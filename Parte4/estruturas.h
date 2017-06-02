#ifndef ESTRUTURAS_FILE
#define ESTRUTURAS_FILE

typedef struct arvore *ARVORE;
typedef struct arvore{
    /*dados*/
    char* valor;
    char* tipoVariavel;
    /*AST*/
    int noAnotado; /*0 - NO, 1 - YES*/
    char* stringAST;
    /*posicao dos elementos*/
    int numLinha;
    int numColuna;

    /*posição na tabela global classe*/
    int pos;
    int tamanhoString;

    /*filho*/
    ARVORE filho;
    ARVORE irmao;
}ARV;

#endif

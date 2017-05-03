#ifndef ESTRUTURAS_FILE
#define ESTRUTURAS_FILE

typedef struct arvore *ARVORE;
typedef struct arvore{
    /*dados*/
    char* valor;
    char* tipoVariavel;
    /*posicao dos elementos*/
    int numLinha;
    int numColuna;
    /*filho*/
    ARVORE filho;
    ARVORE irmao;
}ARV;

#endif
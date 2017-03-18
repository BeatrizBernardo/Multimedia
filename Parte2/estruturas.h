#ifndef ESTRUTURAS_FILE
#define ESTRUTURAS_FILE

typedef struct arvore{
    /*dados*/
    char* valor;
    char* tipoVariavel;
    /*filho*/
    struct arvore *filho;
    struct arvore *irmao;
}ARVORE;

#endif
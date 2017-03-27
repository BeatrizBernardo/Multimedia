#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "ast.h"

/* Cada nó tem que ser criado, introduzindo o valor da variavel (p.e. 5) e o tipo da variavel (p.e. INT)
*  No final o nó deve ser devolvido outra vez
*/
ARVORE criarNo (char *tipoVariavel, char *valor){
    ARVORE no = (ARVORE)malloc(sizeof(ARV));
    if(no != NULL){
        strcpy(no->tipoVariavel,tipoVariavel);
        strcpy(no->valor, valor);
        //no->tipoVariavel = tipoVariavel;
        //no->valor = valor;
        no->filho = NULL;
        no->irmao = NULL;        
    }
    return no;
}

/* Os nós IRMAOS sao criados aqui. 
* A ideia é percorrer todos os nós irmaos de um no filho até ao ultimo 
* e só depois usar a função acima para criar o no: criarNo
*/
void criarIrmao(ARVORE noActual, ARVORE novoNo){
    while(noActual->irmao != NULL){
        noActual = noActual->irmao;
    }
    
    if(novoNo != NULL){
        noActual->irmao = novoNo;
    }else{
        noActual->irmao = criarNo("Null", "Null");
    }
}


void imprimirAST(ARVORE noActual){
    if(noActual != NULL){
        if(noActual->filho != NULL){
            imprimirAST(noActual->filho);
        }
        printf("variavel %s tipoVariavel %s", noActual->valor, noActual->tipoVariavel);
        if(noActual->irmao != NULL){
            imprimirAST(noActual->irmao);
        }
        
    }   
}
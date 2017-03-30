#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "ast.h"

/* Cada nó tem que ser criado, introduzindo o valor da variavel (p.e. 5) e o tipo da variavel (p.e. INT)
*  No final o nó deve ser devolvido outra vez
*/
ARVORE criarNo (char *tipoVariavel, char *valor){
    ARVORE no;
    no = (ARVORE)malloc(sizeof(ARV));

    if(no != NULL){
        /*NECESSÁRIO ALOCAR MEMORIA PARA O COPY DA STRING*/
        if(valor == NULL){
            no->valor = valor;
        }else{
            no->valor = strdup (valor); 
        }

        if(tipoVariavel == NULL){
            no->tipoVariavel = tipoVariavel;
        }else{
            no->tipoVariavel = strdup(tipoVariavel);
        }
        
        //no->valor = (char*)malloc(strlen(valor) + 1);
        //strcpy(no->valor, valor);
        
        no->filho = NULL;
        no->irmao = NULL;        
        //printf("<<<<<< >>>>>>><<<<<<<<<>>>>>>> %s\n", no->tipoVariavel);
    }
    return no;
}

/* Os nós IRMAOS sao criados aqui. 
* A ideia é percorrer todos os nós irmaos de um no filho até ao ultimo 
* e só depois usar a função acima para criar o no: criarNo
* Deve retornar o nó que é criado quando noActual não é NULL
*/
ARVORE criarIrmao(ARVORE noActual, ARVORE novoNo){
    if(noActual == NULL){
        return novoNo;
    }
    
    
    while(noActual->irmao != NULL){
        noActual = noActual->irmao;
    }
    
    noActual->irmao = novoNo;
    return noActual;
}


void imprimirAST(ARVORE noActual, int error, int numFilhos){
    if(error ==  0){
        //printf("aqui\n");
        //printf("kjsdkasjnd %s\n", noActual->tipoVariavel);
        if(noActual != NULL){
            if(noActual->valor != NULL){
                for(int i=0; i < numFilhos; i++){
                    printf("..");
                }
                printf("%s(%s)\n", noActual->tipoVariavel, noActual->valor);
            }else{
                for(int i=0; i < numFilhos; i++){
                    printf("..");
                }
                printf("%s\n", noActual->tipoVariavel);
            }
            
            //printf("oiw %s \n", noActual->filho->tipoVariavel);
            //printf("kdsm %s \n", noActual->irmao->tipoVariavel);

            if(noActual->filho != NULL){
                //printf("anksn %s \n", noActual->filho->valor);
                numFilhos += 1;
                imprimirAST(noActual->filho, error, numFilhos);
                numFilhos -= 1;
            }

            if(noActual->irmao != NULL ){
                //printf("ASDKJ %s \n", noActual->irmao->valor);
                imprimirAST(noActual->irmao, error, numFilhos);
            }
            
        } 
        
        /*if(noActual->tipoVariavel != NULL){
            free(noActual->tipoVariavel);
        }
        if(noActual->valor != NULL){
            free(noActual->valor);
        }
        free(noActual);*/
        
    }  
}

void freeArvore(ARVORE noActual){
    ARVORE auxiliar = noActual;
    while(auxiliar != NULL){
        if(auxiliar->filho != NULL){
            freeArvore(auxiliar->filho);
        }
        if(auxiliar->irmao != NULL){
            freeArvore(auxiliar->irmao);
        }
        free(auxiliar);
    }
}
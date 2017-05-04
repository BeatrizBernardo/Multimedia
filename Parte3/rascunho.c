else if(strcmp(noActual->tipoVariavel, "Call") == 0){
            printf("-<-<-<-<-<-- %s %s %s\n", noCall->tipoVariavel, noCall->valor, noCall->stringAST);
            ARVORE no = noActual;
            flagVarDecl = 0;
            noActual->noAnotado = 1;
            noActual->stringAST = strdup(noCall->stringAST);
            /*
            noActual = noActual->filho; 
            noActual->noAnotado = 1;
            noActual->stringAST = strdup(procurarTipoParametrosMetodo(noActual, noActual->valor, tabela, no));      
            */
            /*verificar se o irmao do ID é um CALL*/
            if(noActual->irmao != NULL){
                if(strcmp(noActual->irmao->tipoVariavel, "Call") == 0){
                    /*informação precisa para o Call*/
                    noCall = noActual;
                }
            }
        }else if(strcmp(noActual->tipoVariavel, "Assign") == 0){
            //printf("-<-<-<-<-<-- %s %s\n", noActual->filho->tipoVariavel, noActual->filho->valor);
            flagVarDecl = 0;
            noActual->noAnotado = 1;
            noActual->stringAST = strdup(procurarTipoVariavel(noActual->filho->valor, tabela));

            /*verificar se o irmao do ID é um CALL*/
            if(noActual->filho->irmao != NULL){
                if(strcmp(noActual->filho->irmao->tipoVariavel, "Call") == 0){
                    /*informação precisa para o Call*/
                    noCall = noActual->filho;
                }
            }
        }else 
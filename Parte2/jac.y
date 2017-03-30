%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"
    #include "estruturas.h"
    #include "ast.h"

    void yyerror (const char *s);
    int yylex(void);

    /*importa as variaveis do lex*/
    extern int lineNum;
    extern int columnNum;
    extern char *yytext; 
    extern int yyleng;

    /*importa do lex mas para AST*/
    extern ARVORE raiz;

    /*importa flag de error*/
    extern int error;

    /*para copia de Type no FieldDecl*/
    ARVORE copiaType;
        
%}

%union{
        char* string;   
        struct arvore *arv; /*definimos uma estrutura do tipo arvore*/
}

%type <arv> Program Program_2 FieldDecl FieldDecl_2 MethodDecl Type MethodHeader MethodBody MethodHeader_2 FormalParams MethodBody_2 VarDecl VarDecl_2 Statement FormalParams_2 Statement_2 Expr Expr2 Assignment MethodInvocation ParseArgs MethodInvocation_2

%token OCURV CCURV OBRACE CBRACE OSQUARE CSQUARE 
%token AND OR LT GT EQ NEQ LEQ GEQ PLUS MINUS STAR DIV MOD NOT ASSIGN SEMI COMMA
%token BOOL CLASS DO DOTLENGTH DOUBLE ELSE IF INT PARSEINT PRINT PUBLIC RETURN STATIC STRING VOID WHILE
%token <string> BOOLLIT
%token <string> RESERVED
%token <string> ID
%token <string> DECLIT
%token <string> REALLIT
%token <string> STRLIT


%left COMMA
%right ASSIGN
%left OR
%left AND
%left EQ NEQ 
%left LT LEQ GT GEQ 
%left PLUS MINUS
%left STAR DIV MOD
%right NOT 

%nonassoc IFX
%nonassoc ELSE

%%

Program: CLASS ID OBRACE Program_2 CBRACE   {   $$ = criarNo("Program", NULL);
                                                $$->filho = criarIrmao(criarNo("Id", $2),$4);
                                                raiz = $$;}
        ; 

/*deve repetir 0 ou + vezes  { FieldDecl | MethodDecl | SEMI } */
Program_2: Program_2 FieldDecl          {$$ = criarIrmao($1, $2);}   
        |Program_2 MethodDecl           {$$ = criarIrmao($1, $2);}   
        |Program_2 SEMI                 {$$ = $1;}
        |                               {$$ = NULL;}
        ;

FieldDecl: PUBLIC STATIC FieldDecl_2 SEMI               {$$ = $3;} 
        | error SEMI                                    {error = 1;}
        ;

/*deve repetir 0 ou + vezes { COMMA ID }*/
FieldDecl_2: FieldDecl_2 COMMA ID                       {       printf("--ss %s %s\n", $$->tipoVariavel, $$->valor);
                                                                $$->irmao = criarIrmao($$->irmao, criarNo("FieldDecl", "se"));

                                                                printf("--rr %s %s\n", $$->irmao->tipoVariavel, $$->irmao->valor);
                                                                
                                                                $$->irmao->filho = criarNo(copiaType->tipoVariavel, NULL);
                                                                $$->irmao->filho= criarIrmao($$->irmao->filho, criarNo("Id", $3));
                                                                
                                                                //printf("--ddd %s %s\n", $$->irmao->filho->tipoVariavel, $$->irmao->filho->valor);
                                                                //printf("--ddd %s %s\n", $$->irmao->filho->irmao->tipoVariavel, $$->irmao->filho->irmao->valor);
                                                        }
        | Type ID                                       {       
                                                                $$ = criarNo("FieldDecl", "pr"); 
                                                                //$$->filho = $1; 
                                                                copiaType = $1;
                                                                $$->filho = criarIrmao($1, criarNo("Id", $2));
                                                                //$$->irmao=NULL;
                                                        }
        ;

MethodDecl: PUBLIC STATIC MethodHeader MethodBody       {$$ = criarNo("MethodDecl", NULL); $$->filho = criarIrmao($3, $4);}
        ;

MethodHeader: Type ID OCURV MethodHeader_2 CCURV        {       $$ = criarNo("MethodHeader", NULL); 
                                                                $$->filho = $1; 
                                                                $$->filho = criarIrmao($$->filho, criarNo("Id", $2)); 
                                                                $$->filho = criarIrmao($$->filho, $4);
                                                        }
        |VOID ID OCURV MethodHeader_2 CCURV             {       $$ = criarNo("MethodHeader", NULL); 
                                                                $$->filho = criarIrmao(criarNo("Void", NULL), criarNo("Id", $2)); 
                                                                $$->filho = criarIrmao($$->filho, $4);
                                                        }
        ;

/*deve ser opcional - sim ou não - [ FormalParams ]*/        
MethodHeader_2: FormalParams            {                                                      
                                                $$ = criarNo("MethodParams", NULL); 
                                                $$ = $1;
                                        }
        |                               {$$ = NULL;}
        ;

MethodBody: OBRACE MethodBody_2 CBRACE          {$$ = $2;}
        ;

/*deve repetir 0 ou + vezes { VarDecl | Statement }*/
MethodBody_2: MethodBody_2 VarDecl              {$$ = $1; $$ = criarIrmao($1, $2);}
        |MethodBody_2 Statement                 {$$ = $1; $$ = criarIrmao($1, $2);}
        |                                       {$$ = NULL;}
        ;

FormalParams: FormalParams_2                    {$$ = $1;}
        | STRING OSQUARE CSQUARE ID             {       $$ = criarNo("ParamDecl", NULL);
                                                        $$->filho = criarIrmao(criarNo("StringArray", NULL), criarNo("Id", $4));
                                                }
        ;
  
/*deve repetir 0 ou + vezes { COMMA Type ID }*/
FormalParams_2:FormalParams_2 COMMA Type ID     {       $$->irmao = criarNo("ParamDecl", NULL); 
                                                        $$->irmao->filho = criarIrmao($3, criarNo("Id", $4));
                                                }
        | Type ID                               {       $$ = criarNo("ParamDecl", NULL);
                                                        $$->filho = criarIrmao($1, criarNo("Id", $2));
                                                }
        ;

VarDecl: VarDecl_2 SEMI          {$$ = $1;}
        ;

/*deve repetir 0 ou + vezes { COMMA ID }*/
VarDecl_2: VarDecl_2 COMMA ID           {       $$->irmao = criarIrmao($$->irmao, criarNo("VarDecl", NULL));
                                                $$->irmao->filho = criarIrmao(criarNo(copiaType->tipoVariavel, copiaType->valor), criarNo("Id", $3));
                                        }
        | Type ID                       {       $$ = criarNo("VarDecl", NULL);
                                                copiaType = $1;
                                                $$->filho = criarIrmao($1, criarNo("Id", $2));
                                        }
        ;

Type: BOOL              {$$ = criarNo("Bool", NULL);}      
    | INT               {$$ = criarNo("Int", NULL);}          /*porque são tipos, não tem "valor"*/
    | DOUBLE            {$$ = criarNo("Double", NULL);}
    ;

Statement: OBRACE Statement_2 CBRACE                            {$$ = $2;}
        | IF OCURV Expr CCURV Statement %prec IFX               {       $$ = criarNo("If", NULL); 
                                                                        $$->filho = criarIrmao($3, $5);
                                                                }
        | IF OCURV Expr CCURV Statement ELSE Statement          {       $$ = criarNo("If", NULL);                                                                        $$->filho = $3; 
                                                                        $$->filho = criarIrmao($3, $5); 
                                                                        $$->filho = criarIrmao($$->filho, $7);
                                                                }
        | WHILE OCURV Expr CCURV Statement                      {       $$ = criarNo("While", NULL); 
                                                                        $$->filho = criarIrmao($3, $5);
                                                                }
        | DO Statement WHILE OCURV Expr CCURV SEMI              {       $$ = criarNo("DoWhile", NULL);
                                                                        $$->filho = criarIrmao($2, $5);
                                                                }
        | PRINT OCURV Expr CCURV SEMI                           {       $$ = criarNo("Print", NULL); 
                                                                        $$->filho = $3;
                                                                }
        | PRINT OCURV STRLIT CCURV SEMI                         {$$ = criarNo("Print", $3);}
        | Assignment SEMI                                       {$$ = $1;}
        | MethodInvocation SEMI                                 {$$ = $1;}
        | ParseArgs SEMI                                        {$$ = $1;}
        | SEMI                                                  {;}
        | RETURN SEMI                                           {$$ = criarNo("Return", NULL);}
        | RETURN Expr SEMI                                      {$$ = criarNo("Return", NULL); $$->filho = $2;}
        | error SEMI                                            {error = 1;}
        ;

/*deve repetir 0 ou + vezes { Statement }*/
Statement_2:Statement_2 Statement       {$$ = $1; $$ = criarIrmao($1, $2);}
        |                               {$$ = NULL;}
        ;

Assignment: ID ASSIGN Expr      {       $$ = criarNo("Assign", NULL); 
                                        $$->filho = criarIrmao(criarNo("Id", $1), $3);
                                }
        ;

MethodInvocation: ID OCURV CCURV                                {$$ = criarNo("Id", NULL);}
        |ID OCURV Expr MethodInvocation_2 CCURV                 {       $$ = criarNo("Id", NULL); 
                                                                        $$->filho = criarIrmao($3, $4);
                                                                }
        |ID OCURV error CCURV                                   {error = 1;}
        ;

/*deve repetir 0 ou + vezes { COMMA Expr }*/
MethodInvocation_2: MethodInvocation_2 COMMA Expr               {$$ = $1; $$ = criarIrmao($1, $3);}
        |                                                       {$$ = NULL;}
        ;

ParseArgs: PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV         {       $$ = criarNo("ParseArgs", NULL); 
                                                                        $$->filho = criarIrmao(criarNo("Id", $3), $5);}
        | PARSEINT OCURV error CCURV                            {error = 1;}
        ;

Expr2:MethodInvocation                  {$$ = $1;}              /*E' -> € {E'.n = E'.i}*/             
    | ParseArgs                         {$$ = $1;}
    | Expr2 AND Expr2                   {$$ = criarNo("And", NULL); $$->filho = criarIrmao($1, $3);} /*AND vai para o topo da pilha, está no topo e a este vamos acrescentar um filho Expr e a este um irmão Expr*/
    | Expr2 OR Expr2                    {$$ = criarNo("Or", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 EQ Expr2                    {$$ = criarNo("Eq", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 GEQ Expr2                   {$$ = criarNo("Geq", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 GT Expr2                    {$$ = criarNo("Gt", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 LEQ Expr2                   {$$ = criarNo("Leq", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 LT Expr2                    {$$ = criarNo("Lt", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 NEQ Expr2                   {$$ = criarNo("Neq", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 PLUS Expr2                  {$$ = criarNo("Plus", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 MINUS Expr2                 {$$ = criarNo("Minus", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 STAR Expr2                  {$$ = criarNo("Star", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 DIV Expr2                   {$$ = criarNo("Div", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 MOD Expr2                   {$$ = criarNo("Mod", NULL);  $$->filho = criarIrmao($1, $3);}
    | NOT Expr2                         {$$ = criarNo("Not", NULL); $$->filho = $2;}   
    | PLUS Expr2      %prec NOT         {$$ = criarNo("Plus", NULL); $$->filho = $2;}              /*E'->NAND T E'1 {E'1.i = mknode("NAND", E'.i, Tn)}*/
    | MINUS Expr2     %prec NOT         {$$ = criarNo("Minus", NULL); $$->filho = $2;}                   /*O meu nó actual (Minus) vai ser irmão do novo nó (Expr), que no final estará no posso da pilha $$*/
    | ID                                {$$ = criarNo("Id", $1);}      /*T->ID  {T.n = mkleaf("Id", ID.lexval)}*/
    | ID DOTLENGTH                      {$$ = criarNo("Length", NULL); $$->filho = criarNo("Id", $1);} 
    | BOOLLIT                           {$$ = criarNo("BoolLit", $1);}
    | DECLIT                            {$$ = criarNo("DecLit", $1);}
    | REALLIT                           {$$ = criarNo("RealLit", $1);}
    | OCURV Expr CCURV                  {$$ = $2;}                      /*T->(E) {T.n = E.n}*/
    | OCURV error CCURV                 {error = 1;}
    ;

Expr:  Assignment       {$$ = $1;}              
    | Expr2             {$$ = $1;}
    ;
%%

void yyerror (const char *s) {      
        printf ("Line %d, col %d: %s: %s\n", lineNum, columnNum-(int)yyleng, s, yytext); 
}
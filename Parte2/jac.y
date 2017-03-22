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
    extern ARVORE *raiz;
    
%}

%union{
        char* string;   
        struct arvore *arv; /*definimos uma estrutura do tipo arvore*/
}

%type <arv> Program Program_2 FieldDecl MethodDecl

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
%left OCURV CCURV OSQUARE CSQUARE

%nonassoc IFX
%nonassoc ELSE

%%

Program: CLASS ID OBRACE Program_2 CBRACE   {raiz = criarNo("Program", "Null"); raiz->filho = $4;}
        ;

/*deve repetir 0 ou + vezes  { FieldDecl | MethodDecl | SEMI } */
Program_2: Program_2 FieldDecl          {$$ = $1; criarIrmao($$, $2);}
        |Program_2 MethodDecl           {$$ = $1; criarIrmao($$, $2);}
        |Program_2 SEMI                 {$$ = $1;}
        |                               {;}
        ;

FieldDecl: PUBLIC STATIC Type ID comma_id SEMI          {;}
        | error SEMI                                    {;}
        ;

/*deve repetir 0 ou + vezes { COMMA ID }*/
comma_id: comma_id COMMA ID                     {;}
        |                                       {;}
        ;

MethodDecl: PUBLIC STATIC MethodHeader MethodBody
        ;

MethodHeader: Type ID OCURV MethodHeader_2 CCURV 
        |VOID ID OCURV MethodHeader_2 CCURV 
        ;

/*deve ser opcional - sim ou não - [ FormalParams ]*/        
MethodHeader_2: FormalParams
        |
        ;

MethodBody: OBRACE MethodBody_2 CBRACE
        ;

/*deve repetir 0 ou + vezes { VarDecl | Statement }*/
MethodBody_2: MethodBody_2 VarDecl
        |MethodBody_2 Statement
        |
        ;

FormalParams: Type ID FormalParams_2
        ;

/*deve repetir 0 ou + vezes { COMMA Type ID }*/
FormalParams_2:FormalParams_2 COMMA Type ID
        |
        ;

FormalParams: STRING OSQUARE CSQUARE ID 
        ;

VarDecl: Type ID comma_id SEMI
        ;

Type: BOOL              {$$ = criarNo("Bool", "Null");}      
    | INT               {$$ = criarNo("Int", "Null");}          /*porque são tipos, não tem "valor"*/
    | DOUBLE            {$$ = criarNo("Double", "Null");}
    ;

Statement: OBRACE Statement_2 CBRACE
        | IF OCURV Expr CCURV Statement %prec IFX
        | IF OCURV Expr CCURV Statement ELSE Statement
        | WHILE OCURV Expr CCURV Statement 
        | DO Statement WHILE OCURV Expr CCURV SEMI 
        | PRINT OCURV Expr CCURV SEMI
        | PRINT OCURV STRLIT CCURV SEMI
        | Assignment SEMI
        | MethodInvocation SEMI
        | ParseArgs SEMI 
        | RETURN SEMI 
        | RETURN Expr SEMI
        | error SEMI;
        ;

/*deve repetir 0 ou + vezes { Statement }*/
Statement_2:Statement_2 Statement
        |
        ;

Assignment: ID ASSIGN Expr 
        ;

MethodInvocation: ID OCURV CCURV 
        |ID OCURV Expr MethodInvocation_2 CCURV
        ;

/*deve repetir 0 ou + vezes { COMMA Expr }*/
MethodInvocation_2: MethodInvocation_2 COMMA Expr
        |
        ;

ParseArgs: PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV 
        | PARSEINT OCURV error CCURV
        ;

Expr: Assignment                {$$ = $1;}              /*E' -> € {E'.n = E'.i}*/
    | MethodInvocation          {$$ = $1;}
    | ParseArgs                 {$$ = $1;}
    | Expr AND Expr             {$$ = $1; $$->irmao = criarIrmao(criarNo("And", "Null"), $2);} /*Expr vai para o topo da pilha, está no topo e a este vamos acrescentar um irmao (AND) e a este outro irmão Expr*/
    | Expr OR Expr 
    | Expr EQ Expr
    | Expr GEQ Expr
    | Expr GT Expr
    | Expr LEQ Expr
    | Expr LT Expr
    | Expr NEQ Expr 
    | Expr PLUS Expr
    | Expr MINUS Expr
    | Expr STAR Expr
    | Expr DIV Expr
    | Expr MOD Expr 
    | PLUS Expr                 {$$ = criarIrmao(criarNo("Plus", "Null"), $2);}              /*E'->NAND T E'1 {E'1.i = mknode("NAND", E'.i, Tn)}*/
    | MINUS Expr                {$$ = criarIrmao(criarNo("Minus", "Null"), $2);}                /*O meu nó actual (Minus) vai ser irmão do novo nó (Expr), que no final estará no posso da pilha $$*/
    | NOT Expr                  {$$ = criarIrmao(criarNo("Not", "Null"), $2);}
    | ID                        {$$ = criarNo("Id", $1);}      /*T->ID  {T.n = mkleaf("Id", ID.lexval)}*/
    | ID DOTLENGTH              
    | OCURV Expr CCURV          {$$ = $2;}                      /*T->(E) {T.n = E.n}*/
    | BOOLLIT                   {$$ = criarNo("BoolLit", $1);}
    | DECLIT                    {$$ = criarNo("DecLit", $1);}
    | REALLIT                   {$$ = criarNo("RealLit", $1);}
    | OCURV error CCURV         {;}
    ;

%%

void yyerror (const char *s) {      
        printf ("Line %d, col %d: %s: %s\n", lineNum, columnNum-(int)yyleng, s, yytext); 
}
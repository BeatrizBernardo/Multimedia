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
    
%}

%union{
        char* string;   
        struct arvore *arv; /*definimos uma estrutura do tipo arvore*/
}

%type <arv> Program Program_2 FieldDecl MethodDecl Type comma_id MethodHeader MethodBody MethodHeader_2 FormalParams MethodBody_2 VarDecl Statement FormalParams_2 Statement_2 Expr Assignment MethodInvocation ParseArgs MethodInvocation_2

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

FieldDecl: PUBLIC STATIC Type ID comma_id SEMI          {$$ = criarNo("FieldDecl", "Null"); $$->filho = $3; criarIrmao($$->filho, criarNo("Id", $4)); criarIrmao($$->filho, $5);}
        | error SEMI                                    {;}
        ;

/*deve repetir 0 ou + vezes { COMMA ID }*/
comma_id: comma_id COMMA ID                     {$$ = $1; criarIrmao($$, criarNo("Id", $3));}
        |                                       {;}
        ;

MethodDecl: PUBLIC STATIC MethodHeader MethodBody       {$$ = criarNo("MethodDecl", "Null"); criarIrmao($$->filho, $3); criarIrmao($$->filho, $4);}
        ;

MethodHeader: Type ID OCURV MethodHeader_2 CCURV        {$$ = criarNo("MethodHeader", "Null"); $$->filho = $1; criarIrmao($$->filho, criarNo("Id", $2)); criarIrmao($$->filho, $4);}
        |VOID ID OCURV MethodHeader_2 CCURV             {$$ = criarNo("MethodHeader", "Null"); $$->filho = criarNo("Void", "Null"); criarIrmao($$->filho, criarNo("Id", $2)); criarIrmao($$->filho, $4);}
        ;

/*deve ser opcional - sim ou não - [ FormalParams ]*/        
MethodHeader_2: FormalParams            {$$ = $1;}
        |                               {;}
        ;

MethodBody: OBRACE MethodBody_2 CBRACE          {$$ = $2;}
        ;

/*deve repetir 0 ou + vezes { VarDecl | Statement }*/
MethodBody_2: MethodBody_2 VarDecl              {$$ = $1; criarIrmao($$, $2);}
        |MethodBody_2 Statement                 {$$ = $1; criarIrmao($$, $2);}
        |                                       {;}
        ;

FormalParams: Type ID FormalParams_2            {$$ = $1; criarIrmao($$, criarNo("Id", $2)); criarIrmao($$, $3);}
        ;

/*deve repetir 0 ou + vezes { COMMA Type ID }*/
FormalParams_2:FormalParams_2 COMMA Type ID             {$$ = $1; criarIrmao($$, $3); criarIrmao($$, criarNo("Id", $4));}
        |                                               {;}
        ;

FormalParams: STRING OSQUARE CSQUARE ID         {criarIrmao($$, criarNo("Id", $4));}
        ;

VarDecl: Type ID comma_id SEMI          {$$ = criarNo("VarDecl", "Null"); $$->filho = $1; criarIrmao($$->filho, criarNo("Id", $2));}
        ;

Type: BOOL              {$$ = criarNo("Bool", "Null");}      
    | INT               {$$ = criarNo("Int", "Null");}          /*porque são tipos, não tem "valor"*/
    | DOUBLE            {$$ = criarNo("Double", "Null");}
    ;

Statement: OBRACE Statement_2 CBRACE                            {$$ = $2;}
        | IF OCURV Expr CCURV Statement %prec IFX               {$$ = criarNo("If", "Null"); $$->filho = $3; criarIrmao($$->filho, $5);}
        | IF OCURV Expr CCURV Statement ELSE Statement          {$$ = criarNo("If", "Null"); $$->filho = $3; criarIrmao($$->filho, $5); criarIrmao($$->filho, $7);}
        | WHILE OCURV Expr CCURV Statement                      {$$ = criarNo("While", "Null"); $$->filho = $3; criarIrmao($$->filho, $5);}
        | DO Statement WHILE OCURV Expr CCURV SEMI              {$$ = criarNo("DoWhile", "Null"); $$->filho = $2; criarIrmao($$->filho, $5);}
        | PRINT OCURV Expr CCURV SEMI                           {$$ = criarNo("Print", "Null"); $$->filho = $3;}
        | PRINT OCURV STRLIT CCURV SEMI                         {$$ = criarNo("Print", $3);}
        | Assignment SEMI                                       {$$ = $1;}
        | MethodInvocation SEMI                                 {$$ = $1;}
        | ParseArgs SEMI                                        {$$ = $1;}
        | RETURN SEMI                                           {$$ = criarNo("Return", "Null");}
        | RETURN Expr SEMI                                      {$$ = criarNo("Return", "Null"); $$->filho = $2;}
        | error SEMI                                            {;}
        ;

/*deve repetir 0 ou + vezes { Statement }*/
Statement_2:Statement_2 Statement       {$$ = $1; criarIrmao($$, $2);}
        |                               {;}
        ;

Assignment: ID ASSIGN Expr      {$$ = criarNo("Assign", "Null"); $$->filho = criarNo("Id", $1); criarIrmao($$->filho, $3);}
        ;

MethodInvocation: ID OCURV CCURV                                {$$ = criarNo("Id", "Null");}
        |ID OCURV Expr MethodInvocation_2 CCURV                 {$$ = criarNo("Id", "Null"); $$->filho = $3; criarIrmao($$->filho, $4);}
        ;

/*deve repetir 0 ou + vezes { COMMA Expr }*/
MethodInvocation_2: MethodInvocation_2 COMMA Expr               {$$ = $1; criarIrmao($$, $3);}
        |                                                       {;}
        ;

ParseArgs: PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV         {$$ = criarNo("ParseArgs", "Null"); $$->filho = criarNo("Id", $3); criarIrmao($$->filho, $5);}
        | PARSEINT OCURV error CCURV                            {;}
        ;

Expr: Assignment                {$$ = $1;}              /*E' -> € {E'.n = E'.i}*/
    | MethodInvocation          {$$ = $1;}
    | ParseArgs                 {$$ = $1;}
    | Expr AND Expr             {$$ = criarNo("And", "Null"); $$->filho = $1; criarIrmao($$->filho, $3);} /*AND vai para o topo da pilha, está no topo e a este vamos acrescentar um filho Expr e a este um irmão Expr*/
    | Expr OR Expr              {$$ = criarNo("Or", "Null"); $$->filho = $1; criarIrmao($$->filho, $3);}
    | Expr EQ Expr              {$$ = criarNo("Eq", "Null"); $$->filho = $1; criarIrmao($$->filho, $3);}
    | Expr GEQ Expr             {$$ = criarNo("Geq", "Null"); $$->filho = $1; criarIrmao($$->filho, $3);}
    | Expr GT Expr              {$$ = criarNo("Gt", "Null"); $$->filho = $1; criarIrmao($$->filho, $3);}
    | Expr LEQ Expr             {$$ = criarNo("Leq", "Null"); $$->filho = $1; criarIrmao($$->filho, $3);}
    | Expr LT Expr              {$$ = criarNo("Lt", "Null"); $$->filho = $1; criarIrmao($$->filho, $3);}
    | Expr NEQ Expr             {$$ = criarNo("Neq", "Null"); $$->filho = $1; criarIrmao($$->filho, $3);}
    | Expr PLUS Expr            {$$ = criarNo("Plus", "Null"); $$->filho = $1; criarIrmao($$->filho, $3);}
    | Expr MINUS Expr           {$$ = criarNo("Minus", "Null"); $$->filho = $1; criarIrmao($$->filho, $3);}
    | Expr STAR Expr            {$$ = criarNo("Star", "Null"); $$->filho = $1; criarIrmao($$->filho, $3);}
    | Expr DIV Expr             {$$ = criarNo("Div", "Null"); $$->filho = $1; criarIrmao($$->filho, $3);}
    | Expr MOD Expr             {$$ = criarNo("Mod", "Null"); $$->filho = $1; criarIrmao($$->filho, $3);}
    | PLUS Expr                 {$$ = criarNo("Plus", "Null"); $$->filho = $2;}              /*E'->NAND T E'1 {E'1.i = mknode("NAND", E'.i, Tn)}*/
    | MINUS Expr                {$$ = criarNo("Minus", "Null"); $$->filho = $2;}                   /*O meu nó actual (Minus) vai ser irmão do novo nó (Expr), que no final estará no posso da pilha $$*/
    | NOT Expr                  {$$ = criarNo("Not", "Null"); $$->filho = $2;}   
    | ID                        {$$ = criarNo("Id", $1);}      /*T->ID  {T.n = mkleaf("Id", ID.lexval)}*/
    | ID DOTLENGTH              {$$ = criarNo("Id", $1);} 
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
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

    /*para copiar*/
    ARVORE copia;
        
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
                                                $$->filho = criarIrmao(criarNo("Id", $2),$4); free($2);
                                                raiz = $$; }
        ; 

/*deve repetir 0 ou + vezes  { FieldDecl | MethodDecl | SEMI } */
Program_2: Program_2 FieldDecl          {$$ = criarIrmao($1, $2);}   
        |Program_2 MethodDecl           {$$ = criarIrmao($1, $2);}   
        |Program_2 SEMI                 {$$ = $1;}
        |                               {$$ = NULL;}
        ;

FieldDecl: PUBLIC STATIC FieldDecl_2 SEMI               {$$ = $3;} 
        | error SEMI                                    {$$ = criarNo("Error", NULL); error = 1;}
        ;

/*deve repetir 0 ou + vezes { COMMA ID }*/
FieldDecl_2: FieldDecl_2 COMMA ID                       {       $$ = criarIrmao($1, copia=criarNo("FieldDecl", NULL));
                                                                copia->filho = criarIrmao(criarNo($$->filho->tipoVariavel, $$->filho->valor), criarNo("Id", $3));
                                                                free($3);
                                                        }
        | Type ID                                       {       $$ = criarNo("FieldDecl", NULL); 
                                                                $$->filho = criarIrmao($1, criarNo("Id", $2)); free($2);
                                                        }
        ;

MethodDecl: PUBLIC STATIC MethodHeader MethodBody       {$$ = criarNo("MethodDecl", NULL); $$->filho = criarIrmao($3, $4);}
        ;

MethodHeader: Type ID OCURV MethodHeader_2 CCURV        {       $$ = criarNo("MethodHeader", NULL); 
                                                                $$->filho = $1; 
                                                                $$->filho = criarIrmao($$->filho, criarNo("Id", $2)); free($2);
                                                                $$->filho = criarIrmao($$->filho, $4);
                                                        }
        |VOID ID OCURV MethodHeader_2 CCURV             {       $$ = criarNo("MethodHeader", NULL); 
                                                                $$->filho = criarIrmao(criarNo("Void", NULL), criarNo("Id", $2)); free($2);
                                                                $$->filho = criarIrmao($$->filho, $4);
                                                        }
        ;

/*deve ser opcional - sim ou não - [ FormalParams ]*/        
MethodHeader_2: FormalParams            {$$ = $1;}
        |                               {$$ = criarNo("MethodParams", NULL); $$->filho = NULL;}
        ;

MethodBody: OBRACE MethodBody_2 CBRACE          {$$ = criarNo("MethodBody", NULL); $$->filho = $2;}
        ;

/*deve repetir 0 ou + vezes { VarDecl | Statement }*/
MethodBody_2: MethodBody_2 VarDecl              {$$ = $1; $$ = criarIrmao($1, $2);}
        |MethodBody_2 Statement                 {       $$ = $1; 
                                                        if($2 != NULL){
                                                                if($2->irmao != NULL){
                                                                        $$ = criarIrmao($1, copia = criarNo("Block", NULL));
                                                                        copia->filho = $2;
                                                                }else{
                                                                      $$ = criarIrmao($1, $2);  
                                                                }
                                                        }else{
                                                                $$ = criarIrmao($1, $2);
                                                        }
                                                }
        |                                       {$$ = NULL;}
        ;

FormalParams: FormalParams_2                    {$$ = criarNo("MethodParams", NULL); $$->filho = $1;}
        | STRING OSQUARE CSQUARE ID             {       $$ = criarNo("MethodParams", NULL);
                                                        $$->filho = criarNo("ParamDecl", NULL);
                                                        $$->filho->filho = criarIrmao(criarNo("StringArray", NULL), criarNo("Id", $4));free($4);
                                                }
        ;
  
/*deve repetir 0 ou + vezes { COMMA Type ID }*/
FormalParams_2:FormalParams_2 COMMA Type ID     {       $$ = criarIrmao($1, copia=criarNo("ParamDecl", NULL));
                                                        copia->filho = criarIrmao($3, criarNo("Id", $4)); free($4);
                                                }
        | Type ID                               {       $$ = criarNo("ParamDecl", NULL);
                                                        $$->filho = criarIrmao($1, criarNo("Id", $2)); free($2);
                                                }
        ;

VarDecl: VarDecl_2 SEMI          {$$ = $1;}
        ;

/*deve repetir 0 ou + vezes { COMMA ID }*/
VarDecl_2: VarDecl_2 COMMA ID           {       $$ = criarIrmao($1, copia=criarNo("VarDecl", NULL));
                                                copia->filho = criarIrmao(criarNo($$->filho->tipoVariavel, $$->filho->valor), criarNo("Id", $3));
                                                free($3);
                                        }
        | Type ID                       {       $$ = criarNo("VarDecl", NULL); 
                                                $$->filho = criarIrmao($1, criarNo("Id", $2)); free($2);
                                        }
        ;

Type: BOOL              {$$ = criarNo("Bool", NULL);}      
    | INT               {$$ = criarNo("Int", NULL);}          /*porque são tipos, não tem "valor"*/
    | DOUBLE            {$$ = criarNo("Double", NULL);}
    ;

Statement: OBRACE Statement_2 CBRACE                            {       if($2 != NULL){
                                                                                if($2->irmao != NULL){
                                                                                        $$ = criarNo("Block", NULL);
                                                                                        $$->filho = $2;
                                                                                }else{
                                                                                        $$ = $2;
                                                                                }
                                                                        }else{
                                                                                $$ = $2;
                                                                        }
                                                                }
        | IF OCURV Expr CCURV Statement %prec IFX               {       $$ = criarNo("If", NULL); 
                                                                        if($5 != NULL){
                                                                                if($5->irmao != NULL){
                                                                                        $$->filho = criarIrmao($3, copia = criarNo("Block", NULL));
                                                                                        copia->filho = criarIrmao($5, criarNo("Block", NULL));
                                                                                }else{
                                                                                        $$->filho = criarIrmao(criarIrmao($3, $5), criarNo("Block", NULL));
                                                                                }
                                                                        }else{
                                                                                $$->filho = criarIrmao($3, criarIrmao(criarNo("Block", NULL), criarNo("Block", NULL)));
                                                                        }
                                                                        
                                                                }
        | IF OCURV Expr CCURV Statement ELSE Statement         {        $$ = criarNo("If", NULL); 
                                                                        if($5 != NULL){
                                                                                if($5->irmao != NULL){
                                                                                        $$->filho = criarIrmao($3, copia = criarNo("Block", NULL));
                                                                                        copia->filho = criarIrmao($5, criarNo("Block", NULL));
                                                                                }else{
                                                                                        $$->filho = criarIrmao($3, $5);
                                                                                }
                                                                        }else{
                                                                                $$->filho = criarIrmao($3,  criarNo("Block", NULL));
                                                                        }
                                                                        
                                                                        if($7 != NULL){
                                                                                if($7->irmao != NULL){
                                                                                        $$->filho = criarIrmao($$->filho, copia = criarNo("Block", NULL));
                                                                                        copia->filho = $7;
                                                                                }else{
                                                                                        $$->filho = criarIrmao($$->filho, $7);
                                                                                }
                                                                        }else{
                                                                               $$->filho = criarIrmao($$->filho, criarNo("Block", NULL));
                                                                        }
                                                                        
                                                                }
        | WHILE OCURV Expr CCURV Statement                      {       $$ = criarNo("While", NULL); 
                                                                        if($5 != NULL){
                                                                                if($5->irmao != NULL){
                                                                                        $$->filho = criarIrmao($3, copia = criarNo("Block", NULL));
                                                                                        copia->filho = $5;
                                                                                }else{
                                                                                        $$->filho = criarIrmao($3, $5);
                                                                                }
                                                                        }else{                                                                                                                          
                                                                                $$->filho = criarIrmao($3, criarNo("Block", NULL));
                                                                        }
                                                                }
        | DO Statement WHILE OCURV Expr CCURV SEMI              {       $$ = criarNo("DoWhile", NULL);
                                                                        if($2 != NULL){
                                                                                if($2->irmao != NULL){
                                                                                        $$->filho = criarIrmao(copia = criarNo("Block", NULL), $5);
                                                                                        copia->filho = $2;
                                                                                }else{
                                                                                        $$->filho = criarIrmao($2, $5);
                                                                                }
                                                                        }else{
                                                                             $$->filho = criarIrmao(criarNo("Block", NULL), $5);
                                                                        }
                                                                        
                                                                }
        | PRINT OCURV Expr CCURV SEMI                           {       $$ = criarNo("Print", NULL); 
                                                                        $$->filho = $3;
                                                                }
        | PRINT OCURV STRLIT CCURV SEMI                         {$$ = criarNo("Print", NULL); $$->filho = criarNo("StrLit", $3); free($3);}
        | Assignment SEMI                                       {$$ = $1;}
        | MethodInvocation SEMI                                 {$$ = $1;}
        | ParseArgs SEMI                                        {$$ = $1;}
        | SEMI                                                  {$$ = NULL;}
        | RETURN SEMI                                           {$$ = criarNo("Return", NULL);}
        | RETURN Expr SEMI                                      {$$ = criarNo("Return", NULL); $$->filho = $2;}
        | error SEMI                                            {$$ = criarNo("Error", NULL); error = 1;}
        ;

/*deve repetir 0 ou + vezes { Statement }*/
Statement_2:Statement_2 Statement       {$$ = $1; $$ = criarIrmao($1, $2);}
        |                               {$$ = NULL;}
        ;



Assignment: ID ASSIGN Expr      {       $$ = criarNo("Assign", NULL); 
                                        $$->filho = criarIrmao(criarNo("Id", $1), $3); free($1);
                                }
        ;

MethodInvocation: ID OCURV CCURV                                {       $$ = criarNo("Call", NULL);
                                                                        $$->filho = criarNo("Id", $1); free($1);
                                                                }
        |ID OCURV Expr MethodInvocation_2 CCURV                 {       $$ = criarNo("Call", NULL);
                                                                        $$->filho = criarIrmao(criarIrmao(criarNo("Id", $1), $3), $4); 
                                                                        free($1);
                                                                }
        |ID OCURV error CCURV                                   {$$ = criarNo("Error", NULL); error = 1;}
        ;

/*deve repetir 0 ou + vezes { COMMA Expr }*/
MethodInvocation_2: MethodInvocation_2 COMMA Expr               {$$ = $1; $$ = criarIrmao($1, $3);}
        |                                                       {$$ = NULL;}
        ;

ParseArgs: PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV         {       $$ = criarNo("ParseArgs", NULL); 
                                                                        $$->filho = criarIrmao(criarNo("Id", $3), $5); free($3);}
        | PARSEINT OCURV error CCURV                            {$$ = criarNo("Error", NULL); error = 1;}
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
    | Expr2 PLUS Expr2                  {$$ = criarNo("Add", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 MINUS Expr2                 {$$ = criarNo("Sub", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 STAR Expr2                  {$$ = criarNo("Mul", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 DIV Expr2                   {$$ = criarNo("Div", NULL);  $$->filho = criarIrmao($1, $3);}
    | Expr2 MOD Expr2                   {$$ = criarNo("Mod", NULL);  $$->filho = criarIrmao($1, $3);}
    | NOT Expr2                         {$$ = criarNo("Not", NULL); $$->filho = $2;}   
    | PLUS Expr2      %prec NOT         {$$ = criarNo("Plus", NULL); $$->filho = $2;}              /*E'->NAND T E'1 {E'1.i = mknode("NAND", E'.i, Tn)}*/
    | MINUS Expr2     %prec NOT         {$$ = criarNo("Minus", NULL); $$->filho = $2;}                   /*O meu nó actual (Minus) vai ser irmão do novo nó (Expr), que no final estará no posso da pilha $$*/
    | ID                                {$$ = criarNo("Id", $1); free($1);}      /*T->ID  {T.n = mkleaf("Id", ID.lexval)}*/
    | ID DOTLENGTH                      {$$ = criarNo("Length", NULL); $$->filho = criarNo("Id", $1); free($1);} 
    | BOOLLIT                           {$$ = criarNo("BoolLit", $1); free($1);}
    | DECLIT                            {$$ = criarNo("DecLit", $1); free($1);}
    | REALLIT                           {$$ = criarNo("RealLit", $1); free($1);}
    | OCURV Expr CCURV                  {$$ = $2;}                      /*T->(E) {T.n = E.n}*/
    | OCURV error CCURV                 {$$ = criarNo("Error", NULL); error = 1;}
    ;

Expr:  Assignment       {$$ = $1;}              
    | Expr2             {$$ = $1;}
    ;
%%

void yyerror (const char *s) {      
        printf ("Line %d, col %d: %s: %s\n", lineNum, columnNum-(int)yyleng, s, yytext); 
}

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
%locations      /*variavel global do yacc que permite obter informações sobre a 
                a posição de cada um dos elementos*/

                /*tells yacc to enable  management of position information associ-
              ated  with each token, provided by the lexer in the global vari-
              able yylloc*/

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

Program: CLASS ID OBRACE Program_2 CBRACE   {   $$ = criarNo("Program", NULL, @1.last_line, @1.first_column);
                                                $$->filho = criarIrmao(criarNo("Id", $2, @1.last_line, @1.first_column),$4); free($2);
                                                raiz = $$; }
        ; 

/*deve repetir 0 ou + vezes  { FieldDecl | MethodDecl | SEMI } */
Program_2: Program_2 FieldDecl          {$$ = criarIrmao($1, $2);}   
        |Program_2 MethodDecl           {$$ = criarIrmao($1, $2);}   
        |Program_2 SEMI                 {$$ = $1;}
        |                               {$$ = NULL;}
        ;

FieldDecl: PUBLIC STATIC FieldDecl_2 SEMI               {$$ = $3;} 
        | error SEMI                                    {$$ = criarNo("Error", NULL, @1.last_line, @1.first_column); error = 1;}
        ;

/*deve repetir 0 ou + vezes { COMMA ID }*/
FieldDecl_2: FieldDecl_2 COMMA ID                       {       $$ = criarIrmao($1, copia=criarNo("FieldDecl", NULL, @1.last_line, @1.first_column));
                                                                copia->filho = criarIrmao(criarNo($$->filho->tipoVariavel, $$->filho->valor, @1.last_line, @1.first_column), criarNo("Id", $3, @1.last_line, @1.first_column));
                                                                free($3);
                                                        }
        | Type ID                                       {       $$ = criarNo("FieldDecl", NULL, @1.last_line, @1.first_column); 
                                                                $$->filho = criarIrmao($1, criarNo("Id", $2, @1.last_line, @1.first_column)); free($2);
                                                        }
        ;

MethodDecl: PUBLIC STATIC MethodHeader MethodBody       {$$ = criarNo("MethodDecl", NULL, @1.last_line, @1.first_column); $$->filho = criarIrmao($3, $4);}
        ;

MethodHeader: Type ID OCURV MethodHeader_2 CCURV        {       $$ = criarNo("MethodHeader", NULL, @1.last_line, @1.first_column); 
                                                                $$->filho = $1; 
                                                                $$->filho = criarIrmao($$->filho, criarNo("Id", $2, @1.last_line, @1.first_column)); free($2);
                                                                $$->filho = criarIrmao($$->filho, $4);
                                                        }
        |VOID ID OCURV MethodHeader_2 CCURV             {       $$ = criarNo("MethodHeader", NULL, @1.last_line, @1.first_column); 
                                                                $$->filho = criarIrmao(criarNo("Void", NULL, @1.last_line, @1.first_column), criarNo("Id", $2, @1.last_line, @1.first_column)); free($2);
                                                                $$->filho = criarIrmao($$->filho, $4);
                                                        }
        ;

/*deve ser opcional - sim ou não - [ FormalParams ]*/        
MethodHeader_2: FormalParams            {$$ = $1;}
        |                               {$$ = criarNo("MethodParams", NULL, -1, -1); $$->filho = NULL;}
        ;

MethodBody: OBRACE MethodBody_2 CBRACE          {$$ = criarNo("MethodBody", NULL, @1.last_line, @1.first_column); $$->filho = $2;}
        ;

/*deve repetir 0 ou + vezes { VarDecl | Statement }*/
MethodBody_2: MethodBody_2 VarDecl              {$$ = $1; $$ = criarIrmao($1, $2);}
        |MethodBody_2 Statement                 {       $$ = $1; 
                                                        if($2 != NULL){
                                                                if($2->irmao != NULL){
                                                                        $$ = criarIrmao($1, copia = criarNo("Block", NULL, @1.last_line, @1.first_column));
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

FormalParams: FormalParams_2                    {$$ = criarNo("MethodParams", NULL, @1.last_line, @1.first_column); $$->filho = $1;}
        | STRING OSQUARE CSQUARE ID             {       $$ = criarNo("MethodParams", NULL, @1.last_line, @1.first_column);
                                                        $$->filho = criarNo("ParamDecl", NULL, @1.last_line, @1.first_column);
                                                        $$->filho->filho = criarIrmao(criarNo("StringArray", NULL, @1.last_line, @1.first_column), criarNo("Id", $4, @1.last_line, @1.first_column));free($4);
                                                }
        ;
  
/*deve repetir 0 ou + vezes { COMMA Type ID }*/
FormalParams_2:FormalParams_2 COMMA Type ID     {       $$ = criarIrmao($1, copia=criarNo("ParamDecl", NULL, @1.last_line, @1.first_column));
                                                        copia->filho = criarIrmao($3, criarNo("Id", $4, @1.last_line, @1.first_column)); free($4);
                                                }
        | Type ID                               {       $$ = criarNo("ParamDecl", NULL, @1.last_line, @1.first_column);
                                                        $$->filho = criarIrmao($1, criarNo("Id", $2, @1.last_line, @1.first_column)); free($2);
                                                }
        ;

VarDecl: VarDecl_2 SEMI          {$$ = $1;}
        ;

/*deve repetir 0 ou + vezes { COMMA ID }*/
VarDecl_2: VarDecl_2 COMMA ID           {       $$ = criarIrmao($1, copia=criarNo("VarDecl", NULL, @1.last_line, @1.first_column));
                                                copia->filho = criarIrmao(criarNo($$->filho->tipoVariavel, $$->filho->valor, @1.last_line, @1.first_column), criarNo("Id", $3, @1.last_line, @1.first_column));
                                                free($3);
                                        }
        | Type ID                       {       $$ = criarNo("VarDecl", NULL, @1.last_line, @1.first_column); 
                                                $$->filho = criarIrmao($1, criarNo("Id", $2, @1.last_line, @1.first_column)); free($2);
                                        }
        ;

Type: BOOL              {$$ = criarNo("Bool", NULL, @1.last_line, @1.first_column);}      
    | INT               {$$ = criarNo("Int", NULL, @1.last_line, @1.first_column);}          /*porque são tipos, não tem "valor"*/
    | DOUBLE            {$$ = criarNo("Double", NULL, @1.last_line, @1.first_column);}
    ;

Statement: OBRACE Statement_2 CBRACE                            {       if($2 != NULL){
                                                                                if($2->irmao != NULL){
                                                                                        $$ = criarNo("Block", NULL, @1.last_line, @1.first_column);
                                                                                        $$->filho = $2;
                                                                                }else{
                                                                                        $$ = $2;
                                                                                }
                                                                        }else{
                                                                                $$ = $2;
                                                                        }
                                                                }
        | IF OCURV Expr CCURV Statement %prec IFX               {       $$ = criarNo("If", NULL, @1.last_line, @1.first_column); 
                                                                        if($5 != NULL){
                                                                                if($5->irmao != NULL){
                                                                                        $$->filho = criarIrmao($3, copia = criarNo("Block", NULL, @1.last_line, @1.first_column));
                                                                                        copia->filho = criarIrmao($5, criarNo("Block", NULL, @1.last_line, @1.first_column));
                                                                                }else{
                                                                                        $$->filho = criarIrmao(criarIrmao($3, $5), criarNo("Block", NULL, @1.last_line, @1.first_column));
                                                                                }
                                                                        }else{
                                                                                $$->filho = criarIrmao($3, criarIrmao(criarNo("Block", NULL, @1.last_line, @1.first_column), criarNo("Block", NULL, @1.last_line, @1.first_column)));
                                                                        }
                                                                        
                                                                }
        | IF OCURV Expr CCURV Statement ELSE Statement         {        $$ = criarNo("If", NULL, @1.last_line, @1.first_column); 
                                                                        if($5 != NULL){
                                                                                if($5->irmao != NULL){
                                                                                        $$->filho = criarIrmao($3, copia = criarNo("Block", NULL, @1.last_line, @1.first_column));
                                                                                        copia->filho = criarIrmao($5, criarNo("Block", NULL, @1.last_line, @1.first_column));
                                                                                }else{
                                                                                        $$->filho = criarIrmao($3, $5);
                                                                                }
                                                                        }else{
                                                                                $$->filho = criarIrmao($3,  criarNo("Block", NULL, @1.last_line, @1.first_column));
                                                                        }
                                                                        
                                                                        if($7 != NULL){
                                                                                if($7->irmao != NULL){
                                                                                        $$->filho = criarIrmao($$->filho, copia = criarNo("Block", NULL, @1.last_line, @1.first_column));
                                                                                        copia->filho = $7;
                                                                                }else{
                                                                                        $$->filho = criarIrmao($$->filho, $7);
                                                                                }
                                                                        }else{
                                                                               $$->filho = criarIrmao($$->filho, criarNo("Block", NULL, @1.last_line, @1.first_column));
                                                                        }
                                                                        
                                                                }
        | WHILE OCURV Expr CCURV Statement                      {       $$ = criarNo("While", NULL, @1.last_line, @1.first_column); 
                                                                        if($5 != NULL){
                                                                                if($5->irmao != NULL){
                                                                                        $$->filho = criarIrmao($3, copia = criarNo("Block", NULL, @1.last_line, @1.first_column));
                                                                                        copia->filho = $5;
                                                                                }else{
                                                                                        $$->filho = criarIrmao($3, $5);
                                                                                }
                                                                        }else{                                                                                                                          
                                                                                $$->filho = criarIrmao($3, criarNo("Block", NULL, @1.last_line, @1.first_column));
                                                                        }
                                                                }
        | DO Statement WHILE OCURV Expr CCURV SEMI              {       $$ = criarNo("DoWhile", NULL, @1.last_line, @1.first_column);
                                                                        if($2 != NULL){
                                                                                if($2->irmao != NULL){
                                                                                        $$->filho = criarIrmao(copia = criarNo("Block", NULL, @1.last_line, @1.first_column), $5);
                                                                                        copia->filho = $2;
                                                                                }else{
                                                                                        $$->filho = criarIrmao($2, $5);
                                                                                }
                                                                        }else{
                                                                             $$->filho = criarIrmao(criarNo("Block", NULL, @1.last_line, @1.first_column), $5);
                                                                        }
                                                                        
                                                                }
        | PRINT OCURV Expr CCURV SEMI                           {       $$ = criarNo("Print", NULL, @1.last_line, @1.first_column); 
                                                                        $$->filho = $3;
                                                                }
        | PRINT OCURV STRLIT CCURV SEMI                         {$$ = criarNo("Print", NULL, @1.last_line, @1.first_column); $$->filho = criarNo("StrLit", $3, @1.last_line, @1.first_column); free($3);}
        | Assignment SEMI                                       {$$ = $1;}
        | MethodInvocation SEMI                                 {$$ = $1;}
        | ParseArgs SEMI                                        {$$ = $1;}
        | SEMI                                                  {$$ = NULL;}
        | RETURN SEMI                                           {$$ = criarNo("Return", NULL, @1.last_line, @1.first_column);}
        | RETURN Expr SEMI                                      {$$ = criarNo("Return", NULL, @1.last_line, @1.first_column); $$->filho = $2;}
        | error SEMI                                            {$$ = criarNo("Error", NULL, @1.last_line, @1.first_column); error = 1;}
        ;

/*deve repetir 0 ou + vezes { Statement }*/
Statement_2:Statement_2 Statement       {$$ = $1; $$ = criarIrmao($1, $2);}
        |                               {$$ = NULL;}
        ;



Assignment: ID ASSIGN Expr      {       $$ = criarNo("Assign", NULL, @1.last_line, @1.first_column); 
                                        $$->filho = criarIrmao(criarNo("Id", $1, @1.last_line, @1.first_column), $3); free($1);
                                }
        ;

MethodInvocation: ID OCURV CCURV                                {       $$ = criarNo("Call", NULL, @1.last_line, @1.first_column);
                                                                        $$->filho = criarNo("Id", $1, @1.last_line, @1.first_column); free($1);
                                                                }
        |ID OCURV Expr MethodInvocation_2 CCURV                 {       $$ = criarNo("Call", NULL, @1.last_line, @1.first_column);
                                                                        $$->filho = criarIrmao(criarIrmao(criarNo("Id", $1, @1.last_line, @1.first_column), $3), $4); 
                                                                        free($1);
                                                                }
        |ID OCURV error CCURV                                   {$$ = criarNo("Error", NULL, @1.last_line, @1.first_column); error = 1;}
        ;

/*deve repetir 0 ou + vezes { COMMA Expr }*/
MethodInvocation_2: MethodInvocation_2 COMMA Expr               {$$ = $1; $$ = criarIrmao($1, $3);}
        |                                                       {$$ = NULL;}
        ;

ParseArgs: PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV         {       $$ = criarNo("ParseArgs", NULL, @1.last_line, @1.first_column); 
                                                                        $$->filho = criarIrmao(criarNo("Id", $3, @1.last_line, @1.first_column), $5); free($3);}
        | PARSEINT OCURV error CCURV                            {$$ = criarNo("Error", NULL, @1.last_line, @1.first_column); error = 1;}
        ;

Expr2:MethodInvocation                  {$$ = $1;}              /*E' -> € {E'.n = E'.i}*/             
    | ParseArgs                         {$$ = $1;}
    | Expr2 AND Expr2                   {$$ = criarNo("And", NULL, @1.last_line, @1.first_column); $$->filho = criarIrmao($1, $3);} /*AND vai para o topo da pilha, está no topo e a este vamos acrescentar um filho Expr e a este um irmão Expr*/
    | Expr2 OR Expr2                    {$$ = criarNo("Or", NULL, @1.last_line, @1.first_column);  $$->filho = criarIrmao($1, $3);}
    | Expr2 EQ Expr2                    {$$ = criarNo("Eq", NULL, @1.last_line, @1.first_column);  $$->filho = criarIrmao($1, $3);}
    | Expr2 GEQ Expr2                   {$$ = criarNo("Geq", NULL, @1.last_line, @1.first_column);  $$->filho = criarIrmao($1, $3);}
    | Expr2 GT Expr2                    {$$ = criarNo("Gt", NULL, @1.last_line, @1.first_column);  $$->filho = criarIrmao($1, $3);}
    | Expr2 LEQ Expr2                   {$$ = criarNo("Leq", NULL, @1.last_line, @1.first_column);  $$->filho = criarIrmao($1, $3);}
    | Expr2 LT Expr2                    {$$ = criarNo("Lt", NULL, @1.last_line, @1.first_column);  $$->filho = criarIrmao($1, $3);}
    | Expr2 NEQ Expr2                   {$$ = criarNo("Neq", NULL, @1.last_line, @1.first_column);  $$->filho = criarIrmao($1, $3);}
    | Expr2 PLUS Expr2                  {$$ = criarNo("Add", NULL, @1.last_line, @1.first_column);  $$->filho = criarIrmao($1, $3);}
    | Expr2 MINUS Expr2                 {$$ = criarNo("Sub", NULL, @1.last_line, @1.first_column);  $$->filho = criarIrmao($1, $3);}
    | Expr2 STAR Expr2                  {$$ = criarNo("Mul", NULL, @1.last_line, @1.first_column);  $$->filho = criarIrmao($1, $3);}
    | Expr2 DIV Expr2                   {$$ = criarNo("Div", NULL, @1.last_line, @1.first_column);  $$->filho = criarIrmao($1, $3);}
    | Expr2 MOD Expr2                   {$$ = criarNo("Mod", NULL, @1.last_line, @1.first_column);  $$->filho = criarIrmao($1, $3);}
    | NOT Expr2                         {$$ = criarNo("Not", NULL, @1.last_line, @1.first_column); $$->filho = $2;}   
    | PLUS Expr2      %prec NOT         {$$ = criarNo("Plus", NULL, @1.last_line, @1.first_column); $$->filho = $2;}              /*E'->NAND T E'1 {E'1.i = mknode("NAND", E'.i, Tn)}*/
    | MINUS Expr2     %prec NOT         {$$ = criarNo("Minus", NULL, @1.last_line, @1.first_column); $$->filho = $2;}                   /*O meu nó actual (Minus) vai ser irmão do novo nó (Expr), que no final estará no posso da pilha $$*/
    | ID                                {$$ = criarNo("Id", $1, @1.last_line, @1.first_column); free($1);}      /*T->ID  {T.n = mkleaf("Id", ID.lexval)}*/
    | ID DOTLENGTH                      {$$ = criarNo("Length", NULL, @1.last_line, @1.first_column); $$->filho = criarNo("Id", $1, @1.last_line, @1.first_column); free($1);} 
    | BOOLLIT                           {$$ = criarNo("BoolLit", $1, @1.last_line, @1.first_column); free($1);}
    | DECLIT                            {$$ = criarNo("DecLit", $1, @1.last_line, @1.first_column); free($1);}
    | REALLIT                           {$$ = criarNo("RealLit", $1, @1.last_line, @1.first_column); free($1);}
    | OCURV Expr CCURV                  {$$ = $2;}                      /*T->(E) {T.n = E.n}*/
    | OCURV error CCURV                 {$$ = criarNo("Error", NULL, @1.last_line, @1.first_column); error = 1;}
    ;

Expr:  Assignment       {$$ = $1;}              
    | Expr2             {$$ = $1;}
    ;
%%

void yyerror (const char *s) {      
        printf ("Line %d, col %d: %s: %s\n", lineNum, columnNum-(int)yyleng, s, yytext); 
}
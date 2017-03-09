%{
    #include <stdio.h>
    int yylex(void);
    void yyerror (const char *s);
%}

%token OCURV CCURV OBRACE CBRACE OSQUARE CSQUARE 
%token AND OR LT GT EQ NEQ LEQ GEQ PLUS MINUS STAR DIV MOD NOT ASSIGN SEMI COMMA
%token BOOL CLASS DO DOTLENGTH DOUBLE ELSE IF INT PARSEINT PRINT PUBLIC RETURN STATIC STRING VOID WHILE

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

%%

Program: CLASS ID OBRACE Program_2 CBRACE   
        ;

/*deve repetir 0 ou + vezes  { FieldDecl | MethodDecl | SEMI } */
Program_2: Program_2 FieldDecl
        |Program_2 MethodDecl
        |Program_2 SEMI
        |
        ;

FieldDecl: PUBLIC STATIC  Type ID comma_id SEMI 
        ;

/*deve repetir 0 ou + vezes { COMMA ID }*/
comma_id: comma_id COMMA ID
        |
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

Type: BOOL 
    | INT 
    | DOUBLE 
    ;

Statement: OBRACE Statement_2 CBRACE
        | IF OCURV Expr CCURV Statement
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
        ;

Expr: Assignment 
    | MethodInvocation 
    | ParseArgs 
    | Expr AND Expr 
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
    | PLUS Expr
    | MINUS Expr
    | NOT Expr 
    | ID
    | ID DOTLENGTH
    | OCURV Expr CCURV 
    | BOOLLIT 
    | DECLIT 
    | REALLIT
    ;

%%
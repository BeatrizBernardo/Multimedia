%{
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include "y.tab.h"

    void yyerror (const char *s);
    int yylex(void);

    /*importa as variaveis do lex*/
    extern int lineNum;
    extern int columnNum;
    extern char *yytext; 
    extern int yyleng;
    
%}

%union{
        char* string;   
}

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

Program: CLASS ID OBRACE Program_2 CBRACE	{}   
        ;

/*deve repetir 0 ou + vezes  { FieldDecl | MethodDecl | SEMI } */
Program_2: Program_2 FieldDecl   {}       
        |Program_2 MethodDecl    {}       
        |Program_2 SEMI          {}       
        |                               
        ;

FieldDecl: PUBLIC STATIC FieldDecl_2 SEMI    {}      
        | error SEMI   {}                                 
        ;

/*deve repetir 0 ou + vezes { COMMA ID }*/
FieldDecl_2: FieldDecl_2 COMMA ID     {}                                            
        | Type ID {}
        ;

MethodDecl: PUBLIC STATIC MethodHeader MethodBody   {}    
        ;

MethodHeader: Type ID OCURV MethodHeader_2 CCURV    {}    
        |VOID ID OCURV MethodHeader_2 CCURV         {}    
        ;

/*deve ser opcional - sim ou não - [ FormalParams ]*/        
MethodHeader_2: FormalParams            {}
        |                               
        ;

MethodBody: OBRACE MethodBody_2 CBRACE          {}
        ;

/*deve repetir 0 ou + vezes { VarDecl | Statement }*/
MethodBody_2: MethodBody_2 VarDecl              {}
        |MethodBody_2 Statement                 {}
        |                                       
        ;

FormalParams: FormalParams_2            {}
        | STRING OSQUARE CSQUARE ID         {}
        ;

/*deve repetir 0 ou + vezes { COMMA Type ID }*/
FormalParams_2:FormalParams_2 COMMA Type ID     {} 
        |   Type ID                                            
        ;


VarDecl: VarDecl_2 SEMI          {}
        ;

/*deve repetir 0 ou + vezes { COMMA ID }*/
VarDecl_2: VarDecl_2 COMMA ID
        | Type ID 
        ;

Type: BOOL              {}
    | INT               {}
    | DOUBLE            {}
    ;
    


Statement: OBRACE Statement_2 CBRACE            			{}                
        | IF OCURV Expr CCURV Statement %prec IFX           {}    
        | IF OCURV Expr CCURV Statement ELSE Statement      {}    
        | WHILE OCURV Expr CCURV Statement                  {}    
        | DO Statement WHILE OCURV Expr CCURV SEMI          {}    
        | PRINT OCURV Expr CCURV SEMI                       {}    
        | PRINT OCURV STRLIT CCURV SEMI                     {}    
        | Assignment SEMI                                   {}    
        | MethodInvocation SEMI                             {}    
        | ParseArgs SEMI                                    {}  
        | SEMI												{} 
        | RETURN SEMI                                       {}    
        | RETURN Expr SEMI                                  {}    
        | error SEMI                                        {}    
        ;

/*deve repetir 0 ou + vezes { Statement }*/
Statement_2:Statement_2 Statement       {}
        |                               
        ;

Assignment: ID ASSIGN Expr      {}
        ;

MethodInvocation: ID OCURV CCURV          {}                      
        |ID OCURV Expr MethodInvocation_2 CCURV           {}      
        |ID OCURV error CCURV                 {}                  
        ;

/*deve repetir 0 ou + vezes { COMMA Expr }*/
MethodInvocation_2: MethodInvocation_2 COMMA Expr         {}      
        |                                                       
        ;

ParseArgs: PARSEINT OCURV ID OSQUARE Expr CSQUARE CCURV        {} 
        | PARSEINT OCURV error CCURV                    {}        
        ;

Expr2: MethodInvocation          {}
    | ParseArgs                 {}
    | Expr2 AND Expr2             {}
    | Expr2 OR Expr2              {}
    | Expr2 EQ Expr2              {}
    | Expr2 GEQ Expr2             {}
    | Expr2 GT Expr2              {}
    | Expr2 LEQ Expr2             {}
    | Expr2 LT Expr2              {}
    | Expr2 NEQ Expr2             {}
    | Expr2 PLUS Expr2            {}
    | Expr2 MINUS Expr2           {}
    | Expr2 STAR Expr2            {}
    | Expr2 DIV Expr2             {}
    | Expr2 MOD Expr2             {}
    | NOT Expr2    		    	{}
    | PLUS Expr2	%prec NOT            	{}     
    | MINUS Expr2	%prec NOT          		{}                   
    | ID                   		{}     
    | ID DOTLENGTH         		{}       
    | BOOLLIT              		{}    
    | DECLIT               		{}     
    | REALLIT              		{} 
    | OCURV Expr CCURV     		{}    
    | OCURV error CCURV    		{}       
	;

Expr: Assignment                {}
   	| Expr2 {}
    ;

%%

void yyerror (const char *s) {      
        printf ("Line %d, col %d: %s: %s\n", lineNum, columnNum-(int)yyleng, s, yytext); 
}

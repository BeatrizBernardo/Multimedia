%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"

	int aux = 0;
    int aux_2 = 0;
    /*as colunas e as linhas começam em 1*/
    int lineNum = 1;
    int columnNum = 1;

    /*contador para as linhas dos comentários*/
    int commentLineNum = 1;
    int commentColumnNum = 1;
    
    int invColumnNum = 1;
%}

%X COMMENTS
%X COMMENT
%X INVSTR

BOOL    "boolean"
BOOLLIT "true"|"false"
CLASS   "class" 
DO  "do" 
DOTLENGTH   ".length"
DOUBLE  "double"
ELSE    "else"
IF  "if" 
INT "int" 
PARSEINT    "Integer.parseInt"
PRINT   "System.out.println"
PUBLIC  "public"
RETURN  "return"
STATIC  "static"
STRING  "String"
VOID    "void"
WHILE   "while" 
OCURV   "(" 
CCURV   ")" 
OBRACE  "{" 
CBRACE  "}"
OSQUARE "[" 
CSQUARE "]" 
AND     "&&" 
OR      "||" 
LT  "<" 
GT  ">" 
EQ  "==" 
NEQ "!=" 
LEQ "<=" 
GEQ ">=" 
PLUS    "+" 
MINUS   "-"
STAR    "*" 
DIV "/" 
MOD "%" 
NOT "!" 
ASSIGN  "=" 
SEMI    ";" 
COMMA   ","

RESERVED    "++"|"--"|null|abstract|continue|for|new|switch|assert|default|package|synchronized|goto|private|this|break|implements|protected|throw|byte|import|throws|case|enum|instanceof|return|transient|catch|extends|short|try|final|interface|finally|long|strictfp|volatile|const|native|super|char|float|System|Integer    

ID  [a-zA-Z_$]([a-zA-Z_$0-9])* 

ESC	\\[fnrt\"\\]
NOTESC	[^\n\r\"\\]

NOTESC2 \\[^\n\r]?

STRLIT \"({ESC}|{NOTESC})*\"

NUMEROS	[1-9]([0-9_]*[0-9])?
DECLIT  0|{NUMEROS}

NUMERO	[0-9]([0-9_]*[0-9])*
EXP	[Ee][+-]?{NUMERO}
REALLIT (({NUMERO}{EXP})|(\.{NUMERO})|({NUMERO}\.)|(\.{NUMERO}{EXP}?)|({NUMERO}\.{NUMERO})|({NUMERO}\.{NUMERO}?{EXP}?))

%%

\"				{BEGIN INVSTR; columnNum += yyleng; invColumnNum = columnNum-1;}
<INVSTR>\"		{BEGIN 0; columnNum += yyleng;}
			
<INVSTR>({ESC}|{NOTESC})		        {columnNum+=yyleng;}
<INVSTR>{NOTESC2}                 {printf("Line %d, col %d: invalid escape sequence (%s)\n", lineNum, columnNum, yytext); columnNum+=yyleng;}
<INVSTR>("\n"|"\r"|"\r\n")            {printf("Line %d, col %d: unterminated string literal\n", lineNum, invColumnNum); lineNum++; columnNum = 1; BEGIN 0;}

"/*"                                {BEGIN COMMENTS; commentLineNum = lineNum; commentColumnNum = columnNum; columnNum += yyleng;}
<COMMENTS><<EOF>>                   {printf("Line %d, col %d: unterminated comment\n", commentLineNum, commentColumnNum); BEGIN 0;}
<COMMENTS>"\n"|"\r"|"\r\n"          {lineNum++; columnNum = 1;} 
<COMMENTS>.                        	 {columnNum += yyleng;}
<COMMENTS>"*/"                      {columnNum += yyleng; BEGIN 0;}

"//"				    {BEGIN COMMENT; commentLineNum = lineNum; commentColumnNum = columnNum; columnNum += yyleng;}
<COMMENT>"\n"|"\r"|"\r\n"           {lineNum++; columnNum = 1; BEGIN 0;} 
<COMMENT>.          	            {columnNum += yyleng;}

{OCURV}     {   columnNum += yyleng; 
                if(aux==1){
                    printf("OCURV\n");
                }
                if(aux_2 == 1){
	                return OCURV;	
                }
            }

{CCURV}     {   columnNum += yyleng; 
                if(aux==1){
                    printf("CCURV\n");
                } 
                if(aux_2 == 1){
                    return CCURV;	
                }
            }

{OBRACE}    {   columnNum += yyleng; 
                if(aux==1){
                    printf("OBRACE\n");
                }
                if(aux_2 == 1){
                	return OBRACE;
                }
            }

{CBRACE}    {   columnNum += yyleng; 
                if(aux==1){
                    printf("CBRACE\n");
                }
                if(aux_2 == 1){ 
                	return CBRACE;
                }
            }

{OSQUARE}   {   columnNum += yyleng; 
                if(aux==1){
                    printf("OSQUARE\n");
                }
                if(aux_2 == 1){ 
            		return OSQUARE;
                }
            }

{CSQUARE}   {   columnNum += yyleng; 
                if(aux==1){
                    printf("CSQUARE\n");
                }
                if(aux_2 == 1){ 
                	return CSQUARE;
                	
                }
            }

{AND}       {   columnNum += yyleng; 
                if(aux==1){
                    printf("AND\n");
                }
                if(aux_2 == 1){ 
            		return AND;
                }
            }

{OR}        {   columnNum += yyleng; 
                if(aux==1){
                    printf("OR\n");
                }
                if(aux_2 == 1){ 
                	return OR;
                }
            }

{LT}        {   columnNum += yyleng; 
                if(aux==1){
                    printf("LT\n");
                }
                if(aux_2 == 1){ 
            		return LT;
                }
            }

{GT}        {   columnNum += yyleng; 
                if(aux==1){
                    printf("GT\n");
                }
                if(aux_2 == 1){ 
        			return GT;
                }
            }

{EQ}        {   columnNum += yyleng; 
                if(aux==1){
                    printf("EQ\n");
                }
                if(aux_2 == 1){ 
                	return EQ;
                }
            }

{NEQ}       {   columnNum += yyleng; 
                if(aux==1){
                    printf("NEQ\n");
                }
                if(aux_2 == 1){ 
                	return NEQ;
                }
            }

{LEQ}       {   columnNum += yyleng; 
                if(aux==1){
                    printf("LEQ\n");
                }
                if(aux_2 == 1){ 
                	return LEQ;
                }
            }

{GEQ}       {   columnNum += yyleng; 
                if(aux==1){
                    printf("GEQ\n");
                }
                if(aux_2 == 1){ 
                	return GEQ;
                }
            }

{PLUS}      {   columnNum += yyleng; 
                if(aux==1){
                    printf("PLUS\n");
                }
                if(aux_2 == 1){ 
                	return PLUS;
                }
            }

{MINUS}     {   columnNum += yyleng; 
                if(aux==1){
                    printf("MINUS\n");
                }
                if(aux_2 == 1){ 
                	return MINUS;
                }
            }

{STAR}      {   columnNum += yyleng; 
                if(aux==1){
                    printf("STAR\n");
                }
                if(aux_2 == 1){ 
                	return STAR;
                }
            }

{DIV}       {   columnNum += yyleng; 
                if(aux==1){
                    printf("DIV\n");
                }
                if(aux_2 == 1){ 
                	return DIV;
                }
            }

{MOD}       {   columnNum += yyleng; 
                if(aux==1){
                    printf("MOD\n");
                }
                if(aux_2 == 1){ 
                	return MOD;
                }
            }

{NOT}       {   columnNum += yyleng; 
                if(aux==1){
                    printf("NOT\n");
                }
                if(aux_2 == 1){ 
                	return NOT;
                }
            }

{ASSIGN}    {   columnNum += yyleng; 
                if(aux==1){
                    printf("ASSIGN\n");
                }
                if(aux_2 == 1){ 
                	return ASSIGN;
                }
            }

{SEMI}      {   columnNum += yyleng; 
                if(aux==1){
                    printf("SEMI\n");
                }
                if(aux_2 == 1){ 
                	return SEMI;
                }
            }

{COMMA}     {columnNum += yyleng; 
                if(aux==1){
                    printf("COMMA\n");
                }
                if(aux_2 == 1){ 
                	return COMMA;
                }
            }

{BOOL}          {   columnNum += yyleng; 
                    if(aux==1){
                        printf("BOOL\n");
                    }
                    if(aux_2 == 1){ 
                    	return BOOL;
                    }
                }

{BOOLLIT}       {   columnNum += yyleng; 
                    if(aux==1){
                        printf("BOOLLIT(%s)\n", yytext);
                    }
                    if(aux_2 == 1){ 
	                    yylval.string=(char*)strdup(yytext);
	                    return BOOLLIT;
                    }
                }

{CLASS}         {   columnNum += yyleng; 
                    if(aux==1){
                        printf("CLASS\n");
                    }
                    if(aux_2 == 1){ 
                    	return CLASS;
                    }
                }

{DO}            {   columnNum += yyleng; 
                    if(aux==1){
                        printf("DO\n");
                    }
                    if(aux_2 == 1){ 
                    	return DO;
                    }
                }

{DOTLENGTH}     {   columnNum += yyleng; 
                    if(aux==1){
                        printf("DOTLENGTH\n");
                    }
                    if(aux_2 == 1){ 
                    	return DOTLENGTH;
                    }
                }

{DOUBLE}        {   columnNum += yyleng; 
                    if(aux==1){
                        printf("DOUBLE\n");
                    }
                    if(aux_2 == 1){ 
                    	return DOUBLE;
                    }
                }

{ELSE}          {   columnNum += yyleng; 
                    if(aux==1){
                        printf("ELSE\n");
                    }
                    if(aux_2 == 1){ 
                    	return ELSE;
                    }
                }

{IF}            {   columnNum += yyleng; 
                    if(aux==1){
                        printf("IF\n");
                    }
                    if(aux_2 == 1){ 
                    	return IF;
                    }
                }

{INT}           {   columnNum += yyleng; 
                    if(aux==1){
                        printf("INT\n");
                    }
                    if(aux_2 == 1){ 
                    	return INT;
                    }
                }

{PARSEINT}      {   columnNum += yyleng; 
                    if(aux==1){
                        printf("PARSEINT\n");
                    }
                    if(aux_2 == 1){ 
                    	return PARSEINT;
                    }
                }

{PRINT}         {   columnNum += yyleng; 
                    if(aux==1){
                        printf("PRINT\n");
                    }
                    if(aux_2 == 1){ 
                    	return PRINT;
                    }
                }

{PUBLIC}        {   columnNum += yyleng; 
                    if(aux==1){
                        printf("PUBLIC\n");
                    }
                    if(aux_2 == 1){ 
                    	return PUBLIC;
                    }
                }

{RETURN}        {   columnNum += yyleng; 
                    if(aux==1){
                        printf("RETURN\n");
                    }
                    if(aux_2 == 1){ 
                    	return RETURN;
                    }
                }

{STATIC}        {   columnNum += yyleng; 
                    if(aux==1){
                        printf("STATIC\n");
                    }
                    if(aux_2 == 1){ 
                    	return STATIC;
                    }
                }

{STRING}        {   columnNum += yyleng; 
                    if(aux==1){
                        printf("STRING\n");
                    }
                    if(aux_2 == 1){ 
                    	return STRING;
                    }
                }

{VOID}          {   columnNum += yyleng; 
                    if(aux==1){
                        printf("VOID\n");
                    }
                    if(aux_2 == 1){ 
                    	return VOID;
                    }
                }

{WHILE}         {   columnNum += yyleng; 
                    if(aux==1){
                        printf("WHILE\n");
                    }
                    if(aux_2 == 1){ 
                    	return WHILE;
                    }
                }

{RESERVED}  {   columnNum += yyleng; 
                if(aux==1){
                    printf("RESERVED(%s)\n", yytext);
                }
                if(aux_2 == 1){ 
			        yylval.string=(char*)strdup(yytext);
			        return RESERVED;
                }
            }


{ID}        {   columnNum += yyleng; 
                if(aux==1){
                    printf("ID(%s)\n", yytext);
                }
                if(aux_2 == 1){ 
	                yylval.string=(char*)strdup(yytext);
	                return ID;
                }
            }

{DECLIT}    {   columnNum += yyleng; 
                if(aux==1){
                    printf("DECLIT(%s)\n", yytext);
                }
                if(aux_2 == 1){ 
		            yylval.string=(char*)strdup(yytext);
		            return DECLIT;
                }
            }

{REALLIT}   {   columnNum += yyleng; 
                if(aux==1){
                    printf("REALLIT(%s)\n", yytext);
                }
                if(aux_2 == 1){ 
	                yylval.string=(char*)strdup(yytext);
	                return REALLIT;
                }
            }

{STRLIT}    {   columnNum += yyleng; 
                if(aux==1){
                    printf("STRLIT(%s)\n", yytext);
                }
                if(aux_2 == 1){ 
	                yylval.string=(char*)strdup(yytext);
	                return STRLIT;
                }
            }

"\t"|"\f"|" " 	        {columnNum += yyleng;}
"\n"|"\r"|"\r\n"        {lineNum++; columnNum = 1;}

.		{printf("Line %d, col %d: illegal character (%c)\n", lineNum, columnNum, yytext[0]); columnNum+=yyleng;} 

%%
int main(int argc, char *argv[]){
    if(argc == 2){
        if(strcmp(argv[1], "-l") == 0){
            /*deve mostrar o resultado*/
            aux = 1;
            yylex();
        } else if(strcmp(argv[1], "-1") == 0){
            yylex();
        }
    }else{
        /*sem nenhuma opção deve detetar erros lexicais ou de sintaxe e emitir mensagens de erro*/
        aux_2 = 1;
        yyparse();
    }
    return 0;
}

int yywrap(){
    return 1;
}
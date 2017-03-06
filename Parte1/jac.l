%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
	int aux=0;
    /*as colunas e as linhas começam em 1*/
    int lineNum = 1;
    int columnNum = 1;

    /*contador para as linhas dos comentários*/
    int commentLineNum = 1;
    int commentColumnNum = 1;
    
    int invLineNum = 1;
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

NOTESC2 \\[^\"\nfnrt\\]?

STRLIT \"({ESC}|{NOTESC})*\"

NUMEROS	[1-9]([0-9_]*[0-9])?
DECLIT  0|{NUMEROS}

NUMERO	[0-9]([0-9_]*[0-9])*
EXP	[Ee][+-]?{NUMERO}
REALLIT (({NUMERO}{EXP})|(\.{NUMERO})|({NUMERO}\.)|(\.{NUMERO}{EXP}?)|({NUMERO}\.{NUMERO})|({NUMERO}\.{NUMERO}?{EXP}?))

%%


"/*"                                {BEGIN COMMENTS; commentLineNum = lineNum; commentColumnNum = columnNum; columnNum += yyleng;}
<COMMENTS><<EOF>>                   {printf("Line %d, col %d: unterminated comment\n", commentLineNum, commentColumnNum); BEGIN 0;}
<COMMENTS>"\n"|"\r"|"\r\n"          {lineNum++; columnNum = 1;} 
<COMMENTS>.                        	 {columnNum += yyleng;}
<COMMENTS>"*/"                      {columnNum += yyleng; BEGIN 0;}

"//"				    {BEGIN COMMENT; commentLineNum = lineNum; commentColumnNum = columnNum; columnNum += yyleng;}
<COMMENT>"\n"|"\r"|"\r\n"           {lineNum++; columnNum = 1; BEGIN 0;} 
<COMMENT>.          	            {columnNum += yyleng;}

{OCURV}     {columnNum += yyleng; if(aux==1){printf("OCURV\n");}}
{CCURV}     {columnNum += yyleng; if(aux==1){printf("CCURV\n");}}
{OBRACE}    {columnNum += yyleng; if(aux==1){printf("OBRACE\n");}}
{CBRACE}    {columnNum += yyleng; if(aux==1){printf("CBRACE\n");}}
{OSQUARE}   {columnNum += yyleng; if(aux==1){printf("OSQUARE\n");}}
{CSQUARE}   {columnNum += yyleng; if(aux==1){printf("CSQUARE\n");}}
{AND}       {columnNum += yyleng; if(aux==1){printf("AND\n");}}
{OR}        {columnNum += yyleng; if(aux==1){printf("OR\n");}}
{LT}        {columnNum += yyleng; if(aux==1){printf("LT\n");}}
{GT}        {columnNum += yyleng; if(aux==1){printf("GT\n");}}
{EQ}        {columnNum += yyleng; if(aux==1){printf("EQ\n");}}
{NEQ}       {columnNum += yyleng; if(aux==1){printf("NEQ\n");}}
{LEQ}       {columnNum += yyleng; if(aux==1){printf("LEQ\n");}}
{GEQ}       {columnNum += yyleng; if(aux==1){printf("GEQ\n");}}
{PLUS}      {columnNum += yyleng; if(aux==1){printf("PLUS\n");}}
{MINUS}     {columnNum += yyleng; if(aux==1){printf("MINUS\n");}}
{STAR}      {columnNum += yyleng; if(aux==1){printf("STAR\n");}}
{DIV}       {columnNum += yyleng; if(aux==1){printf("DIV\n");}}
{MOD}       {columnNum += yyleng; if(aux==1){printf("MOD\n");}}
{NOT}       {columnNum += yyleng; if(aux==1){printf("NOT\n");}}
{ASSIGN}    {columnNum += yyleng; if(aux==1){printf("ASSIGN\n");}}
{SEMI}      {columnNum += yyleng; if(aux==1){printf("SEMI\n");}}
{COMMA}     {columnNum += yyleng; if(aux==1){printf("COMMA\n");}}

{BOOL}          {columnNum += yyleng; if(aux==1){printf("BOOL\n");}}
{BOOLLIT}       {columnNum += yyleng; if(aux==1){printf("BOOLLIT(%s)\n", yytext);}}
{CLASS}         {columnNum += yyleng; if(aux==1){printf("CLASS\n");}}
{DO}            {columnNum += yyleng; if(aux==1){printf("DO\n");}}
{DOTLENGTH}     {columnNum += yyleng; if(aux==1){printf("DOTLENGTH\n");}}
{DOUBLE}        {columnNum += yyleng; if(aux==1){printf("DOUBLE\n");}}
{ELSE}          {columnNum += yyleng; if(aux==1){printf("ELSE\n");}}
{IF}            {columnNum += yyleng; if(aux==1){printf("IF\n");}}
{INT}           {columnNum += yyleng; if(aux==1){printf("INT\n");}}
{PARSEINT}      {columnNum += yyleng; if(aux==1){printf("PARSEINT\n");}}
{PRINT}         {columnNum += yyleng; if(aux==1){printf("PRINT\n");}}
{PUBLIC}        {columnNum += yyleng; if(aux==1){printf("PUBLIC\n");}}
{RETURN}        {columnNum += yyleng; if(aux==1){printf("RETURN\n");}}
{STATIC}        {columnNum += yyleng; if(aux==1){printf("STATIC\n");}}
{STRING}        {columnNum += yyleng; if(aux==1){printf("STRING\n");}}
{VOID}          {columnNum += yyleng; if(aux==1){printf("VOID\n");}}
{WHILE}         {columnNum += yyleng; if(aux==1){printf("WHILE\n");}}

{RESERVED}  {columnNum += yyleng; if(aux==1){printf("RESERVED(%s)\n", yytext);}}


{ID}        {columnNum += yyleng; if(aux==1){printf("ID(%s)\n", yytext);}}
{DECLIT}    {columnNum += yyleng; if(aux==1){printf("DECLIT(%s)\n", yytext);}}
{REALLIT}   {columnNum += yyleng; if(aux==1){printf("REALLIT(%s)\n", yytext);}}

{STRLIT}    {columnNum += yyleng; if(aux==1){printf("STRLIT(%s)\n", yytext);}}
\"								{BEGIN INVSTR; invLineNum = lineNum; invColumnNum = columnNum; columnNum += yyleng;}
<INVSTR>{STRLIT}\"				{BEGIN 0; columnNum += yyleng; if(aux==1){printf("STRLIT(\"%s)\n",yytext);}}
<INVSTR>({ESC}+|{NOTESC}+)		{columnNum+=yyleng;}
<INVSTR>{NOTESC2}               {printf("Line %d, col %d: invalid escape sequence (%s)\n", lineNum, columnNum, yytext); columnNum+=yyleng;}
<INVSTR>{NOTESC2}|("\n"|"\r"|"\r\n")   	{printf("Line %d, col %d: unterminated string literal\n", lineNum, invColumnNum); lineNum++; columnNum = 1; BEGIN 0;}
<INVSTR>\"							   	{BEGIN 0;}

"\t"|"\f"|" " 	{columnNum += yyleng;}
"\n"|"\r"|"\r\n"      {lineNum++; columnNum = 1;}

.		{printf("Line %d, col %d: illegal character (%c)\n", lineNum, columnNum, yytext[0]); columnNum+=yyleng;} 

%%
int main(int argc, char *argv[]){
    if(argc == 2){
        if(strcmp(argv[1], "-l") == 0){
            /*deve mostrar o resultado*/
            aux=1;
        } else if(strcmp(argv[1], "-1") == 0){
        
        }
    }
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}



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
MINUS   "−" 
STAR    "*" 
DIV "/" 
MOD "%" 
NOT "!" 
ASSIGN  "=" 
SEMI    ";" 
COMMA   ","

RESERVED    "++"|"--"|null|abstract|continue|for|new|switch|assert|default|package|synchronized|goto|private|this|break|implements|protected|throw|byte|import|throws|case|enum|instanceof|return|transient|catch|extends|short|try|final|interface|finally|long|strictfp|volatile|const|native|super|char|float    

ID  [a-zA-Z_$]([a-zA-Z_$0-9])* 

NUMERO  [0-9]+(_*[0-9]+)*

DECLIT 0|[1-9][0-9]*|{[1-9]+(_*[0-9]+)*}

REALLIT ({NUMERO})* "."? {NUMERO} ([Ee])? ([+-][{NUMERO}])?

%%
 
{OCURV}     {printf("OCURV");}
{CCURV}     {printf("CCURV");}
{OBRACE}    {printf("OBRACE");}
{CBRACE}    {printf("CBRACE");}
{OSQUARE}   {printf("OSQUARE");}
{CSQUARE}   {printf("CSQUARE");}
{AND}       {printf("AND");}
{OR}        {printf("OR");}
{LT}        {printf("LT");}
{GT}        {printf("GT");}
{EQ}        {printf("EQ");}
{NEQ}       {printf("NEQ");}
{LEQ}       {printf("LEQ");} 
{GEQ}       {printf("GEQ");}
{PLUS}      {printf("PLUS");}
{MINUS}     {printf("MINUS");}
{STAR}      {printf("STAR");}
{DIV}       {printf("DIV");}
{MOD}       {printf("MOD");}
{NOT}       {printf("NOT");}
{ASSIGN}    {printf("ASSIGN");}
{SEMI}      {printf("SEMI");}
{COMMA}     {printf("COMMA");}

{BOOL}          {printf("BOOL");}
{BOOLLIT}       {printf("BOOLLIT");}
{CLASS}         {printf("CLASS");}
{DO}            {printf("DO");}
{DOTLENGTH}     {printf("DOTLENGTH");}
{DOUBLE}        {printf("DOUBLE");}
{ELSE}          {printf("ELSE");}
{IF}            {printf("IF");}
{INT}           {printf("INT");}
{PARSEINT}      {printf("PARSEINT");}
{PRINT}         {printf("PRINT");}
{PUBLIC}        {printf("PUBLIC");}
{RETURN}        {printf("RETURN");}
{STATIC}        {printf("STATIC");}
{STRING}        {printf("STRING");}
{VOID}          {printf("VOID");}
{WHILE}         {printf("WHILE");}

{RESERVED}  {printf("RESERVED(%s)", yytext);}


%%
int main(int argc, char *argv[]){
    if(argc == 2){
        if(strcmp(argv[1], "-l") == 0 || strcmp(argv[1], "-1") == 0){
            /*deve mostrar o resultado*/
        }
    }else{
        /*se nada no stdin só mostrar mensagens de erro*/
    }
    yylex();
    return 0;
}

int yywrap(){
    return 1;
}


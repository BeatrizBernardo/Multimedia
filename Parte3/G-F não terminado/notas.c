#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char *removechar( char *string){
    char t = '_';
    char *str = strdup(string);
    int i,j;
    i = 0;
    while(i<strlen(str))
    {
        if (str[i]==t) 
        { 
            for (j=i; j<strlen(str); j++)
                str[j]=str[j+1];   
        } else i++;
    }
    return str;
}

int main(){
    int a = 2;
    float x = 1.7976931348623157E308;
    float y = 1.797693134;
    printf("@@@@ %f\n", (a == 1? x:y));
    return 0;
}
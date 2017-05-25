#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int atoi(const char *str);
int main(int argc, char *argv[]){
    /*int d = 7;
    float f = 5.5;
    printf("%d\n", a(2,3,4));
    printf("Error: two parameters required.");
    printf("%d\n", 2);
    printf("Error: two parameters required.");
    printf("%f\n", 4.4);
    printf("Error: two parameters required.");
    printf("%f\n", h(6,7,8));
    printf("Error: two parameters required.");
    printf("%d\n", d);
    printf("%f\n", f);*/
    int n = 3;
    int d,e, f;
    if(argc >= 3){
        d = atoi(argv[1]);
        e = atoi(argv[2]);
        f = atoi(argv[3]);
    }
    
    printf("%d\n", d);
    
    return 0;

}

void coisas(int a){
    printf("%d %d %d\n", a, 6, 7);
    printf("senas e cenas\n");
    printf("%f\n", 5.5);
}
int cenas(int a, double c){
    return a;
}



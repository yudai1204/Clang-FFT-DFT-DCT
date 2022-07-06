#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

typedef struct{
    double r, j;
} COMPLEX;

COMPLEX jadd(COMPLEX x, COMPLEX y){
    COMPLEX result;
    result.r = x.r + y.r;
    result.j = x.j + y.j;
    return result;
}
COMPLEX jsub(COMPLEX x, COMPLEX y){
    COMPLEX result;
    result.r = x.r - y.r;
    result.j = x.j - y.j;
    return result;
}
COMPLEX jmul(COMPLEX x, COMPLEX y){
    COMPLEX result;
    result.r = x.r * y.r - x.j * y.j;
    result.j = x.r * y.j + x.j * y.r;
    return result;
}
COMPLEX jdiv(COMPLEX x, COMPLEX y){
    COMPLEX result,denominator,numerator;
    denominator.r = y.r * y.r + y.j * y.j;
    denominator.j = 0;
    numerator.r = x.r * y.r + x.j * y.j;
    numerator.j = x.j * y.r - x.r * y.j;
    result.r = numerator.r / denominator.r;
    result.j = numerator.j / denominator.r;
    return result;
}
void printComp(COMPLEX x){
    if(x.r != 0 || (x.r == 0 && x.j == 0))
        printf("%.1lf",x.r);
    if(x.j != 0 )
        printf("%+.1lfj",x.j);
    printf("\n");
}

COMPLEX kadai1(int k){
    COMPLEX x;
    if(k == 0){
        x.r = 2;
        x.j = 1;
        return x;
    }
    x.r = 1;
    x.j = 2;
    return jmul(x,kadai1(k-1));
}

int main(void){
    COMPLEX x, y;
    x.r = 1;x.j=1;
    y.r = 1;y.j=2;
    printComp(kadai1(10));
    printComp(kadai1(20));
}
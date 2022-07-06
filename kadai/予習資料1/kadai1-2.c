// ./kadai1.png
// 1以上の整数kに対して，f1(k)が次式で与えられるとき，f1(25)，f1(50)を求めよ
// f1(k) = Σ[k-1][n=0](n^2 - 10n)

// ./kadai2.png
// 1以上の𝑘𝑘に対し，f2(k)が次式で与えられるとき，f2(30)， f2(50)を求めよ．
// 答えを小数第二位で四捨五入し，回答せよ
// f2(k) = Σ[k-1][n=0](sin nπ/100)

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <math.h>

double kadai1(double k){
    double sum = 0;
    for(int i=0; i < k; i++ ){
        sum += i*i - 10*i;
    }
    return sum;
}

double kadai2(double k){
    double sum = 0;
    for(int i=0; i < k; i++ ){
        sum += sin(i*M_PI/100);
    }
    return round(sum*10)/10;
}

int main(void){

    printf("f1(25)=%g\n",kadai1(25));
    printf("f1(50)=%g\n",kadai1(50));

    printf("f2(30)=%g\n",kadai2(30));
    printf("f2(50)=%g\n",kadai2(50));
    return 0;
}
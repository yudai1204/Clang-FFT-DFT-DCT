#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"


/* ----------------------------- メイン関数 ----------------------------- */
int main(void){
    //変数定義
    int n = 8;
    int m = expCheck(n);
    if(m == -1){
        return 0;
    }
    COMPLEX* W = getwn(n);
    printCompArray(n,W);
    /*
    printf("bit reverse\n");
    for(int i = 0; i < n; i++){
        printf("%d %lu\n",i,bitReverse(i,m-1));
    }
    */
        return 0;
}

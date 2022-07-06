#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"


/* ----------------------------- メイン関数 ----------------------------- */
int main(void){
    //変数定義
    int n;
    COMPLEX input[N_MAX];
    char filename[] = "DFT_b.txt";
    // ファイルオープン
    n = readRealasComp(filename,input);
    if(n == -1) return 0;
    //初期化
    COMPLEX *output = (COMPLEX*)malloc(n * sizeof(COMPLEX));
    COMPLEX *output2 = (COMPLEX*)malloc(n * sizeof(COMPLEX));
    initComp(n,output);
    initComp(n,output2);
    //計算
    DFT(n,input,output);
    //iDFT(n,output,output2);
    // highpassDFT(n,input,output,10,100);
    //出力
    // double* power = getPowerArray(n,output);
    // printArray(n/2,power);
    //printCompArray(n,output);
    //printCompArray(n,output);
    printCompArray(n,output);
    return 0;
}

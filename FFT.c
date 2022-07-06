#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"


/* ----------------------------- メイン関数 ----------------------------- */
int main(void){
    printf("------------\n");
    //変数定義
    int n;
    COMPLEX input[N_MAX];
    char filename[] = "FFT_a.txt";
    // ファイルオープン
    n = readRealasComp(filename,input);
    if(n == -1) return 0;
    //fftできるかチェック
    if(expCheck(n) == -1){
        return 0;
    }
    //初期化
    COMPLEX *output = (COMPLEX*)malloc(n * sizeof(COMPLEX));
    COMPLEX *output2 = (COMPLEX*)malloc(n * sizeof(COMPLEX));
    initComp(n,output);
    initComp(n,output2);
    //計算
    //FFT(n,input,output);
    //iFFT(n,output,output2);
    //SFFT
    FFT(256,&input[4096-256],output);
    //出力
    double* output3 = getPowerArray(256,output);
    printArray(256,output3);
    //printf("%.1lf\n",rounding(output[10]));
    //printComp(output[10]);
    return 0;
}

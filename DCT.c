#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"

/* ----------------------------- メイン関数 ----------------------------- */
int main(void){
    //変数定義
    int n = 128;
    double input[N_MAX];
    char filename[] = "DCT_a.txt";
    // ファイルオープン
    n = readReal(filename,input);
    if(n == -1) return 0;
    //初期化
    double *output = (double*)malloc(n * sizeof(double));
    double *output2 = (double*)malloc(n * sizeof(double));
    init(n,output);
    init(n,output2);
    //計算
    DCT(n,input,output);
    // quant(n,output,output2);
    // init(n,output);
    //iDCT(n,output2,output);
    //出力
    printArray(n,output);
    // printf("%.1lf\n",rounding(output[10]));
    return 0;
}

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
    char filename[] = "inputs/AudioSignal.csv";
    // ファイルオープン
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error\n");
        return -1;
    }
    if(debug) printf("---start loading.---\n");
    int line;
    fscanf(fp, "%d", &line);
    printf("line: %d\n", line);
    for( n=0; fscanf(fp, "%d,%e",&input[n].r) != EOF && n<line; n++){
        input[n].j = 0;
        if(debug) printf("input[%d].r = %lf\n",n,input[n].r);
    }
    printf("n: %d\n",&n);
    if(debug) printf("---loading completed.---\n");
    fclose(fp);
    //初期化
    COMPLEX *output = (COMPLEX*)malloc(line * sizeof(COMPLEX));
    COMPLEX *output2 = (COMPLEX*)malloc(line * sizeof(COMPLEX));
    initComp(line,output);
    initComp(line,output2);
    //計算
    DFT(line,input,output);
    //iDFT(n,output,output2);
    // highpassDFT(n,input,output,10,100);
    //出力
    double* power = getPowerArray(line,output);
    printArray(n,power);
    //printCompArray(n,output);
    //printCompArray(n,output);
    //printCompArray(line,output);
    return 0;
}

#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"

#define TYPE COMPLEX

/* ----------------------------- メイン関数 ----------------------------- */
int main(void){
    //変数定義
    int n=LINES,er;
    double input[N_MAX][COLMUNS];
    char filename[] = "inputs/2dim.txt";
    // ファイルオープン
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error\n");
        return -1;
    }
    for(int i=0; i<LINES; i++){
        for(int j=0; j<COLMUNS; j++){
            if(fscanf(fp, "%lf", &input[i][j]) == EOF && i*j > LINES*COLMUNS){
                printf("ERROR");
                return -1;
            }
        }
    }
    //変数用意
    TYPE** temp = (TYPE**)malloc(LINES * sizeof(TYPE*));
    for(int i=0; i<LINES; i++){
        temp[i] = (TYPE*)malloc(COLMUNS * sizeof(TYPE));
    }
    TYPE** output = (TYPE**)malloc(LINES * sizeof(TYPE*));
    for(int i=0; i<LINES; i++){
        output[i] = (TYPE*)malloc(COLMUNS * sizeof(TYPE));
    }
    TYPE** output2 = (TYPE**)malloc(LINES * sizeof(TYPE*));
    for(int i=0; i<LINES; i++){
        output2[i] = (TYPE*)malloc(COLMUNS * sizeof(TYPE));
    }
    //初期化
    for(int i=0; i<LINES; i++){
        for(int j=0; j<COLMUNS; j++){
            temp[i][j].r = 0;
            temp[i][j].j = 0;
            output[i][j].r = 0;
            output[i][j].j = 0;
            output2[i][j].r = 0;
            output2[i][j].j = 0;
        }
    }
    
    //計算
    //---------------------------------DFT-----------------------------
    //縦方向にDFTする
    //配列を用意
    TYPE* arrayI = (TYPE*)malloc(LINES * sizeof(TYPE));
    TYPE* arrayO = (TYPE*)malloc(LINES * sizeof(TYPE));
    for (int i = 0; i < LINES; i++){
        for(int j = 0; j < LINES; j++){
            arrayI[j].r = input[j][i];
            arrayI[j].j = 0;
            arrayO[j].r = 0;
            arrayO[j].j = 0;
        }
        //ここでDCT・DFT・FFT
        DFT(LINES,arrayI,arrayO);
        //ここまで
        for(int j = 0; j < LINES; j++){
            temp[j][i] = arrayO[j];
        }
    }
    
    //横方向にDFTする
    for (int i = 0; i < COLMUNS; i++){
        DFT(COLMUNS,&temp[i][0],&output[i][0]);
    }
    //---------------------------------iDFT-----------------------------
    //縦方向にiDFTする
    for (int i = 0; i < LINES; i++){
        for(int j = 0; j < LINES; j++){
            arrayI[j].r = output[j][i].r;
            arrayI[j].j = output[j][i].j;
            arrayO[j].r = 0;
            arrayO[j].j = 0;
        }
        //ここでDCT・DFT・FFT
        iDFT(LINES,arrayI,arrayO);
        //ここまで
        for(int j = 0; j < LINES; j++){
            temp[j][i] = arrayO[j];
        }
    }
    
    //横方向にiDFTする
    for (int i = 0; i < COLMUNS; i++){
        iDFT(COLMUNS,&temp[i][0],&output2[i][0]);
    }
    //---------------------------------出力-----------------------------
    //出力
    for(int i = 0; i < LINES; i++){
        for(int j = 0; j < COLMUNS; j++){
            printf("%4.1lf %c j%4.1lf   ",output2[i][j].r, (output2[i][j].r<0)?'-':'+' ,fabs(output2[i][j].j));
        }
        printf("\n");
    }
    //メモリ開放
    free(arrayI);
    free(arrayO);
    free(temp);
    free(output);
    free(output2);
    return 0;
}

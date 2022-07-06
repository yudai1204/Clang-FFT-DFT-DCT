#define _USE_MATH_DEFINES
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "util.h"

/* ----------------------------- 便利関数 ----------------------------- */
//読み込み
int readReal(char *filename, double *input){
    int n=0;
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error\n");
        return -1;
    }
    if(debug) printf("---start loading.---\n");
    for( n=0; fscanf(fp, "%lf",&input[n]) != EOF; n++){
        if(debug) printf("input[%d] = %lf\n",n,input[n]);
    }
    if(debug) printf("---loading completed.---\n");
    fclose(fp);
    return n;
}
int readRealasComp(char *filename, COMPLEX *input){
    int n=0;
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error\n");
        return -1;
    }
    if(debug) printf("---start loading.---\n");
    for( n=0; fscanf(fp, "%lf",&input[n].r) != EOF; n++){
        input[n].j = 0;
        if(debug) printf("input[%d].r = %lf\n",n,input[n].r);
    }
    if(debug) printf("---loading completed.---\n");
    fclose(fp);
    return n;
}
int readReal2dim(char *filename, double input[][COLMUNS]){
    /*
    double** input = (double**)malloc(line * sizeof(double*));
    for(int i=0; i<line; i++){
        input[i] = (double*)malloc(column * sizeof(double));
    }
    */
    FILE *fp;
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error\n");
        return -1;
    }
    if(debug) printf("---start loading.---\n");
    
    for(int i=0; i<LINES; i++){
        for(int j=0; j<COLMUNS; j++){
            if(fscanf(fp, "%lf", &input[i][j]) == EOF && i*j > LINES*COLMUNS){
                printf("ERROR");
                return -1;
            }
        }
    }
    if(debug) printf("---loading completed.---\n");
    return 0;
}
COMPLEX changeDoubleToComplex(double input){
    COMPLEX output;
    output.r = input;
    output.j = 0;
    return output;
}
//初期化
void init(int n, double *output){
    for(int i=0; i<n; i++){
        output[i] = 0;
    }
    if(debug) printf("---init done.---\n");
}
void initComp(int n, COMPLEX *output){
    for(int i=0; i<n; i++){
        output[i].r = output[i].j =  0;
    }
    if(debug) printf("---init done.---\n");
}

//四捨五入
double rounding( double in){
    return round(in*order)/order;
}
//出力
void printArray(int n, double *input){
    for(int i=0; i<n; i++){
        if(order == 10)
            printf("%.1lf\n",rounding(input[i]));
        else
            printf("%g\n",rounding(input[i]));
    }
}

void printComp(COMPLEX input){
    if(rounding(input.r) != 0 || (rounding(input.r) == 0 && rounding(input.j) == 0)){
        if(order == 10)
            printf("% 7.1lf",rounding(input.r));
        else
            printf("%g",rounding(input.r));
    }
    if(rounding(input.j) != 0 ){
        if(order == 10)
            printf("%+ 7.1lfj",rounding(input.j));
        else
            printf("%+gj",rounding(input.j));
    }
    printf("\n");
}

void printCompArray(int n, COMPLEX *input){
    for(int i=0; i<n; i++){
        printComp(input[i]);
    }
}
unsigned long bitReverse(int input,char bit){
    unsigned long reversed = 0;
    for(int i=0; i<bit+1; i++){
        if(input & 1)
            reversed |= (1 << (bit-i));
        input >>= 1;
    }
    return reversed;
}
int expCheck(int n){
    int cnt;
    for(cnt = 0; n > 1; cnt++){
        if(n%2){
            printf("ERROR: 入力が2のべき乗ではありません\n");
            return -1;
        }
        n/=2;
    }
    return cnt;
}

/* ----------------------------- 複素数系関数 ----------------------------- */
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

COMPLEX* getwn(int n){
    COMPLEX* W = (COMPLEX*)malloc(n*sizeof(COMPLEX));
    for(int i = 0; i < n; i++){
        W[i].r = cos((-2*i*M_PI)/n);
        W[i].j = sin((-2*i*M_PI)/n);
    }
    return W;
}
COMPLEX* getiwn(int n){
    COMPLEX* W = (COMPLEX*)malloc(n*sizeof(COMPLEX));
    for(int i = 0; i < n; i++){
        W[i].r = cos((2*i*M_PI)/n);
        W[i].j = sin((2*i*M_PI)/n);
    }
    return W;
}
/* ----------------------------- 計算関数 ----------------------------- */
//DCT
void DCT( int n, double *input, double *output){
    if(debug) printf("---starting DCT.---\n");
    for( int i=0; i<n; i++){
        for( int j=0; j<n; j++){
            output[i] += input[j]*cos((2*j+1)*i*M_PI/(2*n));
        }
    }
    if(debug) printf("---DCT done.---\n");
}
//逆DCT
void iDCT( int n, double *input, double *output){
    if(debug) printf("---starting iDCT.---\n");
    for( int i=0; i<n; i++){
        output[i] = input[0]/(double)(2);
        for( int j=1; j<n; j++){
            output[i] += input[j]*cos((2*i+1)*j*M_PI/(2*n));
        }
        output[i] = (2*output[i])/n;
    }
    if(debug) printf("---iDCT done.---\n");
}
//量子化
void quant( int n, double *input, double *output){
    if(debug) printf("---starting quant.---\n");
    for( int i=0; i<n; i++){
        output[i] = floor( input[i] / 20 + 0.5 ) * 20;
    }
    if(debug) printf("---quant done.---\n");
}
//DFT
void DFT(int n, COMPLEX *input, COMPLEX *output){
    if(debug) printf("---starting DFT.---\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            COMPLEX temp, temp2;
            temp.r = cos((-2*M_PI*i*j)/n);
            temp.j = sin((-2*M_PI*i*j)/n);
            output[i] = jadd( output[i] , jmul(input[j], temp) );
        }
    }
    if(debug) printf("---DFT done.---\n");
}
//逆DFT
void iDFT(int n, COMPLEX *input, COMPLEX *output){
    if(debug) printf("---starting iDFT.---\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            COMPLEX temp, temp2;
            temp.r = cos((2*M_PI*i*j)/n);
            temp.j = sin((2*M_PI*i*j)/n);
            output[i] = jadd( output[i] , jmul(input[j], temp) );
        }
        output[i].r /= n;
        output[i].j /= n;
    }
    if(debug) printf("---iDFT done.---\n");
}
//FFT
void FFT(int n, COMPLEX *defaultInput, COMPLEX *output){
    int m = expCheck(n);
    COMPLEX* W = getwn(n);
    //まずinputを並び替える
    COMPLEX* input = (COMPLEX*)malloc(n*sizeof(COMPLEX));
    for(int i = 0; i < n; i++){
        input[i] = output[i]= defaultInput[bitReverse(i,m-1)];
    }
    //再帰する
    block(n, n, W, input, output);
    free(input);
}
void block(int n, int rootn, COMPLEX *W, COMPLEX *input, COMPLEX *output){
    if(n > 2){
        //n!=2のとき(下にさらに子ブロックがあるとき)
        COMPLEX* upperChild = (COMPLEX*)malloc(n/2 * sizeof(COMPLEX));
        COMPLEX* downChild = (COMPLEX*)malloc(n/2 * sizeof(COMPLEX));
        //再帰部分 上の子と下の子をそれぞれupperChildとdownChildに入れる
        block(n/2, rootn, W, &input[0], upperChild);
        block(n/2, rootn, W, &input[n/2], downChild);
        //FFT計算部分
        //上側、横はそのままナナメは回転
        for(int i = 0; i < n/2; i++){
            output[i] = jadd(upperChild[i] , jmul(downChild[i] , W[i*(rootn/n)] ));
        }
        //下側、ナナメはそのまま横は回転
        for(int i = n/2; i < n; i++){
            output[i] = jadd(jmul(downChild[i-n/2] , W[i*(rootn/n)]), upperChild[i-n/2]);
        }
        free(upperChild);
        free(downChild);
    }else{
        //n=2のとき(一番右側のブロックの時)
        output[0] = jadd(input[0], input[1]);
        output[1] = jsub(input[0], input[1]);
    }
}
//逆FFT
void iFFT(int n, COMPLEX *defaultInput, COMPLEX *output){
    int m = expCheck(n);
    COMPLEX* W = getiwn(n);
    //まずinputを並び替える
    COMPLEX* input = (COMPLEX*)malloc(n*sizeof(COMPLEX));
    for(int i = 0; i < n; i++){
        input[i] = output[i]= defaultInput[bitReverse(i,m-1)];
    }
    //再帰する
    iblock(n, n, W, input, output);
    //nで割る
    COMPLEX ncom; ncom.r = n; ncom.j = 0;
    for (int i=0; i<n; i++)
        output[i] = jdiv(output[i],ncom);
    free(input);
}
void iblock(int n, int rootn, COMPLEX *W, COMPLEX *input, COMPLEX *output){
    if(n > 2){
        //n!=2のとき(下にさらに子ブロックがあるとき)
        COMPLEX* upperChild = (COMPLEX*)malloc(n/2 * sizeof(COMPLEX));
        COMPLEX* downChild = (COMPLEX*)malloc(n/2 * sizeof(COMPLEX));
        //再帰部分 上の子と下の子をそれぞれupperChildとdownChildに入れる
        iblock(n/2, rootn, W, &input[0], upperChild);
        iblock(n/2, rootn, W, &input[n/2], downChild);
        //FFT計算部分
        //上側、横はそのままナナメは回転
        for(int i = 0; i < n/2; i++){
            output[i] = jadd(upperChild[i] , jmul(downChild[i] , W[i*(rootn/n)] ));
        }
        //下側、ナナメはそのまま横は回転
        for(int i = n/2; i < n; i++){
            output[i] = jadd(jmul(downChild[i-n/2] , W[i*(rootn/n)]), upperChild[i-n/2]);
        }
        free(upperChild);
        free(downChild);
    }else{
        //n=2のとき(一番右側のブロックの時)
        output[0] = jadd(input[0], input[1]);
        output[1] = jsub(input[0], input[1]);
    }
}


/* ----------------------------- フィルター関数 ----------------------------- */
//DCTローパス(ハイカット)フィルタ
void lowpassDCT( int n, double *input, double *output, int k){
    // C(i) = 0 (i >= k)
    double *temp = (double*)malloc(n * sizeof(double));
    init(n,temp);
    DCT(n,input,temp);
    for(int i = k; i <n; i++){
        temp[i] = 0;
    }
    iDCT(n,temp,output);
    free(temp);
}
//DCTハイパス(ローカット)フィルタ
void highpassDCT( int n, double *input, double *output, int k){
    // C(i) = 0 (i < k)
    double *temp = (double*)malloc(n * sizeof(double));
    init(n,temp);
    DCT(n,input,temp);
    for(int i= 0; i <k; i++){
        temp[i] =0;
    }
    iDCT(n,temp,output);
    free(temp);
}

//DFTローパス(ハイカットフィルタ)
void lowpassDFT( int n, COMPLEX *input, COMPLEX *output, int k, double sampling){
    COMPLEX *temp = (COMPLEX*)malloc(n * sizeof(COMPLEX));
    initComp(n,temp);
    DFT(n,input,temp);
    double resolution = sampling/n;
    int kinvert = k/resolution;

    for(int i = kinvert+1; i < n-kinvert; i++){
        temp[i].r = temp[i].j = 0;
    }

    iDFT(n,temp,output);
    free(temp);
}

//DFTハイパス(ローカットフィルタ)
void highpassDFT( int n, COMPLEX *input, COMPLEX *output, int k, double sampling){
    COMPLEX *temp = (COMPLEX*)malloc(n * sizeof(COMPLEX));
    initComp(n,temp);
    DFT(n,input,temp);
    double resolution = sampling/n;
    int kinvert = k/resolution;

    temp[0].r = temp[0].j = 0;
    for(int i = 1; i < kinvert; i++){
        temp[i].r = temp[i].j = 0;
        temp[n-i].r = temp[n-i].j = 0;
    }
    iDFT(n,temp,output);
    free(temp);
}

//成分を取得する
//振幅を取得
double getAmp(COMPLEX input){
    return sqrt(pow(input.r,2)+pow(input.j,2));
}
//位相を取得
double getPhase(COMPLEX input){
    return atan(input.j/input.r);
}
//パワーーーーーーーーーー！！！！！！！！！！！！！
double getPower(COMPLEX input){
    return pow(input.r,2)+pow(input.j,2);
}
//パワーを配列で出力
double* getPowerArray(int n,COMPLEX* input){
    double* output = (double*)malloc(n*sizeof(double));
    for(int i=0;i<n; i++){
        output[i] = getPower(input[i]);
    }
    return output;
}
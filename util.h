#ifndef UTIL_H_

#define true 1
#define false 0
#define rep(n) for(int i=0; i<=n; i++)
#define elif else if

#define N_MAX 131073
#define order 10 //四捨五入する時用の定数(10で第一位まで出す、100で第二位までだす)
#define debug true

#define COLMUNS 4
#define LINES   4


typedef struct{
    double r, j;
} COMPLEX;

//便利関数
int readReal(char *filename, double *input);//ファイル読み込み
int readRealasComp(char *filename, COMPLEX *input);//ファイル読み込み
int readReal2dim(char *filename, double input[][COLMUNS]);
COMPLEX changeDoubleToComplex(double input);
void init( int n,double *output );//初期化
void initComp(int n,COMPLEX *output);
double rounding( double in);      //四捨五入
void printArray(int n, double *input);//出力
void printComp(COMPLEX input);          //複素数出力
void printCompArray(int n,COMPLEX *input);//複素配列出力
unsigned long bitReverse(int input,char bit);//ビット逆順
int expCheck(int n);//べき乗チェック

//複素数計算
COMPLEX jadd(COMPLEX x, COMPLEX y);
COMPLEX jsub(COMPLEX x, COMPLEX y);
COMPLEX jmul(COMPLEX x, COMPLEX y);
COMPLEX jdiv(COMPLEX x, COMPLEX y);

COMPLEX* getwn(int n);
COMPLEX* getiwn(int n);

//演算用関数
void DCT( int n, double *input, double *output);
void iDCT( int n, double *input, double *output);
void quant( int n, double *input, double *output);
void lowpassDCT( int n, double *input, double *output, int k);
void highpassDCT( int n, double *input, double *output, int k);

void DFT(int n, COMPLEX *input, COMPLEX *output);
void iDFT(int n, COMPLEX *input, COMPLEX *output);
void lowpassDFT( int n, COMPLEX *input, COMPLEX *output, int k, double sampling);
void highpassDFT( int n, COMPLEX *input, COMPLEX *output, int k, double sampling);

void FFT(int n, COMPLEX *defaultInput, COMPLEX *output);
void block(int n, int rootn, COMPLEX *W, COMPLEX *input, COMPLEX *output);
void iFFT(int n, COMPLEX *defaultInput, COMPLEX *output);
void iblock(int n, int rootn, COMPLEX *W, COMPLEX *input, COMPLEX *output);

double getAmp(COMPLEX input);
double getPhase(COMPLEX input);
double getPower(COMPLEX input);
double* getPowerArray(int n,COMPLEX* input);

#endif /* UTIL_H_ */
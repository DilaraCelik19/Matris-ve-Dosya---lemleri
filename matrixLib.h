/*matrixLib.h Dosyası
 Matrislerde ve vektörlerde bizden istenen birtakım işlemleri yapan bir proje.
 1.Proje
 04.12.2022
 Dilara Çelik dilara_celik@stu.fsm.edu.tr

*/
#ifndef MATRIXLIB_H
#define MATRIXLIB_H

float *returnVector(int );
float **returnMatrix(int, int );
void freeMatrix(float **, int );
void fillMatrix(float **,int ,int ,int );
void fillVector(float *,int ,int );
float mean(float *, int );
float covariance(float *, float *, int );
float correlation(float *, float *, int );
float **matrixMultiplication(float **, float **, int , int , int , int );
float **matrixTranspose(float **, int , int );
float *rowMeans(float **, int , int );
float *columnMeans(float **, int , int );
float **covarianceMatrix(float **, int , int );
float determinant(float **, int );
void  printVector(int ,float * );
void printMatrix(float **, int , int );

#endif
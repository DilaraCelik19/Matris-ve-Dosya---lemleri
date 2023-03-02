#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
/*matrixLib.c Dosyası
 Matrislerde ve vektörlerde bizden istenen birtakım işlemleri yapan bir proje.
 1.Proje
 04.12.2022
 Dilara Çelik dilara_celik@stu.fsm.edu.tr

*/
float *returnVector(int size)
{
    float *p = (float *)malloc(size * sizeof(float)); // Dinamik şekilde bir vektör oluşturdum

    
    return p;
}

float **returnMatrix(int row, int col)
{

    float **matris = (float **)malloc(row * sizeof(float*)); // Dinamik bir şekilde 2 boyutlu matris oluşturdum.
    for (int i = 0; i < row; i++)
    {
        matris[i] = malloc(col * sizeof(float));
    }

    return matris;
}

void freeMatrix(float **mat, int row)
{

    for (int i = 0; i < row; i++)
    {
        free(mat[i]); // Tahsis edilen belleği boşalttı.
    }
    free(mat);
}

void fillMatrix(float **mat,int row,int col,int seed){
   srand(seed);
   for (int i = 0; i < row; i++)
   {
    for (int j = 0; j < col; j++)
    {
        mat[i][j]= (float)(1+rand()%10);
    }
    
   }
   
}
void fillVector(float *vec,int size,int seed){
    srand(seed);
    for (int i = 0; i < size; i++)
    {
        vec[i]=(float)(1+rand()%10);
    }
    
}

float mean(float *vec, int size)
{
    float sum = 0.0;
    float mean = 0.0;
    for (int i = 0; i < size; i++)
    {
        sum += vec[i]; // Vektörün elemanlarını topluyor.
    }
    mean = sum / size; // Toplamı vektörün uzunluğuna bölünce vektörün ortalamasını alıyorum.
    return mean;
}
float covariance(float *vec1, float *vec2, int size)
{
    float mean1 = mean(vec1, size); // 1.vektörün ortalamasını veriyor.
    float mean2 = mean(vec2, size); // 2.vektörün ortalamasını veriyor.
    float process1 = 0;
    float process2 = 0;
    float product = 1;
    float sum = 0;
    for (int i = 0; i < size; i++)
    {
        process1 = vec1[i] - mean1;    // 1.vektörün elemanlarını ortalamasından çıkarıyor.
        process2 = vec2[i] - mean2;    // 2.vektörün elemanlarını ortalamasından çıkarıyor.
        product = process1 * process2; // 1.ve 2.işlemi çarpıyor.

        sum += product; // Ve çarpımı topluyor.
    }
    return sum / (size - 1);
}

float correlation(float *vec, float *vec2, int size)
{
    float mean1 = mean(vec, size);  // 1.vektörün ortalamasını alıyor.
    float mean2 = mean(vec2, size); // 2.vektörün ortalamasını alıyor.
    float sum1 = 0;
    float sum2 = 0;
    float var1 = 1;
    float var2 = 1;
    for (int i = 0; i < size; i++)
    {
        sum1 += (vec[i] - mean1) * (vec[i] - mean1);   // 1.vektörün elemanlarından ort çıkartarak karesini alıyor
        sum2 += (vec2[i] - mean2) * (vec2[i] - mean2); // 2.vektörün elemanlarından ort çıkartarak karesini alıyor
    }
    var1 = sum1 / (float)(size - 1);
    var2 = sum2 / (float)(size - 1);
    // Aşağıda iki vektörün kovaryansı alınıyor ve var1 var2 nin çarpımının kareköküne bölünüyor.
    return covariance(vec, vec2, size) / sqrt(var1 * var2);
}

float **matrixMultiplication(float **mat1, float **mat2, int row1, int col1, int row2, int col2)
{

    if (col1 != row2) // col1 ve row2 eşit değilse çarpım işlemini yapmıyor.
    {
        printf("Matrices are not suitable for multiplication");
        exit(0);
    }
    float **multiplicationMatrix = returnMatrix(row1, col2); // Dinamik şekilde bir matris oluşturuldu.
    for (int i = 0; i < row1; i++)
    {
        for (int j = 0; j < col2; j++)
        {
            float sum = 0;
            for (int k = 0; k < col1; k++)
            {
                sum += mat1[i][k] * mat2[k][j]; // 1.matrisin satırı 2.matrisin sütunuyla çarpılır.
            }
            multiplicationMatrix[i][j] = sum;
        }
    }
    return multiplicationMatrix;
}
float **matrixTranspose(float **mat, int row, int col)
{
    float **matris = returnMatrix(col, row); // Yeni bir matris oluştu.
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            matris[j][i] = mat[i][j]; // Satır ve sütunlar bu işlemle yer değiştirir.
        }
    }

    return matris;
}
float *rowMeans(float **mat, int row, int col)
{

    float *rowMeanmatris = (float *)malloc(row * sizeof(float));

    for (int i = 0; i < row; i++)
    {
        float toplam = 0;
        for (int j = 0; j < col; j++)
        {
            toplam += mat[i][j]; // Matrisin satırındaki elemanları toplar.
        }

        rowMeanmatris[i] = toplam / col; // Satırların ortalamasını alır.
    }
    return rowMeanmatris;
}

float *columnMeans(float **mat, int row, int col)
{
    float *columnMeanmatris = (float *)malloc(col * sizeof(float));

    for (int i = 0; i < col; i++)
    {
        float toplam = 0;
        for (int j = 0; j < row; j++)
        {
            toplam += mat[j][i]; // Matrisin sütunlarındaki elemanları toplar.
        }

        columnMeanmatris[i] = toplam / row; // Sütunların ortalamasını alır.
    }
    return columnMeanmatris;
}

float **covarianceMatrix(float **mat, int row, int col)
{
    if (row != col) // Satır ve sütun eşit değilse bu işlem olmaz.Bunu kontrol eder.
    {
        printf("This operation cannot be done");
        exit(0);
    }
    else
    {
        float *mean = columnMeans(mat, row, col);
        float **matris = returnMatrix(row, col);

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < col; j++)
            {
                matris[i][j] = mat[i][j] - mean[i]; // Matrisin elemanlarından sütun ort çıkarır.
            }
        }

        float **transpoze = matrixTranspose(matris, row, col);
        float **matrixmultiplication = matrixMultiplication(transpoze,matris, col, row, row, col);

        float **lastMatris = returnMatrix(col, col);
        for (int i = 0; i < col; i++)
        {

            for (int j = 0; j < col; j++)
            {

                lastMatris[i][j] = matrixmultiplication[i][j] / (float)(row); // Çarptığı matrisi satır sayısına böler ve son matrisimize atar.
            }
        }
        return lastMatris;
    }
}

float determinant(float **mat, int row)
{
    if (row != 3)
    {
        printf("Determinant cannot be calculated");
        exit(0);
    }
    int col = row + 2;
    for (int i = 0; i < row; i++)
    {
        mat[i] = realloc(mat[i], col * sizeof(float)); // Matrisin sütunlarını genişlettim.
    }

    for (int i = 0; i < row; i++)
    {
        mat[i][3] = mat[i][0];
        mat[i][4] = mat[i][1];
    }

    float *plusVector = returnVector(3);  // Artıları boyutu 3 olan  vektörde tuttum
    float *minusVector = returnVector(3); // Eksileri boyutu 3 olan vektörde tuttum.

    for (int i = 0; i < col - 2; i++)
    {
        int k = i;
        float multiplication = 1;
        for (int j = 0; j < row; j++)
        {
            multiplication *= mat[j][k]; // Artı ile çarpılan sayıların çarpımını tutan değeri alıyoruz.
            k++;
        }
        plusVector[i] = multiplication; // Çarpımı ise artıları tutan vektöre atadım.
    }

    for (int i = 0; i < col - 2; i++)
    {
        int m = i;
        float minusMultiplication = 1;
        for (int j = 2; j >= 0; j--)
        {
            minusMultiplication *= mat[j][m];
            m++;
        }
        minusVector[i] = minusMultiplication;
    }

    float det = 0;
    for (int i = 0; i < 3; i++)
    {
        det += plusVector[i];
        det -= minusVector[i];
    }

    return det;
}

void printVector(int size, float *vec)
{
    for (int i = 0; i < size; i++)
    {
        printf("%.1f ", vec[i]);
    }
}

void printMatrix(float **mat, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%f ", mat[i][j]);
        }
        printf("\n");
    }
}

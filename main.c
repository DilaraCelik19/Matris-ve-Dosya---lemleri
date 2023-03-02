#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrixLib.h"
/*main.c Dosyası
 Dosya işlemleriyle matrise birtakım işlemleri yapan bir proje.
 2.Proje
 21.12.2022
 Dilara Çelik dilara_celik@stu.fsm.edu.tr

*/

typedef enum
{
    Irissetosa = 1,
    Irisversicolor = 2,
    Irisvirginica = 3
} Species;

typedef struct
{
    int id;
    float SepalLengthCm;
    float SepalWidthCm;
    float PetalLengthCm;
    float PetalWidthCm;
    Species species;

} IrisDataType;



void printCorelation(FILE *fp, float **matrix)
{
  fprintf(fp, "Corelation of properties: \n\n");

  
  fprintf(fp, "SepalLengthCm and PetalLenghthCm : %.3f\n", correlation(matrix[0], matrix[2], 150));
  fprintf(fp, "SepalLengthCm and SepalWidthCm : %.3f\n", correlation(matrix[0], matrix[1], 150));

  fprintf(fp, "SepalLengthCm and PetalWidthCm : %.3f\n", correlation(matrix[0], matrix[3], 150));
  fprintf(fp, "SepalWidthCm and PetalLenghthCm : %.3f\n", correlation(matrix[1], matrix[2], 150));
 
  fprintf(fp, "PetalLenghthCm and PetalWidthCm : %.3f\n", correlation(matrix[2], matrix[3], 150));
   fprintf(fp, "SepalWidthCm and PetalWidthCm : %.3f\n", correlation(matrix[1], matrix[3], 150));
  fprintf(fp, "\n\n");
}
float variance( float *array,int size)
{
    float sum = 0.0;
  float arrMean = mean(array, size);
  
  for (int i = 0; i < size; i++)
  {
    sum += (array[i] - arrMean) * (array[i] - arrMean);
  }
   float result=sum/size;
  return result;
}
void printVariance(FILE *file, float **matrix)
{
  fprintf(file," Variance of properties SepalLengthCm, SepalWidthCm, PetalLengthCm ve PetalWidthCm :\n\n");
  fprintf(file,"SepalLengthCm: %.3f\n", variance( matrix[0],150));
  fprintf(file,"SepalWidthCm: %.3f\n", variance( matrix[1],150));
  fprintf(file,"PetalLengthCm: %.3f\n", variance( matrix[2],150));
  fprintf(file,"PetalWidthCm: %.3f\n", variance( matrix[3],150));
  fprintf(file, "\n\n");
}

void printMeans(FILE *file, float **matrix)
{
  fprintf(file, " Mean of properties SepalLengthCm, SepalWidthCm, PetalLengthCm ve PetalWidthCm:\n");

  fprintf(file, "%.3f\n",mean(matrix[0], 150)); //özelliklerin ortalamasını basıyor
  fprintf(file, "%.3f\n",mean(matrix[1], 150));
  fprintf(file, "%.3f\n",mean(matrix[2], 150));
  fprintf(file, "%.3f\n",mean(matrix[3], 150));
  fprintf(file, "\n");
}

void addDataToMatrix(IrisDataType *dizi, float **matris)
{
  for (int i = 0; i < 150; i++)
  {
    matris[i][0] = dizi[i].SepalLengthCm; //Dizideki verileri teker teker matrise yazıyor.
    matris[i][1] = dizi[i].SepalWidthCm;
    matris[i][2] = dizi[i].PetalLengthCm;
    matris[i][3] = dizi[i].PetalWidthCm;
  }
}
void writeFile(){
     FILE *file = fopen("IrisStatistic.txt", "w");
    if (file == NULL)
    {
        printf("ERROR ");
    }
}
void printCovMatris(FILE *fp,float **matris){
   
   fprintf(fp,"Covariance Matrix:");
    
    float ** covM=covarianceMatrix(matris,150,4);//matrisin kovaryansını alıp basıyor
    for (int i = 0; i < 4; i++)
    {
       for (int j = 0; j < 4; j++)
       {
        fprintf(fp, "%.2f ",covM[i][j]); 
       }
        fprintf(fp, "\n\n");
    }   
    
    
}

int main()
{
 

  // Burada dosyayı açma işlemini yapıyoruz
  FILE *fp = fopen("Iris.csv", "r");
  if (fp == NULL)
  {
    printf("The file cannot open: %s\n", "Iris.csv");
    return 1;
  }

  // Burada ise CSV dosyasındaki verileri tutacak matrisi oluşturuyoruz.
  char temporary[1024];
  int counter = atoi(fgets(temporary, 1024, fp));
  //Struct dizimizi dinamik bir şekilde oluşturuyoruz.
  IrisDataType *data = (IrisDataType *)malloc(sizeof(IrisDataType) * counter);

  fgets(temporary, 1024, fp);

  for (int i = 0; i < counter; i++)
  {
    char line[512];
    fgets(line, 512, fp);
    char *ptr = strtok(line, ",");
    ptr = strtok(NULL, ",");

    data[i].SepalLengthCm = atof(ptr); //struct dizisinin içine sepalLength özelliğini atıyoruz
    ptr = strtok(NULL, ",");

    data[i].SepalWidthCm = atof(ptr);//struct dizisinin içine sepalWidth özelliğini atıyoruz.
    ptr = strtok(NULL, ",");

    data[i].PetalLengthCm = atof(ptr);//struct dizisinin içine petalLength özelliğini atıyoruz.
    ptr = strtok(NULL, ",");

    data[i].PetalWidthCm = atof(ptr);//struct dizisinin içine petalWidth özelliğini atıyoruz.
    ptr = strtok(NULL, ",");

    if (strcmp(ptr, "Iris-setosa\n") == 0) //İsmi Iris-setosa olan türü diziye atıyoruz.
    {
      data[i].species = Irissetosa;
    }
    else if (strcmp(ptr, "Iris-versicolor\n") == 0)//İsmi Iris-versicolor olan türü diziye atıyoruz.
    {
      data[i].species = Irisversicolor;
    }
    else if (strcmp(ptr, "Iris-virginica\n") == 0)//İsmi Iris-virginica ise bu  türü diziye atıyoruz.
    {
      data[i].species = Irisvirginica;
    }
    else
      printf("There is something wrong.");
  }

  float **matdata = returnMatrix(150, 4); //150x4 bir matris oluşturuyoruz.
  addDataToMatrix(data, matdata);  //Matrisimizin içini dolduruyoruz

  printMatrix(matdata, 150, 4); //Burada ise  oluşan matrisi ekrana basıyoruz 
  printf("*************************\n\n");
  float **transpozMat ;
  transpozMat= matrixTranspose(matdata, 150, 4); //matDatanın transpozunu alıyoruz 


  printMatrix(transpozMat, 4, 150); //Transpozu alınan matrisi ekrana basıyoruz.


   FILE *file = fopen("IrisStatistic.txt", "w");
    if (file == NULL)
    {
        printf("ERROR ");
    }
   
    float **a=matdata;
  printVariance(file, transpozMat);
  printCorelation(file, transpozMat);
  printMeans(file, transpozMat); 
  printCovMatris(file,a);

    fclose(fp);
    return 0;
}






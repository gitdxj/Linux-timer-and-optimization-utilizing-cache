/******************
代码涉及Linux系统调用
请在Linux下编译运行
*******************/

#include <iostream>
#include <stdio.h>
#include <sys/time.h>
using namespace std;
void get_matrix(double ** matrix,  int row,  int column);  // 为矩阵赋初值
void show_matrix(double **matrix,  int row,  int column);  // 显示矩阵
void get_vect(double *vect, int dimention);  // 为向量赋初值
void multiply(double **matrix, int row, int column, double *vect, int dim);  // 抛弃局部性原理进行的算法
void multiply_cache(double **matrix, int row, int column, double *vect, int dim);  // 充分利用cache的算法
int main()
{
    struct timeval start;
    struct timeval end;
    unsigned long diff;

    int row = 10000;
    int column = 10000;

    double **matrix = new double*[row];
    for(int i = 0; i<row; i++)
        matrix[i] = new double[column];
    get_matrix(matrix, row, column);
//    show_matrix(matrix, row, column);

    double *vect = new double[row];
    get_vect(vect, row);

    gettimeofday(&start, NULL);
//    multiply(matrix, row, column, vect, row);
    multiply_cache(matrix, row, column, vect, row);
    gettimeofday(&end, NULL);

    diff = 1000000*(end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

    cout << "the time diff is " << diff << "ms"<<endl;
    return 0;
}


void get_matrix(double **matrix, int row, int column)
{
    for(int i = 0; i<row; i++)
        for(int j = 0; j<column; j++)
            matrix[i][j] = i+j;
}

void show_matrix(double **matrix, int row, int column)
{
    for(int i = 0; i<row; i++){
        for(int j = 0; j<column; j++)
            printf("%f ", matrix[i][j]);
        printf("\n");
       }
}

void get_vect(double *vect, int dimention)
{
    for(int i = 0; i<dimention; i++)
        vect[i] = dimention;
}

void multiply(double **matrix, int row, int column, double *vect, int dim)
{
    double sum = 0;
    for(int i = 0; i<column; i++)
        for(int j = 0; j<row; j++)
        {
            sum += matrix[j][i] * vect[j];
        }
}

void multiply_cache(double **matrix, int row, int column, double *vect, int dim)
{
    double sum = 0;
    for(int i = 0; i<row; i++)
        for(int j = 0; j<column; j++)
        {
            sum += matrix[i][j] * vect[i];
        }
}

/******************
代码涉及Linux系统调用
请在Linux下编译运行
*******************/

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sys/time.h>
using namespace std;
void get_matrix(double ** matrix,  int row,  int column);  // 为矩阵赋初值
void show_matrix(double **matrix,  int row,  int column);  // 显示矩阵
void get_vect(double *vect, int dimention);  // 为向量赋初值
unsigned long multiply(double **matrix, double *vect, int dim);  // 抛弃局部性原理进行的算法
unsigned long multiply_cache(double **matrix, double *vect, int dim);  // 充分利用cache的算法
void time_comparison(int dim, unsigned long & time_interval_cache, unsigned long & time_intervel_no_cache);
int main()
{
    int n = 200;
    int dimension = 0;

    int *scale = new int[n];
    unsigned long *time_interval_cache = new unsigned long[n];
    unsigned long *time_interval_no_cache = new unsigned long[n];

    for(int i = 0; i < n; i++)
    {
        scale[i] = dimension;
        time_comparison(dimension, time_interval_cache[i], time_interval_no_cache[i]); cout<<endl;
        dimension += 100;
    }

    ofstream outFile;
    outFile.open("data.csv", ios::out);
    for(int i = 0; i < n; i++)
    {
        cout << "scale: " << scale[i] << endl;
        cout << "utilizing cache: " << time_interval_cache[i] << endl;
        cout << "without utilizing cache: " << time_interval_no_cache[i] << endl;
        outFile << scale[i] << ',' << time_interval_cache[i] << ',' << time_interval_no_cache[i] <<endl;
    }

    return 0;
}


void next_scale(int & scale)
{
    scale += 10;
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

unsigned long multiply(double **matrix, double *vect, int dim)
{
    struct timeval start;
    struct timeval end;
    unsigned long time_interval;

    gettimeofday(&start, NULL);

    double sum = 0;
    for(int i = 0; i<dim; i++)
        for(int j = 0; j<dim; j++)
        {
            sum += matrix[j][i] * vect[j];
        }

    gettimeofday(&end, NULL);

    time_interval = 1000000*(end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

    cout << dim << "(without utilizing cache): " << time_interval << " us" << endl;

    return time_interval;
}

unsigned long multiply_cache(double **matrix, double *vect, int dim)
{
    struct timeval start;
    struct timeval end;
    unsigned long time_interval;

    gettimeofday(&start, NULL);

    double sum = 0;
    for(int i = 0; i<dim; i++)
        for(int j = 0; j<dim; j++)
        {
            sum += matrix[i][j] * vect[i];
        }

    gettimeofday(&end, NULL);

    time_interval = 1000000*(end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

    cout << dim << "(utilizing cache): " << time_interval << " us" << endl;

    return time_interval;
}

void time_comparison(int dim, unsigned long & time_interval_cache, unsigned long & time_intervel_no_cache)
{
    double **matrix = new double*[dim];
    for(int i = 0; i<dim; i++)
        matrix[i] = new double[dim];
    get_matrix(matrix, dim, dim);

    double *vect = new double[dim];
    get_vect(vect, dim);

    time_interval_cache = multiply_cache(matrix, vect, dim);
    time_intervel_no_cache = multiply(matrix, vect, dim);

    for(int i = 0; i<dim; i++)
        delete []matrix[i];
    delete []matrix;
    delete []vect;
}

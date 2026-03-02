#define _USE_MATH_DEFINES
#include "matrix.h"
#include <stdio.h>
#include <math.h>



void init_identity_matrix (float matrix[3][3]){
    printf("Identikus matrix:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 1.0;
            }   
            else{
                matrix[i][j] = 0.0;
            }
        }   
    }
    print_matrix(matrix);
}
void skalar_times(float matrix[3][3], float value){
    printf("Skalaris szorzas:\n");
    float eredmeny[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            eredmeny[i][j] = matrix[i][j] * value;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix1[i][j] = eredmeny[i][j];
        }
    }
    print_matrix(matrix1);
}
void multiply_matrices(float matrix1[3][3], float matrix2 [3][3]){
    printf("Matrix szorzas:\n");
    float eredmeny[3][3];
    for (int i = 0; i < 3; i++)  //sor
    {
        for (int k = 0; k < 3; k++) 
        {
            eredmeny[i][k] = 0.0;
            for (int j = 0; j < 3; j++)  //oszlop
            {
                eredmeny[i][k] += matrix1[i][j]* matrix2[j][k];
            }
        }
    }
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            matrix1[i][j] = eredmeny[i][j];
        }
    }
    print_matrix(matrix1);
}
void transform_point(float homogen[3], float transzformacio [3][3]){
    printf("Transzformáció eredménye:\n");
    float eredmeny[3];
    for (int i = 0; i < 3; i++)
    {
        eredmeny[i] = 0.0;
        for (int j = 0; j < 3; j++)
        {
            eredmeny[i] += homogen[j]*transzformacio[i][j];
        }
        printf("%.4f\n", eredmeny[i]);
    }
}

void init_zero_matrix(float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            matrix[i][j] = 0.0;
        }
    }
}

void print_matrix(const float matrix[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%4.4f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void add_matrices(const float a[3][3], const float b[3][3], float c[3][3])
{
    int i;
    int j;

    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            c[i][j] = a[i][j] + b[i][j];
        }
    }
}
void shift(float matrix[3][3],float x,float y){
    float transz_matrix[3][3];
    init_identity_matrix(transz_matrix);

    transz_matrix[0][2] = x;
    transz_matrix[1][2] = y;

    multiply_matrices(transz_matrix,matrix);

}
void scale(float matrix[3][3],float x,float y){
    float transz_matrix[3][3];
    init_identity_matrix(transz_matrix);

    transz_matrix[0][0] = x;
    transz_matrix[1][1] = y;

    multiply_matrices(transz_matrix,matrix);

}
void rotate(float matrix[3][3],float fok){
    float transz_matrix[3][3];
    init_identity_matrix(transz_matrix);

    float rad = fok * M_PI / 180.0;

    float c = cos(rad);
    float s = sin(rad);

    transz_matrix[0][0] = c;
    transz_matrix[0][1] = -s;
    transz_matrix[1][0] = s;
    transz_matrix[1][1] = c;

    multiply_matrices(transz_matrix,matrix);
}

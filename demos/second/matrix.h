#ifndef MATRIX_H
#define MATRIX_H

void init_identity_matrix (float matrix[3][3]);
void skalar_times(float matrix[3][3], float value);
void multiply_matrices(float matrix1[3][3], float matrix2 [3][3],float eredmeny[][]);
void transform_point(float matrix1[3][3], float matrix2 [3][3]);


#ifndef


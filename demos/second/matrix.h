#ifndef MATRIX_H
#define MATRIX_H

void init_identity_matrix (float matrix[3][3]);
void skalar_times(float matrix[3][3], float value);
void multiply_matrices(float matrix1[3][3], float matrix2 [3][3]);
void transform_point(float homogen[3], float transzformacio [3][3]);
void shift(float matrix[3][3],float x, float y);
void scale(float matrix[3][3],float x,float y);
void rotate(float matrix[3][3],float fok);

/**
 * Initializes all elements of the matrix to zero.
 */
void init_zero_matrix(float matrix[3][3]);

/**
 * Print the elements of the matrix.
 */
void print_matrix(const float matrix[3][3]);

/**
 * Add matrices.
 */
void add_matrices(const float a[3][3], const float b[3][3], float c[3][3]);

#endif //MATRIX_H


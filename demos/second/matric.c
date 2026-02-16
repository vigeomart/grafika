#include "matrix.h"

void init_identity_matrix (float matrix[3][3]){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; i < 3; i++)
        {
            if (i == j)
            {
                matrix[i][j] = 1;
            }   
        }   
    }
}
void skalar_times(float matrix[3][3], float value){
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; i++)
        {
            matrix[i][j] *= value;
        }
    }
}
void multiply_matrices(float matrix1[3][3], float matrix2 [3][3], float eredmeny[3][3]){
    
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; i++)
        {
            
        }   
    }
}
void transform_point(float matrix1[3][3], float matrix2 [3][3]){

}


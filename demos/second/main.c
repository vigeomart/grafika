#include "matrix.h"


int main(){
    float identity_matrix[3][3];
    float matrix1[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    float matrix2[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    float orai[3][3] = {{-1,0,-6},{0,1,0},{0,0,1}};
    float homogen[3] = {-5,2,1};
    
    
    init_identity_matrix(identity_matrix);
    skalar_times(matrix1,3);
    multiply_matrices(matrix1,matrix2);
    transform_point(homogen,orai);

    shift(identity_matrix,3,0);
    rotate(identity_matrix,90);
    scale(identity_matrix,2,3);
}
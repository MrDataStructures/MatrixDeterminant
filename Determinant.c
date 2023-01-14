#include <stdio.h>
#include <stdlib.h>

long** create_matrix(long n){
    long** matrix;
    matrix = malloc(n * sizeof(long*));
    for(long i = 0; i < n; i++)
        matrix[i] = malloc(n * sizeof(long));
    return matrix;
}

long** delete_matrix(long** mat, long n){
    for(int i = 0; i < n; i++)
        free(mat[i]);
    free(mat);
}

long** make_matrix(FILE* fp, long n){
    long** matrix = create_matrix(n);
    for(long i = 0; i < n; i++)
        for(long j = 0; j < n; j++)
            fscanf(fp, "%li\n", &matrix[i][j]);
    return matrix;
}

void cofactor(long**mat, long**temp, int p, int q, int n){
    int i = 0, j = 0;
    for (int row = 0; row < n; row++){
        for(int col = 0; col < n; col++){
            if(row != p && col != q){
                temp[i][j++] = mat[row][col];
                if(j == n - 1){
                    j = 0;
                    i++;
                }
            }
        }
    }
}

long det(long**mat, int n){
    long ans = 0;
    if(n == 1)
        return mat[0][0];
 
    long sign = 1;
    long** temp = create_matrix(n);
    for(int f = 0; f < n; f++){
        cofactor(mat, temp, 0, f, n);
        ans += sign * mat[0][f] * det(temp, n - 1);
        sign = -sign;
    }
    delete_matrix(temp, n);
    return ans;
}

int main(int argc, char* argv[argc+1]){
    FILE * fp = fopen(argv[1], "r");
    long num;
    if(fp == NULL){
        printf("error");
        return EXIT_SUCCESS;
    }
    else{
        fscanf(fp, "%li\n", &num);
        long** matrix = make_matrix(fp, num);
        printf("%li\n", det(matrix, num));
        delete_matrix(matrix, num);
    }
    fclose(fp);
    return 0;
}

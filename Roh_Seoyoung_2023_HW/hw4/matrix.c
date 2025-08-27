/*
<행렬의 행(row)과 열(column)의 값을 입력 받는다. (scanf() 사용)
<모든 행렬은 동적 메모리할당(dynamic memory allocation) 방식으로 생성한다.
<Print Matrix - A와 B 행렬을 출력한다. (print matrix() 사용)
<Add Matrix - A + B를 구현한다. (함수: addition matrix())
<Subtract Matrix - A − B를 구현한다. (함수: subtraction matrix())
<Transpose matrix a - A의 전치행렬 T를 구현한다. (함수: transpose matrix())
<Multiply Matrix - A × B를 구현한다. (함수: multiply matrix())
< 모든 메뉴에서 연산이 끝나면, print matrix()를 사용하여 결과값을 프린트한다.
<연산이 종료되거나 프로그램을 종료할 때 할당했던 메모리를 해제 한다. (함수: free matrix())
*/
#include <stdio.h>
#include <stdlib.h>

/*<모든 행렬은 동적 메모리할당(dynamic memory allocation) 방식으로 생성한다.*/

int** creatematrix(int row, int col) {
    int** matrix;
    matrix = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++) {
        matrix[i] = (int *)malloc(col * sizeof(int));
    }
    return matrix;
}

void printmatrix(int **A,int An,int Am){
    for(int i=0;i<An;i++){
        if(A==0){
            break;
        }
        for(int j=0;j<Am;j++){
            printf("%d",A[i][j]);
            printf("    ");
        }
        printf("\n");
    }
}

/*<Add Matrix - A + B를 구현한다. (함수: addition matrix())*/
int **additionmatrix(int **A,int An,int Am,int **B,int Bn,int Bm){
    int **add=creatematrix(An,Am);
    if(An!=Bn||Am!=Bm){
        printf("size error: can't add\n");
        return 0;
    }
    for(int i=0;i<An;i++){
        for(int k=0;k<Am;k++){
            add[i][k]=A[i][k]+B[i][k];
        }
    }
    return add;
}

/*<Subtract Matrix - A − B를 구현한다. (함수: subtraction matrix())*/
int **subtractionmatrix(int **A,int An,int Am,int **B,int Bn,int Bm){
    if(An!=Bn||Am!=Bm){
        printf("size error: can't sub\n");
        return 0; 
    }
    int **sub=creatematrix(An,Am);
    for(int i=0;i<An;i++){
        for(int k=0;k<Am;k++){
            sub[i][k]=A[i][k]-B[i][k];
        }
    }
    return sub;
}

/*<Multiply Matrix - A × B를 구현한다. (함수: multiply matrix())*/
int **multiplymatrix(int **A,int An,int Am,int **B,int Bn,int Bm){
     if(Am!=Bn){
        printf("size error: can't mul\n");
        return 0; 
    }
    int **mul=creatematrix(An,Bm);
    for(int i=0;i<An;i++){
        for(int j=0;j<Bm;j++){
            mul[i][j]=0;
            for(int k=0;k<Am;k++){
                mul[i][j]+=A[i][k]*B[k][j];
                }
        }
    }
    return mul;
}

/*<Transpose matrix a - A의 전치행렬 T를 구현한다. (함수: transpose matrix())*/
int **transposematrix(int **array,int n,int m){
    int **result = creatematrix(m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = array[j][i];
            
        }
    }
    return result;
}

void freematrix(int **matrix, int row) {
    for (int i = 0; i < row; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    printf("[----- [문서영] [2022042011] -----]\n");
/*<행렬의 행(row)과 열(column)의 값을 입력 받는다. (scanf() 사용)*/
    /*행렬 A*/
    int N,M;
    printf("A rows count");
    scanf("%d",&N);
    printf("A cols count");
    scanf("%d",&M);
    int** matrixA = creatematrix(N,M);
    /*배열 입력 받기*/
    printf("matrix A\n");
    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            scanf("%d",&matrixA[i][j]);
        }
    }
    /*행렬 B*/
    int n,m;
    printf("B rows count");
    scanf("%d",&n);
    printf("B cols count");
    scanf("%d",&m);

    int **matrixB = creatematrix(n,m);
    /*배열 입력 받기*/
    printf("matrix B\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            scanf("%d",&matrixB[i][j]);
        }
    }

/*<Print Matrix - A와 B 행렬을 출력한다. (print matrix() 사용)*/
printf("matrixA: \n");
 printmatrix(matrixA,N,M);
printf("matrixB: \n");
 printmatrix(matrixB,n,m);

printf("A+B\n");
int **add=additionmatrix(matrixA,N,M,matrixB,n,m);
printmatrix(add,n,m);

printf("A-B\n");
int **sub=subtractionmatrix(matrixA,N,M,matrixB,n,m);
printmatrix(sub,n,m);

printf("A*B\n");
int **mul=multiplymatrix(matrixA,N,M,matrixB,n,m);
printmatrix(mul,N,m);

printf("transport A\n");
int **trans=transposematrix(matrixA,N,M);
printmatrix(trans,M,N);

/*<연산이 종료되거나 프로그램을 종료할 때 할당했던 메모리를 해제 한다. (함수: free matrix())*/
 freematrix(matrixA, N);
 freematrix(matrixB, n);

}
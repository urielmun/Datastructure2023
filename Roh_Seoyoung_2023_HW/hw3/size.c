#include<stdio.h>
#include<stdlib.h>
void main()
{
    printf("[----- [문서영] [2022042011] -----]\n");
int **x; /*int자료형을 이중참조하는 x선언*/
printf("sizeof(x) = %lu\n", sizeof(x));
printf("sizeof(*x) = %lu\n", sizeof(*x));
printf("sizeof(**x) = %lu\n", sizeof(**x));
/*36bit노트북 특성상 int, 포인터 모두 4bytes로 출력된다.*/
}
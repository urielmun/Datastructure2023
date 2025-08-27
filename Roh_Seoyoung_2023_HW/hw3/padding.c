#include <stdio.h>
struct student {
    /*struct는 타입이 다른 데이터들을 그룹화한다.*/
char lastName[13]; /* 13 bytes */
int studentId; /* 4 bytes */
short grade; /* 2 bytes */
};
int main()
{
    printf("[----- [문서영] [2022042011] -----]\n");
struct student pst;
printf("size of student = %ld\n", sizeof(struct student));/*struct내의 데이터들의 메모리 합은 19이지만, 
구조내의 빈공간을 채워넣기(padding)하므로 
짝수바이트거나 4,8,16등의 배수가 되는 메모리의 경계에 의해 24가 출력된다.*/
printf("size of int = %ld\n", sizeof(int));/*sizeof(int)=4*/
printf("size of short = %ld\n", sizeof(short));/*sizeof(short)=4*/
return 0;
}
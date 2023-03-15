#include <stdio.h>
int main()
{
printf("[----- [문서영] [2022042011] -----]\n");
char charType;/*자료형 char의 변수명은 charType*/
int integerType;/*자료형 int의 변수명은 integerType*/
float floatType;/*자료형 float의 변수명은 floatType*/
double doubleType;/*자료형 double의 변수명은 doubleType*/
/*sizeof: 프로그래머가 만든 소스코드에서 메모리 공간을 실제 몇 byte를 잡아먹고 있는지 확인하기 위한 함수*/
printf("Size of char: %ld byte\n",sizeof(charType));/*자료형 char의 변수 charType이 차지하는 byte출력 (1)*/
printf("Size of int: %ld bytes\n",sizeof(integerType));/*자료형 int의 변수 integerType이 차지하는 byte출력 (4)*/
printf("Size of float: %ld bytes\n",sizeof(floatType));/*자료형 float의 변수 floatType이 차지하는 byte출력 (4)*/
printf("Size of double: %ld bytes\n",sizeof(doubleType));/*자료형 double의 변수 doubleType이 차지하는 byte출력 (8)*/
printf("-----------------------------------------\n");
printf("Size of char: %ld byte\n",sizeof(char));/*자료형 char이 차지하는 byte출력 (1)*/
printf("Size of int: %ld bytes\n",sizeof(int));/*자료형 int이 차지하는 byte출력 (4)*/
printf("Size of float: %ld bytes\n",sizeof(float));/*자료형 float이 차지하는 byte출력 (4)*/
printf("Size of double: %ld bytes\n",sizeof(double));/*자료형 double이 차지하는 byte출력 (8)*/
printf("-----------------------------------------\n");
printf("Size of char*: %ld byte\n",sizeof(char*));/*char형 변수를 포인팅하는 함수포인터의 byte출력(4)*/
printf("Size of int*: %ld bytes\n",sizeof(int*));/*int형 변수를 포인팅하는 함수포인터의 byte출력(4)*/
printf("Size of float*: %ld bytes\n",sizeof(float*));/*float형 변수를 포인팅하는 함수포인터의 byte출력(4)*/
printf("Size of double*: %ld bytes\n",sizeof(double*));/*double형 변수를 포인팅하는 함수포인터의 byte출력(4)*/
return 0;
}
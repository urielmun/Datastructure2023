#include <stdio.h>
int main()
{

printf("[----- [문서영] [2022042011] -----]\n");

int i; /*자료형 int의 변수 i 선언*/
int *ptr; /*4바이트의 int형 변수의 주소를 저장할 포인터 선언*/
int **dptr;/*int형 포인터를 가리키고 있는 포인터의 선언(이중포인터)*/
i = 1234;
printf("[checking values before ptr = &i] \n");
printf("value of i == %d\n", i); /*int 형 변수 i가 갖는 값(1234)*/
printf("address of i == %p\n", &i);/*int 형 변수 i가 갖는 주소값(0061FF1C)*/
printf("value of ptr == %p\n", ptr);/*ptr을 주소로 가지는 값 출력(003A6000)*/
printf("address of ptr == %p\n", &ptr);/*포인터 ptr이 저장된 주소값 출력(0061FF18)*/
ptr = &i; /* ptr is now holding the address of i */
printf("\n[checking values after ptr = &i] \n");
printf("value of i == %d\n", i);/*int 형 변수 i가 갖는 값(1234)*/
printf("address of i == %p\n", &i);/*int 형 변수 i가 갖는 주소값(0061FF1C)*/
printf("value of ptr == %p\n", ptr);/*ptr을 주소로 가지는 값 출력(&i=0061FF1C)*/
printf("address of ptr == %p\n", &ptr);/*포인터 ptr이 저장된 주소값 출력(0061FF18)*/
printf("value of *ptr == %d\n", *ptr);/*포인터 ptr을 주소로 가지는 값 출력(i=1234)*/
dptr = &ptr; /* dptr is now holding the address of ptr */
printf("\n[checking values after dptr = &ptr] \n");
printf("value of i == %d\n", i);/*int 형 변수 i가 갖는 값(1234)*/
printf("address of i == %p\n", &i);/*int 형 변수 i가 갖는 주소값(0061FF1C)*/
printf("value of ptr == %p\n", ptr);/*ptr을 주소로 가지는 값 출력(&i=0061FF1C)*/
printf("address of ptr == %p\n", &ptr);/*포인터 ptr이 저장된 주소값 출력(0061FF18)*/
printf("value of *ptr == %d\n", *ptr);/*포인터 ptr을 주소로 가지는 값 출력(i=1234)*/
printf("value of dptr == %p\n", dptr);/*이중포인터 dptr에 저장된 값 출력(0061FF18)*/
printf("address of dptr == %p\n", &dptr);/*이중포인터 dptr이 저장된 주소값 출력(0061FF14)*/
printf("value of *dptr == %p\n", *dptr);/*이중포인터 dptr을 주소로 가지는 값 출력(1차 참조값=ptr=&i=0061FF1C)*/
printf("value of **dptr == %d\n", **dptr);/*이중포인터 dptr을 주소로 가지는 값 출력(2차 참조값=*ptr=i=1234)*/
*ptr = 7777; /* changing the value of *ptr */
printf("\n[after *ptr = 7777] \n");
printf("value of i == %d\n", i);/* *ptr=7777=i 변수 i에 새롭게 저장된 값 출력(7777)*/
printf("value of *ptr == %d\n", *ptr);/*ptr을 주소로 가지는 값 출력(7777)*/
printf("value of **dptr == %d\n", **dptr);/*dptr을 이차 참조하는 값 출력(7777)*/
**dptr = 8888; /* changing the value of **dptr */
printf("\n[after **dptr = 8888] \n");
printf("value of i == %d\n", i);/* **dptr=*ptr=8888=i 변수 i에 새롭게 저장된 값 출력(7777)*/
printf("value of *ptr == %d\n", *ptr);/*ptr을 주소로 가지는 값 출력(8888)*/
printf("value of **dptr == %d\n", **dptr);/*dptr을 이차 참조하는 값 출력(8888)*/
return 0;
}
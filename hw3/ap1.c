#include <stdio.h>
#include <stdlib.h>
void main()
{
	printf("[----- [문서영] [2022042011] -----]\n");
	int list[5];/*5개 정수를 저장하는 리스트*/
	int* plist[5] = { NULL, };
	/*정수에 대한 5개 포인터*/
	/*NULL포인터는 어떤 객체나 함수도 가리키지 않는다.*/
	plist[0] = (int*)malloc(sizeof(int)); 
	/*동적메모리를 할당하는 malloc을 통하여 정수형 int 의 공간을 4bytes만큼의 양의 공간으로 할당한다. */
	/*heap으로 할당받는다.*/
	list[0] = 1;
	list[1] = 100;
	*plist[0] = 200;
	printf("list[0] = %d\n", list[0]);/*list[0]에 저장된 값을 출력한다.*/
	printf("&list[0] = %p\n", &list[0]);/*list[0]의 기본주소를 출력한다.*/
	printf("list = %p\n", list);/*list[0]의 포인터를 출력한다.*/
	printf("&list = %p\n", &list);/*list[0]의 포인터를 출력한다.*/
	printf("----------------------------------------\n\n");
	printf("list[1] = %d\n", list[1]);/*list[1]에 저장된 값을 출력한다.*/
	printf("&list[1] = %p\n", &list[1]);/*list[1]을 가리키는 포인터를 출력한다.*/
	printf("*(list+1) = %d\n", *(list + 1));/*list[1]에 저장된 값을 출력한다.*/
	printf("list+1 = %p\n", list + 1);/*list[1]을 가리키는 포인터를 출력한다.*/
	printf("----------------------------------------\n\n");
	printf("*plist[0] = %d\n", *plist[0]);/*plist[0]에 저장된 값이 가리키는 값을 출력한다.*/
	printf("&plist[0] = %p\n", &plist[0]);/*plist[0]을 가리키는 포인터를 출력한다.*/
	printf("&plist = %p\n", &plist);/*plist[0]을 가리키는 포인터를 출력한다.*/
	printf("plist = %p\n", plist);/*plist[0]을 가리키는 포인터를 출력한다.*/
	printf("plist[0] = %p\n", plist[0]);/*plist[0]을 가리키는 포인터를 출력한다.*/
	printf("plist[1] = %p\n", plist[1]);/*plist[0]이후의 원소는 NULL포인터이므로 어떤 객체나 함수도 가리키지 않는다.*/
	printf("plist[2] = %p\n", plist[2]);
	printf("plist[3] = %p\n", plist[3]);
	printf("plist[4] = %p\n", plist[4]);
	free(plist[0]);
}
#include <stdio.h>
#include <stdlib.h>
void main()
{
    printf("[----- [문서영] [2022042011] -----]\n");
	int list[5];/*5개 정수를 저장하는 리스트*/
	int* plist[5];/*정수에 대한 5개 포인터*/
	list[0] = 10;
	list[1] = 11;
	plist[0] = (int*)malloc(sizeof(int));
	/*동적메모리를 할당하는 malloc을 통하여 정수형 int 의 공간을 4bytes만큼의 양의 공간으로 할당한다. */
	/*heap으로 할당받는다.*/
	printf("list[0] \t= %d\n", list[0]);/*list[0]에 저장된 값인 10이 출력된다.*/
	printf("list \t\t= %p\n", list);/*list[0]를 가리키는 포인터가 출력된다.*/
	printf("&list[0] \t= %p\n", &list[0]);/*list[0]를 가리키는 포인터가 출력된다.*/
	printf("list + 0 \t= %p\n", list + 0);/*list[0]를 가리키는 포인터가 출력된다.*/
	printf("list + 1 \t= %p\n", list + 1);/*list[1]를 가리키는 포인터가 출력된다.*/
	printf("list + 2 \t= %p\n", list + 2);/*list[2]를 가리키는 포인터가 출력된다.*/
	printf("list + 3 \t= %p\n", list + 3);/*list[3]를 가리키는 포인터가 출력된다.*/
	printf("list + 4 \t= %p\n", list + 4);/*list[4]를 가리키는 포인터가 출력된다.*/
	printf("&list[4] \t= %p\n", &list[4]);/*list[4]를 가리키는 포인터가 출력된다.*/
	free(plist[0]);
}
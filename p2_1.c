#include <stdio.h>
#define MAX_SIZE 100
float sum1(float list[], int);
float sum2(float *list, int);
float sum3(int n, float *list);
float input[MAX_SIZE], answer;
int i;
void main(void)
{
    printf("[----- [문서영] [2022042011] -----]\n");
    for(i=0; i < MAX_SIZE; i++)
    input[i] = i;
/* for checking call by reference */
printf("--------------------------------------\n");
printf(" sum1(input, MAX_SIZE) \n");
printf("--------------------------------------\n");

printf("input \t= %p\n", input);/*input(=&input[0])*/
answer = sum1(input, MAX_SIZE);/*input의 주소가 sum1함수의 list에 복사된다.*/
printf("The sum is: %f\n\n", answer);/*배열의 모든 요소를 더하여 합을 반환한다.*/

printf("--------------------------------------\n");
printf(" sum2(input, MAX_SIZE) \n");
printf("--------------------------------------\n");

printf("input \t= %p\n", input);/*input(=&input[0])*/
answer = sum2(input, MAX_SIZE);/*input의 주소가 sum2함수의 list에 복사된다.*/
printf("The sum is: %f\n\n", answer);/*배열의 모든 요소를 더하여 합을 반환한다.*/

printf("--------------------------------------\n");
printf(" sum3(MAX_SIZE, input) \n");
printf("--------------------------------------\n");

printf("input \t= %p\n", input);
answer = sum3(MAX_SIZE, input);
printf("The sum is: %f\n\n", answer);
/*코드의 마지막에는 함수의 스택 변수를 재사용하는 것을 테스트하는 코드가 포함되어 있습니다. 
sum3() 함수에서 사용된 tempsum 변수가 다시 사용되어 
main() 함수에서 출력되는 answer 변수의 값이 변경되는 것을 확인할 수 있습니다.*/
}

/*sum1은 배열의 첫 번째 요소를 가리키는 포인터 list를 배열 자체로 전달받는다.
 그리고 포인터 list를 이용하여 배열의 모든 요소를 더한다.*/
float sum1(float list[], int n) {
printf("list\t= %p\n", list);
printf("&list\t= %p\n\n", &list);
int i;
float tempsum = 0;
for(i = 0;i < n;i++)
tempsum += list[i];
return tempsum;
}
/*sum2는 함수는 배열의 첫 번째 요소를 가리키는 포인터 list를 이용하여 배열의 모든 요소를 더한다.*/
float sum2(float *list, int n) {
printf("list\t= %p\n", list);
printf("&list\t= %p\n\n", &list);
int i;
float tempsum = 0;
for(i = 0;i < n;i++)
tempsum += *(list +i);
return tempsum;
}

/* stack variable reuse test */
/*sum3는  함수는 배열의 첫 번째 요소를 가리키는 포인터 list와 배열의 길이 n을 전달받는다. 
이 함수에서는 포인터 list를 이용하여 배열의 모든 요소를 더합니다.*/
float sum3(int n, float *list) {
printf("list\t= %p\n", list);
printf("&list\t= %p\n\n", &list);
int i;
float tempsum = 0;
for(i = 0;i < n;i++)
tempsum += *(list +i);
return tempsum;
}

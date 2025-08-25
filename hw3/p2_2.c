#include <stdio.h>
void print_one(int *ptr, int rows);
int main()
{
    printf("[----- [문서영] [2022042011] -----]\n");
int one[] = {0, 1, 2, 3, 4};
printf("one = %p\n", one); /*one=&one=&one[0]*/
printf("&one = %p\n", &one);
printf("&one[0] = %p\n", &one[0]);
printf("\n");

printf("------------------------------------\n");
printf(" print_one(&one[0], 5) \n");
printf("------------------------------------\n");
print_one(&one[0], 5);
/*
Address    Content
&one[i]    i 
가 출력된다.(i는 0부터 4까지 대입)*/
printf("------------------------------------\n");
printf(" print_one(one, 5) \n");
printf("------------------------------------\n");
print_one(one, 5);/*=print_one(&one[0], 5);*/
/*
Address    Content
&one[i]    i 
가 출력된다.(i는 0부터 4까지 대입)*/
return 0;
}

void print_one(int *ptr, int rows)/* */
{/* print out a one-dimensional array using a pointer */
int i;
printf ("Address \t Contents\n");
for (i = 0; i < rows; i++)
printf("%p \t %5d\n", ptr + i, *(ptr + i));
printf("\n");
}
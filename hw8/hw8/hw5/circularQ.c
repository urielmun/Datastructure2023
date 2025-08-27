/**
 * circularQ.c
 *
 * School of Computer Science, 
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType *createQueue();
int freeQueue(QueueType *cQ);
int isEmpty(QueueType *cQ);
int isFull(QueueType *cQ);
void enQueue(QueueType *cQ, element item);
void deQueue(QueueType *cQ, element* item);
void printQ(QueueType *cQ);
void debugQ(QueueType *cQ);
element getElement();


int main(void)
{
    printf("[----- [문서영] [2022042011] -----]");
	QueueType *cQ = createQueue();
	element data;

	char command;

	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I': //Insert Q
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D'://Delete Q
			deQueue(cQ,&data);
			break;
		case 'p': case 'P'://Print Q상태 보여줌
			printQ(cQ);
			break;
		case 'b': case 'B'://Debug Q에서 rear의 포인터를 출력
			debugQ(cQ);
			break;
		case 'q': case 'Q'://Quit 프로그램 종료
			break;

		default://그 무엇도 아닐때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');


	return 1;
}

QueueType *createQueue() 
/* 입력값의 위치를 알리는 rear 와 출력될 위치를 알리는 front값을 각각 -1로 초기화해줌
rear와 front로 현재 Q의 상태를 알수 있음
큐 동적할당*/
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType *cQ)
/*원형 큐 동적할당 (단, 원형 큐가 NULL이라면 종료 (동적할당X))
*/
{
    if(cQ == NULL) return 1;
    free(cQ);
    return 1;
}

element getElement()
/*
*/
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


int isEmpty(QueueType *cQ)
/*
front = rear 일 경우 공백 상태
추후 isEmpty 사용할 때, 1이 반환되면 '공백 상태'임을 의미 (아닌 경우 0)
*/
{
	if (cQ->front == cQ->rear){
		printf("Circular Queue is empty!");
		return 1;
	}
	else return 0;
}

int isFull(QueueType *cQ)
/*(rear+1)%MAX 값과 front의 값이 같다면 큐가 가득 차 있음을 알 수 있음
 Circular Queue is full! 출력*/
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {
		printf(" Circular Queue is full!");
		return 1;
	}
	else return 0;
}

void enQueue(QueueType *cQ, element item)
/*rear쪽에서 요소 삽입
rear값이 MAX를 넘어가면 다시 배열의 첫번째 위치로 돌아가게 됨*/
{
	if(isFull(cQ)) return;
	else {
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;
		cQ->queue[cQ->rear] = item;
	}
}

void deQueue(QueueType *cQ, element *item)
/*front쪽에서 요소 삭제
*/
{
	if(isEmpty(cQ)) return;
	else {
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;
		*item = cQ->queue[cQ->front];
		return;
	}
}


void printQ(QueueType *cQ)
/*현재 Q 출력
1) 공백이면 출력할 게 없음
2) int first, last 변수를 선언하고 해당 변수로 큐 배열 접근
-while(first!=last) : first와 last가 같으면 전부 출력한 것임
-first를 한 칸씩 앞으로 옮겨줌 (first++; 안됨! 원형 큐라는 것을 인지)
*/
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while(i != last){
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ)

{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	//printQ(cQ);
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}


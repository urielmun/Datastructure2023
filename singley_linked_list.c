/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int key;
	struct Node* link;
} listNode;

typedef struct Head {
	struct Node* first;
}headNode;


/* �⑥닔 由ъ뒪�� */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
    printf("[----- [문서영] [2022042011] -----]");

	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);/*command 값을 입력받는다.*/

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {
/*
먼저, initialize 함수는 연결 리스트를 초기화하고 새로운 headNode 구조체를 반환하는 함수입니다. 
이 함수는 매개변수로 headNode 구조체 포인터 h를 받습니다.

함수는 입력된 h 포인터가 NULL이 아니라면, 
freeList 함수를 호출하여 h 포인터가 가리키는 연결 리스트의 메모리를 해제합니다. 
이는 연결 리스트의 중복 생성을 방지하기 위함입니다.

그 후, temp 포인터를 생성하여 새로운 headNode 구조체를 동적으로 할당합니다. 
temp 포인터가 가리키는 headNode 구조체의 first 멤버를 NULL로 초기화합니다. 
마지막으로 temp 포인터를 반환하여 새로운 headNode 구조체를 생성한 후에 이를 이용할 수 있도록 합니다.

따라서, initialize 함수는 연결 리스트를 초기화하고 새로운 headNode 구조체를 반환하는 유용한 함수입니다.
*/
	if(h != NULL)
		freeList(h);

	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
	/* 
동적으로 할당된 연결 리스트의 메모리를 해제 
먼저 리스트의 첫 번째 노드를 가리키는 포인터 p를 생성
이후 fgnyu에 while 루프를 이용하여 리스트를 처음부터 끝까지 순회하며,
현재 노드를 가리키는 포인터 p가 NULL이 될 때까지 반복한다
반복문 내에서는 현재 노드를 가리키는 포인터 prev를 생성한다.
prev 포인터는 p 포인터가 가리키는 노드를 가리킨다. 
이후에 p 포인터를 다음 노드로 이동시키고, prev 포인터가 가리키는 노드의 메모리를 해제한다. 
리스트 전체를 순회한 후에 headNode 구조체의 포인터를 이용하여 동적 할당된 메모리를 해제합니다.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}



int insertNode(headNode* h, int key) {
	/*연결 리스트에 새로운 노드를 삽입하는 함수
	매개변수로는 headNode 구조체 포인터와 삽입할 key값이 주어짐*/

	listNode* node = (listNode*)malloc(sizeof(listNode));
/*listNode 구조체 포인터를 동적 할당하여 새로운 노드를 생성한다.
* 이 노드의 key 값은 매개변수로 전달받은 key 값으로 설정하고, link 값은 NULL로 초기화한다*/
	node->key = key;
	node->link = NULL;
/* 만약 리스트가 비어있는 경우, headNode 구조체의 first 포인터를 새로운 노드의 포인터로 설정한다.*/
	if (h->first == NULL)
/*
	만약 현재 노드가 첫 번째 노드인 경우, headNode 구조체의 first 포인터를 새로운 노드의 포인터로 설정하고,
* 새로운 노드의 link 포인터를 현재 노드의 포인터로 설정합니다.
*/
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	
	while(n != NULL) {
/* 리스트를 순회하다가, 현재 노드의 key 값이 삽입할 key 값보다 작은 경우,
* 다음 노드로 이동. 이때 이전 노드를 가리키는 trail 포인터를 업데이트한다.*/
		if(n->key >= key) {
			
			if(n == h->first) {
				h->first = node;
				node->link = n;
			} else { 
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}
/* 리스트를 전체적으로 순회한 후에는 trail 포인터가 가리키는 노드 다음에 새로운 노드를 삽입
* 따라서 trail 노드의 link 포인터를 새로운 노드의 포인터로 설정.*/
	
	trail->link = node;
	return 0;
}
/*
 key 값을 가지는 노드를 연결 리스트의 맨 끝에 추가하는 함수
 
 새로운 listNode 구조체를 동적 할당하여 node 포인터가 가리키도록 한다.
 이후에는 node 포인터가 가리키는 listNode 구조체의 key 멤버에 입력된 key 값을 저장
 node 포인터가 가리키는 listNode 구조체의 link 멤버는 NULL로 초기화
 
 다음으로, 연결 리스트가 비어있는 경우에는 h 포인터가 가리키는 headNode 구조체의 
 first 멤버를 node 포인터로 설정한다.
 
 만약 연결 리스트에 노드가 있는 경우에는 마지막 노드를 찾아서 node 노드를 추가한다.
 이를 위해 먼저 n 포인터를 h 포인터가 가리키는 연결 리스트의 첫 번째 노드인 h->first로 설정한다.
 그리고 n 포인터가 가리키는 listNode 구조체의 link 멤버가 NULL이 아닐 때까지 n 포인터를 n->link로 이동시킨다.
 이후에, n 포인터가 가리키는 listNode 구조체의 link 멤버를 node 포인터로 설정하여 node 노드를 추가합니다.
 */

int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {
		n = n->link;
	}
	n->link = node;
	return 0;
}

/*
 입력된 key 값을 가지는 노드를 연결 리스트의 맨 앞에 추가하는 함수이다
 
  새로운 listNode 구조체를 동적 할당하고 node 포인터가 가리키도록 한다.
  node 포인터가 가리키는 listNode 구조체의 key 멤버에 입력된 key 값을 저장한다.
 
  다음으로, node 포인터가 가리키는 listNode 구조체의 link 멤버를 h 포인터가 가리키는 연결 리스트의 
  첫 번째 노드인 h->first로 설정하고,
  그리고 h 포인터가 가리키는 headNode 구조체의 first 멤버를 node 포인터로 설정하여 node 노드를 추가한다.
 
  */

int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	node->link = h->first;
	h->first = node;

	return 0;
}

/*
이 코드는 링크드 리스트에서 지정한 key 값을 가지는 노드를 찾아서 삭제하는 함수

먼저, 리스트가 비어있는 경우 "nothing to delete" 메시지를 출력하고 함수를 빠져나간다.
노드를 탐색할 때는 포인터 n과 그 이전 노드를 가리키는 포인터 trail을 사용한다. 
노드를 찾을 때까지 리스트를 순회하며, key 값을 가지는 노드를 찾으면 해당 노드를 삭제하고 함수를 빠져나간다.

삭제할 노드가 리스트의 첫 번째 노드인 경우, 
headNode 구조체의 first 멤버를 삭제할 노드의 다음 노드로 바꾼다.
삭제할 노드가 리스트의 첫 번째 노드가 아닌 경우, 이전 노드의 link를 삭제할 노드의 다음 노드로 바꾼다.
찾지 못한 경우 "cannot find the node for key = %d" 메시지를 출력한다.
*/
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	
	while(n != NULL) {
		if(n->key == key) {
			/* 泥� �몃뱶 �욎そ�� �쎌엯�댁빞�� 寃쎌슦 �몄� 寃��� */
			if(n == h->first) {
				h->first = n->link;
			} else { /* 以묎컙�� 寃쎌슦嫄곕굹 留덉�留됱씤 寃쎌슦 */
				trail->link = n->link;
			}
			free(n);
			return 0;
		}

		trail = n;
		n = n->link;
	}

	/* 李얠� 紐� �쒓꼍�� */
	printf("cannot find the node for key = %d\n", key);
	return 0;

}

/**
이 코드는 연결 리스트에서 마지막 노드를 삭제하는 함수이다.

우선, 첫 번째 노드가 NULL인 경우 "nothing to delete."를 출력하고 함수를 빠져나간다.
그렇지 않은 경우, 리스트를 처음부터 탐색하면서 현재 노드(n)의 다음 노드(link)가 NULL일 때까지 계속 진행
이때, 현재 노드(n)와 그 이전 노드(trail)를 모두 저장하고 다음 노드로 이동한다.

리스트 탐색이 끝나면, 마지막 노드(n)를 삭제한다.
이때, 리스트의 길이가 1인 경우 (즉, 첫 번째 노드가 마지막 노드인 경우), 첫 번째 노드를 NULL로 설정합니다. 
그렇지 않은 경우, 이전 노드(trail)의 링크를 NULL로 설정하여 마지막 노드를 삭제
 */
int deleteLast(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* �몃뱶媛� �섎굹留� �덈뒗 寃쎌슦, 利� first node == last node��  寃쎌슦 泥섎━ */
	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 留덉�留� �몃뱶源뚯� �대룞 */
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	/* n�� ��젣�섎�濡�, �댁쟾 �몃뱶�� 留곹겕 NULL 泥섎━ */
	trail->link = NULL;
	free(n);

	return 0;
}
/**
이 코드는 연결 리스트에서 첫 번째 노드를 삭제하는 함수이다.

headNode 포인터 h가 NULL인지 확인하고, NULL이 아닌 경우에는 리스트가 비어있는지 확인
만약 리스트가 비어있다면 "nothing to delete"라는 메시지를 출력하고 함수를 종료

리스트가 비어있지 않다면, 
리스트의 첫 번째 노드를 가리키는 포인터 n을 headNode 구조체의 first 멤버에서 가져온다.
 headNode 구조체의 first 멤버를 n의 다음 노드를 가리키도록 변경한다. 
이렇게 되면 첫 번째 노드가 삭제됩니다. 마지막으로, n이 가리키는 첫 번째 노드를 메모리에서 해제
 */
int deleteFirst(headNode* h) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;

	h->first = n->link;
	free(n);

	return 0;
}


/**
 이 함수는 링크드 리스트를 역순으로 바꾼다.

먼저, 링크드 리스트가 비어있는 경우 "nothing to invert..." 메시지를 출력하고 함수를 종료

링크드 리스트를 역순으로 바꾸기 위해, 현재 노드를 가리키는 포인터 변수 `n`, 
이전 노드를 가리키는 포인터 변수 `trail`, 
그리고 현재 노드와 이전 노드 사이의 노드를 가리키는 포인터 변수 `middle`을 초기화한다.

그리고 현재 노드를 처음부터 끝까지 한 칸씩 이동하면서, 
`middle`이 가리키는 노드를 `trail`이 가리키도록 하고, `n`이 가리키는 노드를 `middle`이 가리키도록 한다.
그리고 `n`을 다음 노드로 이동시키고, `middle`의 링크를 `trail`이 가리키는 노드로 바꿔준다.
이 과정을 리스트의 끝까지 반복한다. 

최종적으로 `h->first`가 가리키는 노드를 `middle`이 가리키는 노드로 바꿔줌으로써, 
리스트의 링크드리스트가 역순으로 바뀐 것을 확인할 수 있다.
 */
int invertList(headNode* h) {


	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;

	return 0;
}

/*
이 함수는 연결리스트에 있는 모든 노드들을 출력

함수는 연결리스트를 처음부터 끝까지 탐색하면서 각 노드의 key 값을 출력한다.
노드의 key 값: 정수형

그리고 마지막으로 출력된 노드의 번호와 전체 노드의 개수를 출력합니다.
*/

void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}

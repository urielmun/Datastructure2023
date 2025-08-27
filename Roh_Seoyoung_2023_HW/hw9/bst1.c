#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);  // 이진 탐색 트리를 초기화하는 함수
void inorderTraversal(Node* ptr);	  // 재귀적인 중위 순회를 수행하는 함수
void preorderTraversal(Node* ptr);    // 재귀적인 전위 순회를 수행하는 함수
void postorderTraversal(Node* ptr);	  // 재귀적인 후위 순회를 수행하는 함수
int insert(Node* head, int key);  // 트리에 새로운 노드를 삽입하는 함수
int deleteLeafNode(Node* head, int key);  // 트리에서 주어진 키 값을 가진 리프 노드를 삭제하는 함수
Node* searchRecursive(Node* ptr, int key);  // 주어진 키 값을 가진 노드를 재귀적으로 탐색하는 함수
Node* searchIterative(Node* head, int key);  // 주어진 키 값을 가진 노드를 반복적으로 탐색하는 함수
int freeBST(Node* head);  // 트리에 할당된 모든 메모리를 해제하는 함수



int main()
{
    printf("[----- [문서영] [2022042011] -----]");
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {//

//트리가 비어있지 않으면 모든 노드를 해제한다.
	if(*h != NULL)
		freeBST(*h);

//헤드 노드 설정
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	//왼쪽 노드는 0을 가리킴
	(*h)->right = *h;  //오른쪽 노드로 자기자신 가리킴
	(*h)->key = -9999; //키 값은 -9999으로 초기화
	return 1;
}



void inorderTraversal(Node* ptr)
{ //중위 순회(inorder traversal)를 수행하여 트리의 노드를 키 값의 오름차순으로 출력합니다.
//left->root->right
	if(ptr) {
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
{//전위 순회(preorder traversal)를 수행하여 트리의 노드를 출력합니다. 
//root->left->right
	if(ptr) {
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr)
{//후위 순회(postorder traversal)를 수행하여 트리의 노드를 출력합니다
//left->right->root
	if(ptr) {
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{//노드를 추가한다.
	
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;//새로운 노드의 키값 설정
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {//헤드노드의 왼쪽노드가 빌 경우
		head->left = newNode;//헤드의 왼쪽이 새로운 노드를 가리키게 설정한다.
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {//헤드의 왼쪽이 안비어있을때까지

		if(ptr->key == key) return 1;//헤드의 왼쪽 노드의 키값이 이미 설정하려는 값과 같을때 리턴

		parentNode = ptr;//parentNode=head->left

		if(ptr->key < key)//헤드 왼쪽의 키값이 설정하려는 키값보다 작을시 
			ptr = ptr->right;//헤드왼쪽이 헤드왼쪽 노드의 오른쪽에 자기 자신을 가리키게 한다.
		else
			ptr = ptr->left;
	}

	
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)
{//맨끝 노드를 삭제해라 
	if (head == NULL) {//헤드가 0이라면 삭제할 노드가 없다.
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {//헤드 노드밖에 없는 이진 트리
		printf("\n Nothing to delete!!\n");
		return -1;
	}
//ptr이 헤드의 left를 가리키게 한다. 
	Node* ptr = head->left;
//부모 노드를 저장해둔다
	Node* parentNode = head;

	while(ptr != NULL) {
//ptr이 0을 가리킬 때까지
		if(ptr->key == key) {
			if(ptr->left == NULL && ptr->right == NULL) {//key를 가진 노드가 마지막 노드임
				/* root node case */
				if(parentNode == head)//헤드 노드가 부모노드일때 헤드의 왼쪽이 0을 가리키게 한다.
					head->left = NULL;

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL;
				else
					parentNode->right = NULL;

				free(ptr);
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
				//key값을 가진 노드가 마지막 노드가 아닐때 오류
			}
			return 1;
		}

		parentNode = ptr;
		
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	// 노드가 비어있거나 탐색한 경로에 해당 키를 가진 노드가 없는 경우
	if(ptr == NULL)
		return NULL;

	if(ptr->key < key)// 현재 노드의 키가 찾고자 하는 키보다 작을 경우
        // 오른쪽 서브트리에서 재귀적으로 탐색
		ptr = searchRecursive(ptr->right, key);
	else if(ptr->key > key)// 현재 노드의 키가 찾고자 하는 키보다 클 경우
        // 왼쪽 서브트리에서 재귀적으로 탐색
		ptr = searchRecursive(ptr->left, key);

	/* if ptr->key == key */
	return ptr;

}
Node* searchIterative(Node* head, int key)
{//head부터 쭉 내려오면서 key 값을 찾아보자
	/* root node */
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		if(ptr->key == key)
			return ptr;

		if(ptr->key < key) ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr)//노드 동적 할당 해제
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if(head->left == head)//head 하나만 트리에 속한 노드이다.
	{
		free(head);
		return 1;
	}

	Node* p = head->left;//p는 head->left를 가리키게 한다.

	freeNode(p);//p를 동적 할당 해제한다.

	free(head);//head도 해제한다.
	return 1;
}





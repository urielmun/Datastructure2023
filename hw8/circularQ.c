
#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
    printf("[----- [문서영] [2022042011] -----]");
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
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


int initialize(listNode** h) {

	/* headNode媛� NULL�� �꾨땲硫�, freeNode瑜� �몄텧�섏뿬 �좊떦�� 硫붾え由� 紐⑤몢 �댁젣 */
	if(*h != NULL)
		freeList(*h);

	/* headNode�� ���� 硫붾え由щ� �좊떦�섏뿬 由ы꽩 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){
    if(h!=NULL){
    free(h);}
    else {
        printf("It's already NULL");
    }
	return 0;
}

void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}

int insertLast(listNode* h, int key) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->key = key;

    newNode->llink = h->llink;
    newNode->rlink = h;
    h->llink->rlink = newNode;
    h->llink = newNode;

    return 1;
}

int deleteLast(listNode* h) {
    if (h->rlink == h) {
        printf("List is empty. Cannot delete from an empty list.\n");
        return 0;
    }

    listNode* lastNode = h->llink;
    lastNode->llink->rlink = h;
    h->llink = lastNode->llink;
    free(lastNode);

    return 1;
}

int insertFirst(listNode* h, int key) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->key = key;

    newNode->llink = h;
    newNode->rlink = h->rlink;
    h->rlink->llink = newNode;
    h->rlink = newNode;

    return 1;
}

int deleteFirst(listNode* h) {
    if (h->rlink == h) {
        printf("List is empty. Cannot delete from an empty list.\n");
        return 0;
    }

    listNode* firstNode = h->rlink;
    firstNode->rlink->llink = h;
    h->rlink = firstNode->rlink;
    free(firstNode);

    return 1;
}

int invertList(listNode* h) {
    if (h->rlink == h) {
        printf("List is empty. Cannot invert an empty list.\n");
        return 0;
    }

    listNode* current = h;
    listNode* temp = NULL;

    do {
        temp = current->rlink;
        current->rlink = current->llink;
        current->llink = temp;
        current = current->llink;
    } while (current != h);

    return 1;
}

int insertNode(listNode* h, int key) {
    listNode* newNode = (listNode*)malloc(sizeof(listNode));
    newNode->key = key;

    listNode* p = h->rlink;

    while (p != h) {
        if (p->key > key) {
            newNode->llink = p->llink;
            newNode->rlink = p;
            p->llink->rlink = newNode;
            p->llink = newNode;
            return 1;
        }
        p = p->rlink;
    }

    newNode->llink = h->llink;
    newNode->rlink = h;
    h->llink->rlink = newNode;
    h->llink = newNode;

    return 1;
}

int deleteNode(listNode* h, int key) {
    if (h->rlink == h) {
        printf("List is empty. Cannot delete from an empty list.\n");
        return 0;
    }

    listNode* p = h->rlink;

    while (p != h) {
        if (p->key == key) {
            p->llink->rlink = p->rlink;
            p->rlink->llink = p->llink;
            free(p);
            return 1;
        }
        p = p->rlink;
    }

    printf("Key %d not found in the list.\n", key);
    return 0;
}







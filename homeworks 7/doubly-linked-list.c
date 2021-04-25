/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
 /* �ʿ��� ������� �߰� if necessary */


typedef struct Node {
	int key;					//������	
	struct Node* llink;			//��ũ(���� ��� )
	struct Node* rlink;			//��ũ(���� ���)
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* �Լ� ����Ʈ */

/* note: initialize�� ���������͸� �Ű������� ����
		 singly-linked-list�� initialize�� �������� ���� �Ұ� */
int initialize(headNode** h);

/* note: freeList�� �̱������͸� �Ű������� ����
		- initialize�� �� �ٸ��� ���� �Ұ�
		- ���������͸� �Ű������� �޾Ƶ� ������ �� ���� �� */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command;
	int key;
	headNode* headnode = NULL;

	do {
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");
		printf("----------------[ �� �� �� ]-----------[ 2018038014 ]-----------\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
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

	} while (command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {
	/* headNode�� NULL�� �ƴϸ�, freeNode�� ȣ���Ͽ� �Ҵ�� �޸� ��� ���� */
	if ((*h) != NULL)
		freeList(*h);

	/* headNode�� ���� �޸𸮸� �Ҵ��Ͽ� ���� */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h) {
	listNode *p = h->first;
	listNode *prev = NULL;
	while (p != NULL) {					//p�� NULL�� �ƴϸ�
		prev = p;						// p�� �����ϱ� ���� prev�� ���
		p = p->llink;					// p�� ���� ���� �̵�
		free(prev);						// ���� ��� ���� 
	}
	free(h);							// ��� ���� 
	return 0;

	

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if (h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while (p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {
	listNode* newNode = (listNode*)malloc(sizeof(listNode));		//������ ��带 �����Ҵ��Ѵ�.
	listNode* lastNode;												//����Ʈ�� ��尡 �����ϴ� ��� ��������� ������ ��´�.
	newNode->key = key;												//�Է¹��� Ű���� ���ο� ��忡 ����										
	
	if (h->first == NULL)		// ���� ����Ʈ�� �����϶�
	{
		h->first = newNode;		// first�� newNode�� ����
		newNode->rlink = NULL;	// newNode.link�� NULL������ �ʱ�ȭ
		return 0;
	}
	lastNode = h->first;				//��� ����
	while (lastNode->rlink != NULL)		// lastNode�� �� ���� ���������� �̵�
		lastNode = lastNode->rlink;
	
	newNode->llink = lastNode;			// �ΰ��� ã������ newNode.llink�� lastNode�� ����Ų��.
	lastNode->rlink = newNode;			// 	lastNode.rlink�� newNode�� ����Ų��.
	newNode->rlink = NULL;				// newNode.rlink ���� NULL �ʱ�ȭ
	return 0;
}



/**
 * list�� ������ ��� ����
 */
int deleteLast(headNode* h) {
	listNode* removenode;			// ������ ��带 ���� ������
	listNode* prenode;				// �����ϱ��� ����� ������ �����ϴ� ������
	
	if (h->first == NULL)
		return 0;						// ���� ����Ʈ�� ���, ���� �ߴ�
	if (h->first->rlink == NULL)		// ����Ʈ�� ��尡 �Ѱ��� ���
	{
		free(h->first);				// ù��° ��� �޸� ����
		h->first = NULL;			// ����Ʈ ���� �����͸� null�� �����Ѵ�.
		return 0;
	}
	else                           // ����Ʈ�� ��尡 ������ �ִ� ���
	{
		prenode = h->first;					//���� ��尡 first�� ����Ų��.
		removenode = h->first->rlink;		//���� ��尡 first�� link�� ����Ų��.
		while (removenode->rlink != NULL)		// ����Ű�� ��ũ�� NULL���̸�
		{
			prenode = removenode;				// removenode�� �ּҸ� prenode�� ����
			removenode = removenode->rlink;		// ���� ����Ʈ�� ã�´�.
		}
		free(removenode);
		prenode->rlink = NULL;				//pre�� ����Ű�� �ִ� ��ũ�� NULL�θ����.

	
	}



	return 0;
}



/**
 * list ó���� key�� ���� ����ϳ��� �߰�
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;													//���ο� ��带 �ʱ�ȭ�Ѵ�.
	node->rlink = NULL;
	node->llink = NULL;
	if(h->first == NULL)												// ����� �������
	{
		h->first = node;
	}
	else																// �׿��� ��쿡��
	{
		node->rlink = h->first;
		h->first->llink = node;
		h->first = node;
	}
	

	return 0;
}

/**
 * list�� ù��° ��� ����
 */
int deleteFirst(headNode* h) {
	listNode* removenode = (listNode*)malloc(sizeof(listNode)); // ù ��° ��带 ���� ������ ��带 �����Ҵ� �޴´�.
	removenode = h->first;										// removernode�� h.first�� �ּҰ��� ���´�.
	h->first = removenode->rlink;								// h.first�� removernode.link�� �ű��.
	free(removenode);											// �޸� ����
	return 0;

}



/**
 * ����Ʈ�� ��ũ�� �������� �� ��ġ
 */
int invertList(headNode* h) {
	listNode* p;			//	ó�� �ּҸ� �����ϴ� ���
	listNode* q;			//	�������� �������ֱ� ���� q,r����
	listNode* r;			
	p = h->first;			// ������ p�� ù ��° ��忡 ����
	q = NULL;				// �ʱ�ȭ

	while (p != NULL) {		// ����Ʈ��ù ��° ������ ��ũ�� ���� ���� ���� �̵��ϸ鼭 ��尣 ������ �ٲ۴�.
		r = q;				// �ʱ�ȭ
		q = p;				// q�� p����� ������ ����
		p = p->rlink;		// ���� ��带 ã�´�.
		q->rlink = r;		// r�� ���� ���� �����Ѵ�.
	}
	h->first = q;			// ó�� �ּҸ� q�� ����

	return 0;
}



/* ����Ʈ�� �˻��Ͽ�, �Է¹��� key���� ū���� ������ ��� �ٷ� �տ� ���� */

int insertNode(headNode* h, int key) {
   listNode* newnode = (listNode*)malloc(sizeof(listNode));		// ��带 �Է¹��� ��� 
   listNode* findnode = (listNode*)malloc(sizeof(listNode));	// 

   newnode->key = key;
   newnode->rlink = NULL;
   newnode->llink = NULL;

   if (h->first == NULL)                                          // ��� ��尡 ���������
   {
      h->first = newnode;
   }
   else if (h->first->key >= newnode->key)                              // �Է� �� ���� ù��° ��� ������ ������ 
   {
      newnode->rlink = h->first;
      h->first->llink = newnode;
      h->first = newnode;

   }
   else {
      findnode = h->first; // findnode�� �ּҰ��� frist�� ����Ų��.

      while (findnode!= NULL)   						// ã�� ��尡 �ΰ��� ������ �������� Ž��
      {
         if (newnode->key <= findnode->key)				// �Էµ� ���� ã�� ������ �۰ų� ������ 
         {
            newnode->rlink = findnode;
            newnode->llink = findnode->llink;
            findnode->llink->rlink = newnode;
            findnode->llink = newnode;
            return 0;
         }

         if (findnode->rlink == NULL)					// ���� ���� ��尡 �ΰ��̸� ����
            break;

         findnode = findnode->rlink;                  	// ���� ����Ʈ�� �Ѿ��.
      }

      if (findnode->rlink == NULL && findnode->key < key)		// ���� �Էµ� ���� �������� �Էµ� ���
      {
         findnode->rlink = newnode;
         newnode->llink = findnode;
         newnode->rlink = NULL;
      }
   }
   return 0;
}

/**
 * list���� key�� ���� ��� ����
 */
int deleteNode(headNode* h, int key) {
	listNode* prenode;																// ���� �ּҸ� ������ ���
	listNode* findnode;																// ó�� �ּҰ��� ������ ���
	listNode* removenode = (listNode*)malloc(sizeof(listNode));						// ã�� ��� ���� ������ ��带 �����Ҵ� 
	if (h->first == NULL)															// ����� NULL���̸� 0���� ��ȯ
	{
		printf("�� ����Ʈ�Դϴ�.\n");
		return 0;
	}
	else
	{
	
		if (h->first->key == key) 													// key���� ù ��� �� ���
		{
		
			removenode = h->first;														// ��尡 ��带 ����Ų��.
			h->first = removenode->rlink;												// ��尡 removenode.rlink�� ����Ű�� ��带 ����Ų��.
			h->first->llink =NULL;														
		 	free(removenode);															// �޸� �Ҵ� ����
		 	return 0;
	 	}
		else {
			prenode = h->first;
			findnode = h->first->rlink;
			while (findnode->rlink != NULL)										// remove ->link �� ���� �ƴҶ�����, ����ڰ� ã�� �� ���� Ž��
			{
				prenode = findnode;												// removenode�� �ּҸ� prenode�� ����
				findnode = findnode->rlink;										// ���� ����Ʈ�� ã�´�.
				
				if(findnode->key == key)										// key���� ���� ��带 ã������ while�� ����
					break;
				
				
			}
			
			if(findnode->rlink == NULL)													// ������ ��带 ���ﶧ 
			{
				removenode = findnode;
				prenode = findnode->llink;
				prenode->rlink= NULL;
				free(removenode);
				
			}

			else																					// �׿��� ���
			{
				removenode = findnode;
				prenode->rlink = findnode->rlink;
				findnode->rlink->llink  = findnode->llink;											// �����ϰ� �߰� ���� �����ϰ�  ��带 �̾��ش�.
				free(removenode);
			}
		}
	}
	return 1;
}
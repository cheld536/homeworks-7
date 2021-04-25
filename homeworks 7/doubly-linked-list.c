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
 /* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;					//데이터	
	struct Node* llink;			//링크(다음 노드 )
	struct Node* rlink;			//링크(이전 노드)
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
		 singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
		- initialize와 왜 다른지 이해 할것
		- 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
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
		printf("----------------[ 김 윤 희 ]-----------[ 2018038014 ]-----------\n");
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
	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if ((*h) != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h) {
	listNode *p = h->first;
	listNode *prev = NULL;
	while (p != NULL) {					//p가 NULL이 아니면
		prev = p;						// p를 변경하기 전에 prev에 기억
		p = p->llink;					// p를 다음 노드로 이동
		free(prev);						// 이전 노드 해제 
	}
	free(h);							// 헤더 해제 
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
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	listNode* newNode = (listNode*)malloc(sizeof(listNode));		//삽입할 노드를 동적할당한다.
	listNode* lastNode;												//리스트에 노드가 존재하는 경우 마지막노드 정보를 담는다.
	newNode->key = key;												//입력받은 키값을 새로운 노드에 저장										
	
	if (h->first == NULL)		// 현재 리스트가 공백일때
	{
		h->first = newNode;		// first를 newNode로 저장
		newNode->rlink = NULL;	// newNode.link를 NULL값으로 초기화
		return 0;
	}
	lastNode = h->first;				//헤드 부터
	while (lastNode->rlink != NULL)		// lastNode가 널 값을 만날때까지 이동
		lastNode = lastNode->rlink;
	
	newNode->llink = lastNode;			// 널값을 찾았으면 newNode.llink로 lastNode를 가르킨다.
	lastNode->rlink = newNode;			// 	lastNode.rlink로 newNode를 가르킨다.
	newNode->rlink = NULL;				// newNode.rlink 값을 NULL 초기화
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	listNode* removenode;			// 삭제할 노드를 담을 포인터
	listNode* prenode;				// 삭제하기전 노드의 정보를 저장하는 포인터
	
	if (h->first == NULL)
		return 0;						// 공백 리스트인 경우, 삭제 중단
	if (h->first->rlink == NULL)		// 리스트에 노드가 한개인 경우
	{
		free(h->first);				// 첫번째 노드 메모리 해제
		h->first = NULL;			// 리스트 시작 포인터를 null로 설정한다.
		return 0;
	}
	else                           // 리스트에 노드가 여려개 있는 경우
	{
		prenode = h->first;					//이전 노드가 first를 가르킨다.
		removenode = h->first->rlink;		//제거 노드가 first의 link를 가르킨다.
		while (removenode->rlink != NULL)		// 가르키는 링크가 NULL값이면
		{
			prenode = removenode;				// removenode의 주소를 prenode에 저장
			removenode = removenode->rlink;		// 다음 리스트를 찾는다.
		}
		free(removenode);
		prenode->rlink = NULL;				//pre가 가르키고 있는 링크를 NULL로만든다.

	
	}



	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;													//새로운 노드를 초기화한다.
	node->rlink = NULL;
	node->llink = NULL;
	if(h->first == NULL)												// 헤더가 비었으면
	{
		h->first = node;
	}
	else																// 그외의 경우에는
	{
		node->rlink = h->first;
		h->first->llink = node;
		h->first = node;
	}
	

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	listNode* removenode = (listNode*)malloc(sizeof(listNode)); // 첫 번째 노드를 지울 포인터 노드를 동적할당 받는다.
	removenode = h->first;										// removernode는 h.first의 주소값을 같는다.
	h->first = removenode->rlink;								// h.first를 removernode.link로 옮긴다.
	free(removenode);											// 메모리 해제
	return 0;

}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {
	listNode* p;			//	처음 주소를 저장하는 노드
	listNode* q;			//	역순으로 변경해주기 위한 q,r노드들
	listNode* r;			
	p = h->first;			// 포인터 p를 첫 번째 노드에 설정
	q = NULL;				// 초기화

	while (p != NULL) {		// 리스트의첫 번째 노드부터 링크를 따라 다음 노드로 이동하면서 노드간 연결을 바꾼다.
		r = q;				// 초기화
		q = p;				// q에 p노드의 정보를 저장
		p = p->rlink;		// 다음 노드를 찾는다.
		q->rlink = r;		// r을 다음 노드로 지정한다.
	}
	h->first = q;			// 처음 주소를 q로 변경

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */

int insertNode(headNode* h, int key) {
   listNode* newnode = (listNode*)malloc(sizeof(listNode));		// 노드를 입력받을 노드 
   listNode* findnode = (listNode*)malloc(sizeof(listNode));	// 

   newnode->key = key;
   newnode->rlink = NULL;
   newnode->llink = NULL;

   if (h->first == NULL)                                          // 헤드 노드가 비어있으면
   {
      h->first = newnode;
   }
   else if (h->first->key >= newnode->key)                              // 입력 된 값이 첫번째 노드 값보다 작으면 
   {
      newnode->rlink = h->first;
      h->first->llink = newnode;
      h->first = newnode;

   }
   else {
      findnode = h->first; // findnode의 주소값을 frist로 가르킨다.

      while (findnode!= NULL)   						// 찾는 노드가 널값을 가지기 이전까지 탐색
      {
         if (newnode->key <= findnode->key)				// 입력된 값이 찾는 값보다 작거나 같을때 
         {
            newnode->rlink = findnode;
            newnode->llink = findnode->llink;
            findnode->llink->rlink = newnode;
            findnode->llink = newnode;
            return 0;
         }

         if (findnode->rlink == NULL)					// 만약 다음 노드가 널값이면 중지
            break;

         findnode = findnode->rlink;                  	// 다음 리스트로 넘어간다.
      }

      if (findnode->rlink == NULL && findnode->key < key)		// 새로 입력된 값이 마지막에 입력될 경우
      {
         findnode->rlink = newnode;
         newnode->llink = findnode;
         newnode->rlink = NULL;
      }
   }
   return 0;
}

/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {
	listNode* prenode;																// 이전 주소를 저장할 노드
	listNode* findnode;																// 처음 주소값을 저장할 노드
	listNode* removenode = (listNode*)malloc(sizeof(listNode));						// 찾은 노드 값을 해제할 노드를 동적할당 
	if (h->first == NULL)															// 헤더가 NULL값이면 0값을 반환
	{
		printf("빈 리스트입니다.\n");
		return 0;
	}
	else
	{
	
		if (h->first->key == key) 													// key값이 첫 노드 일 경우
		{
		
			removenode = h->first;														// 노드가 헤드를 가르킨다.
			h->first = removenode->rlink;												// 헤드가 removenode.rlink가 가르키는 노드를 가르킨다.
			h->first->llink =NULL;														
		 	free(removenode);															// 메모리 할당 해제
		 	return 0;
	 	}
		else {
			prenode = h->first;
			findnode = h->first->rlink;
			while (findnode->rlink != NULL)										// remove ->link 가 널이 아닐때까지, 사용자가 찾는 값 까지 탐색
			{
				prenode = findnode;												// removenode의 주소를 prenode에 저장
				findnode = findnode->rlink;										// 다음 리스트를 찾는다.
				
				if(findnode->key == key)										// key값과 같은 노드를 찾았을때 while문 중지
					break;
				
				
			}
			
			if(findnode->rlink == NULL)													// 마지막 노드를 지울때 
			{
				removenode = findnode;
				prenode = findnode->llink;
				prenode->rlink= NULL;
				free(removenode);
				
			}

			else																					// 그외의 경우
			{
				removenode = findnode;
				prenode->rlink = findnode->rlink;
				findnode->rlink->llink  = findnode->llink;											// 삭제하고 중간 값을 삭제하고  노드를 이어준다.
				free(removenode);
			}
		}
	}
	return 1;
}
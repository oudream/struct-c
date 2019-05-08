#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>


typedef struct Node
{
	int data;
	struct Node * next;
}NODE, *PNODE;

int is_empty(PNODE pHead);               //�ж������Ƿ�Ϊ��
int is_last(PNODE p, PNODE pHead);       //�жϵ�ǰλ���Ƿ�Ϊĩβ
PNODE create_list();                     //������ͷ��㵥��������ͷָ��
PNODE find(int x, PNODE pHead);          //��������
PNODE find_previous(int x, PNODE pHead); //����x��ǰ��
void delete_node(int x, PNODE pHead);    //����ɾ������
void insert(int x, PNODE pHead, PNODE p);//��������
void delete_list(PNODE pHead);           //�������
void insertSort(PNODE pHead);			 //�������ֱ�Ӳ�������


/*
�������ֱ�Ӳ�������
*/
void insertSort(PNODE pHead)
{
	int value;
	PNODE pCom, pPre, pTmp;

	//���������ܹ�˳����ʣ������ﶨ�������ָ���������٣�
	//Ҫ�Ƚ�Ԫ��pTmp�͵�ǰ�Ƚ�Ԫ�ص�ǰ��pCom
	for (pTmp = pHead->next->next; pTmp != NULL; pTmp = pTmp->next)
	{
		//Ѱ��pPre
		pPre = pHead;
		while (pPre->next != pTmp)
			pPre = pPre->next;

		//ֻҪpCom��ָ�Ľڵ����һ���ڵ㲻��pTmp����������
		//��pCom��ָ�Ľڵ�����ݴ���pTmp��ָ�ڵ����ݣ��򽻻��������ڵ��λ��
		for (pCom = pHead; pCom->next != pTmp; pCom = pCom->next)
		{
			if (pCom->next->data > pTmp->data)
			{
				pPre->next = pTmp->next;
				pTmp->next = pCom->next;
				pCom->next = pTmp;
				break;
			}
		}
	}
}

/*
������ͷ��㵥��������ͷָ��
*/
PNODE create_list()
{
	int val;
	PNODE pHead = (PNODE)malloc(sizeof(NODE));
	PNODE pCurrent = pHead;
	pCurrent->next = NULL;
	if (NULL == pHead)
	{
		printf("pHead malloc failed.\n");
		exit(-1);
	}
	while (1)
	{
		scanf("%d", &val);
		if (val == -1)//�������Ϊ-1��������ѭ��
			break;

		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		if (NULL == pNew)
		{
			printf("pNew malloc failed.\n");
			exit(-1);
		}
		pNew->data = val;
		pNew->next = pCurrent->next;
		pCurrent->next = pNew;
		pCurrent = pCurrent->next;
	}

	return pHead;
}

/*
�ж������Ƿ�Ϊ��
*/
int is_empty(PNODE pHead)
{
	return pHead->next == NULL;
}

/*
�жϵ�ǰλ���Ƿ�Ϊĩβ
*/
int is_last(PNODE p, PNODE pHead)
{
	return p->next == NULL;
}

/*
��������
*/
PNODE find(int x, PNODE pHead)
{
	PNODE p;
	p = pHead->next;

	while (NULL != p && p->data != x)
		p = p->next;

	return p;
}

/*
����x��ǰ��
*/
PNODE find_previous(int x, PNODE pHead)
{
	PNODE p;
	p = pHead;

	while (NULL != p->next && p->next->data != x)
		p = p->next;

	return p;
}


/*
����ɾ������
ͨ��ǰ����ɾ��Ҫɾ���Ľڵ�
*/
void delete_node(int x, PNODE pHead)
{
	PNODE p, temp;
	p = find_previous(x, pHead);

	//�����ǰ��p�ĺ��滹�нڵ�
	if (!is_last(p, pHead))
	{
		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
}

/*
��������
*/
void insert(int x, PNODE pHead, PNODE p)
{
	PNODE pNew;
	pNew = (PNODE)malloc(sizeof(NODE));
	if (NULL == pNew)
	{
		printf("pNew malloc failed.");
	}

	pNew->data = x;
	pNew->next = p->next;
	p->next = pNew;
}

/*
ɾ������
*/
void delete_list(PNODE pHead)
{
	PNODE p, temp;
	p = pHead->next;
	pHead->next = NULL;

	while (p != NULL)
	{
		temp = p->next;
		free(p);
		p = temp;
	}
}

void traverse(PNODE pHead)
{
	PNODE p = pHead->next;

	while (NULL != p)
	{
		printf("%d\n", p->data);
		p = p->next;
	}
}



int main()
{
	int x;
	PNODE pHead, p;

	//��������
	printf("����-1��������\n");
	pHead = create_list();

	//��������
	insertSort(pHead);
	traverse(pHead);

	return 0;
}
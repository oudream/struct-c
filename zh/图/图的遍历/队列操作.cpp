#include "stdafx.h"


/*
��������
*/
PQUEUE CreateQueue()
{
	PQUEUE Q;
	Q = (PQUEUE)malloc(sizeof(struct Queue));
	if (NULL == Q)
	{
		printf("Out of space.\n");
		exit(-1);
	}

	Q->Front = Q->Rear = (PQNODE)malloc(sizeof(struct QNode));
	if (NULL == Q->Front)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	Q->Front->pNext = NULL;
	Q->Rear->pNext = NULL;

	return Q;
}

/*
���
*/
void EnQueue(int X, PQUEUE Q)
{
	PQNODE pNew;
	pNew = (PQNODE)malloc(sizeof(struct QNode));
	if (NULL == pNew)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	else
	{
		pNew->pNext = Q->Rear->pNext;
		Q->Rear->pNext = pNew;
		Q->Rear = pNew;
		pNew->data = X;
	}
}

/*
����
*/
void DeQueue(PQUEUE Q)
{
	if (IsQueueEmpty(Q))
	{
		printf("The queue is empty.\n");
		exit(-1);
	}

	PQNODE tmp = Q->Front->pNext;
	Q->Front->pNext = tmp->pNext;
	free(tmp);
}

/*
����ջ��Ԫ��
*/
int Front(PQUEUE Q)
{
	if (!IsQueueEmpty(Q))
		return Q->Front->pNext->data;
	else
	{
		printf("The queue can not return the top element, because it is empty now.\n");
		exit(-1);
	}
}

/*
�ж϶����Ƿ�Ϊ��
*/
int IsQueueEmpty(PQUEUE Q)
{
	return Q->Front->pNext == NULL;
}
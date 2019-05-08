#include "stdafx.h"


/*
����ջ�ṹ
*/
PSTACK CreateStack()
{
	//����ջ�ṹ�ռ�
	PSTACK S;
	S = (PSTACK)malloc(sizeof(struct Stack));
	if (NULL == S)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	S->TopOfStack = (PSNODE)malloc(sizeof(struct SNode));
	if (NULL == S->TopOfStack)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	//��ʼ��ջ
	S->TopOfStack->pNext = NULL;
	return S;
}

/*
��ջ
*/
void Push(int X, PSTACK S)
{
	PSNODE pNew = (PSNODE)malloc(sizeof(struct SNode));
	if (NULL == pNew)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	else
	{
		pNew->pNext = S->TopOfStack->pNext;
		S->TopOfStack->pNext = pNew;
		pNew->data = X;
	}
}

/*
��ջ
*/
void Pop(PSTACK S)
{
	if (IsStackEmpty(S))
	{
		printf("The stack is empty.\n");
		exit(-1);
	}

	PSNODE tmp = S->TopOfStack->pNext;
	S->TopOfStack->pNext = tmp->pNext;
	free(tmp);
}

/*
����ջ��Ԫ��
*/
int Top(PSTACK S)
{
	if (!IsStackEmpty(S))
		return S->TopOfStack->pNext->data;
	else
	{
		printf("The stack can not return the top element, because it is empty now.\n");
		exit(-1);
	}
}

/*
�ж�ջ�Ƿ�Ϊ��
*/
int IsStackEmpty(PSTACK S)
{
	return S->TopOfStack->pNext == NULL;
}
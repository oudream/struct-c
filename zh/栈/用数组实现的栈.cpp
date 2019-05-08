/**********************************************************************
ջ��������
������ʵ�ֵ�ջ�ṹ��ȱ����������Ҫ��̬�ķ�����Դ�������������������
����һ��ջ�ṹ�洢��ɾ�������ݣ���ʹ������ʵ����Ч�ʸ���һЩ��Ψһ�Ĳ���
���Ǿ�����Ҫ��ǰ������ռ��С,����ֻ��ʵ����һЩջ��������
������find_min������
**********************************************************************/

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


typedef struct StackRecord
{
	int capcity;
	int topOfStack;
	int *array;
}*Stack;	//ջָ�����


void dispose_stack(Stack S);
int is_empty(Stack S);
void make_empty(Stack S);
int is_full(Stack S);
Stack create_statck(int maxElements);
Stack create_mstatck(int maxElements);
void push(int x, Stack S, Stack M);
int top(Stack S);
void pop(Stack S, Stack M);
int top_and_pop(Stack S, Stack M);
int find_min(Stack M);


void main()
{
	Stack S = create_statck(5);
	Stack M = create_mstatck(1);

	push(10, S, M);
	push(3, S, M);
	printf("min is:%d\n", find_min(M));
	pop(S, M);
	printf("min is:%d\n", find_min(M));
}


/*
�ͷ�ջ����
*/
void dispose_stack(Stack S)
{
	if (NULL != S)
	{
		free(S->array);
		free(S);
	}
}

/*
�ж�ջ�Ƿ�Ϊ������
*/
int is_empty(Stack S)
{
	return S->topOfStack == -1;
}

/*
����һ����ջ����
*/
void make_empty(Stack S)
{
	S->topOfStack = -1;
}

/*
�ж�ջ��������
*/
int is_full(Stack S)
{
	return S->topOfStack == S->capcity - 1;
}

/*
����ջ����
*/
Stack create_statck(int maxElements)
{
	Stack s;

	//����ջ�ռ�
	s = (Stack)malloc(sizeof(struct StackRecord));
	if (NULL == s)
	{
		printf("Out of space.\n");
		exit(-1);
	}

	//����ջ����ռ�,ջ��ʼ��
	s->array = (int*)malloc(sizeof(int) * maxElements);
	if (NULL == s->array)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	s->capcity = maxElements;
	make_empty(s);

	return s;
}

/*
������Сֵջ����
*/
Stack create_mstatck(int maxElements)
{
	Stack m;

	//����ջ�ռ�
	m = (Stack)malloc(sizeof(struct StackRecord));
	if (NULL == m)
	{
		printf("Out of space.\n");
		exit(-1);
	}

	//����ջ����ռ�,ջ��ʼ��
	m->array = (int*)malloc(sizeof(int) * maxElements);
	if (NULL == m->array)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	m->capcity = maxElements;
	make_empty(m);

	return m;
}

/*
��ջ����
*/
void push(int x, Stack S, Stack M)
{
	if (is_full(S))
	{
		printf("Full stack.\n");
	}
	else
	{	//�����ǰ��ջֵ��M��ջ��ֵС�滻
		if (!is_empty(M))
		{
			if (x < top(M))
				M->array[M->topOfStack] = x;
		}
		else
		{
			M->array[++M->topOfStack] = x;
		}

		S->array[++S->topOfStack] = x;
	}
}

/*
����ջ������
*/
int top(Stack S)
{
	if (!is_empty(S))
		return S->array[S->topOfStack];
	printf("Empty stack.\n");

	return 0;
}

/*
��ջ����
*/
void pop(Stack S, Stack M)
{
	int i;

	if (is_empty(S))
	{
		printf("Empty stack.\n");
	}
	else
	{	//���Ҫ��ջ��Ԫ������Сֵ
		//��Сֵջ��ջ,S��ջ,��Sջ��Ϊ��ʱ�ҳ���Сֵ������Сֵջ
		if (top(M) == top(S))
		{
			M->topOfStack--;
			S->topOfStack--;
		}
		if (!is_empty(S))
		{
			int min = S->array[0];
			for (i = 0; i <= S->topOfStack; i++)
			{
				if (S->array[i] < min)
					min = S->array[i];
			}

			M->array[++M->topOfStack] = min;
		}
	}
}

/*
����Ԫ�ز���ջ����
*/
int top_and_pop(Stack S, Stack M)
{
	int i, topValue;

	if (!is_empty(S))
	{	
		if (top(M) == top(S))
		{
			M->topOfStack--;
			topValue = S->array[S->topOfStack--];
		}
		if (!is_empty(S))
		{
			int min = S->array[0];
			for (i = 0; i <= S->topOfStack; i++)
			{
				if (S->array[i] < min)
					min = S->array[i];
			}
			M->array[M->topOfStack] = min;
		}

		return topValue;
	}
	printf("Empty stack.\n");

	return 0;
}

/*
�ҳ�ջ����СԪ��
*/
int find_min(Stack M)
{
	return top(M);
}
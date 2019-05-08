#include "targetver.h"

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>


/*
ͼ���ڽӱ�洢�ṹ
���ڽӱ�����һ��������洢ÿ���ڵ���Ϊͷ��㣬
ÿ��ͷ���������һ������洢ͼ��ÿ���ߵ���ֹ�ڵ㡣
*/
typedef struct Node
{	//����ṹ�洢����ָ��Ľڵ�
	int vertex;		//����ͼ�б�ʾһ���߼�����ָ��ĵ���Ϣ
	struct Node *pNext;	//�����ڸýڵ����һ���ڵ�
}NODE, *PNODE;
typedef struct Head
{	//����ṹ�洢������ʼ��
	int data;		//����ʼ����Ϣ
	PNODE pAdj;		//��β�ڵ���Ϣ
	struct Head *pNext;	//�����ڸýڵ����һ���ڵ�
}*Graph;


//����ͼ�ṹ
Graph CreateGraph(int, int, Graph);

//ͼ��������ȱ���
void DFS(Graph);

//ͼ�Ĺ�����ȱ���
void BFS(Graph);


/*
ջ�ṹ����
*/
typedef struct SNode
{	//ջ�ڵ㱣��ڵ���Ϣ����һ���ڵ�ĵ�ַ
	int data;
	struct SNode *pNext;
}SNODE, *PSNODE;
typedef struct Stack
{	//ջ�ṹ������ջ��ָ��
	PSNODE TopOfStack;
}STACK, *PSTACK;


//����ջ�ṹ
PSTACK CreateStack();

//�ж�ջ�Ƿ�Ϊ��
int IsStackEmpty(PSTACK);

//��ջ
void Push(int, PSTACK);

//��ջ
void Pop(PSTACK);

//����ջ��Ԫ��
int Top(PSTACK);


/*
���нṹ
*/
typedef struct QNode
{	//���нڵ㱣��ڵ���Ϣ����һ���ڵ�ĵ�ַ
	int data;
	struct QNode *pNext;
}QNODE, *PQNODE;
typedef struct Queue
{	//���нṹ�������ͷָ��Ͷ�βָ��
	PQNODE Front;
	PQNODE Rear;
}QUEUE, *PQUEUE;


//��������
PQUEUE CreateQueue();

//�ж϶����Ƿ�Ϊ��
int IsQueueEmpty(PQUEUE);

//���
void EnQueue(int, PQUEUE);

//����
void DeQueue(PQUEUE);

//����ջ��Ԫ��
int Front(PQUEUE);

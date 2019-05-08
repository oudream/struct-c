#include "stdafx.h"


#define NUM 100 	//ͼ�нڵ����
int STATUS[NUM];	//���汻���ʹ��ڵ���Ϣ

/*
����ͼ�ṹ
*/
Graph CreateGraph(int Start, int End, Graph OriginG)
{
	int i;
	Graph G, tmp;

	//��ͼΪ���򴴽�ͼ��������Gָ��ԭʼ��ͼ
	if (NULL == OriginG)
	{
		//�����ڽӱ�ͷ�ڵ�洢�ռ�
		G = (Graph)malloc(sizeof(struct Head));
		if (NULL == G)
		{
			printf("Out of space.\n");
			exit(-1);
		}
		G->pNext = NULL;

		//��ʼ���ڽӱ�ͷ����
		for (i = 0; i < NUM; i++)
		{
			tmp = (Graph)malloc(sizeof(struct Head));
			if (NULL == tmp)
			{
				printf("Out of space.\n");
				exit(-1);
			}
			tmp->data = i;
			tmp->pAdj = NULL;
			tmp->pNext = G->pNext;
			G->pNext = tmp;
		}
	}
	else
		G = OriginG;

	//���������ӽڵ�洢�ռ�
	PNODE newNode = (PNODE)malloc(sizeof(struct Node));
	if (NULL == newNode)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	else
	{
		//�����ӽӽڵ��ʼ��
		newNode->vertex = End;
		newNode->pNext = NULL;
	}

	//ͨ��ͼ�Ļ���ϢΪͼ��ʼ��
	tmp = G->pNext;
	for (i = 0; i < NUM; i++)
	{
		if (tmp->data == Start)
		{
			newNode->pNext = tmp->pAdj;
			tmp->pAdj = newNode;
			newNode->vertex = End;
			break;
		}
		tmp = tmp->pNext;
	}

	return G;
}

/*
�ڵ��Ƿ񱻷��ʹ�
*/
int has_visited(PNODE Child)
{
	if (Child == NULL)
		return 0;

	return STATUS[Child->vertex] == 1;
}

/*
Ѱ����һ������ʼ��
*/
Graph next_vertex(Graph G, int info)
{
	Graph pStart = G->pNext;
	while (pStart->data != info)
		pStart = pStart->pNext;

	return pStart;
}

/*
ͼ��������ȱ���
*/
void DFS(Graph G, int Start)
{
	//ͼָ��,����,����ͼ��ʼ�Ľڵ㲢ָ����
	Graph pTraverse = next_vertex(G, Start);

	//����ջ�ṹ�洢�������Ľڵ�
	PSTACK S = CreateStack();

	//��Start�ڵ���Ϊ��ȱ���ɭ�ֵĸ��������Ϊ�ѱ�����
	Push(pTraverse->data, S);
	STATUS[pTraverse->data] = 1;
	printf("%d ", Top(S));

	//ʹ��ջ�ṹ�洢�������ڵ㣬ģ��ݹ�ĵ�ִ�з�ʽ
	while (!IsStackEmpty(S))
	{
		if (pTraverse->pAdj != NULL)					//���ڽӱ�ͷ�ڵ���ĳ�����������ӱ���������ʼ������ֹ��
		{
			//��һ��Ҫ�����Ľڵ㣨����β��
			PNODE pChild = pTraverse->pAdj;

			if (pChild == NULL)							//��Ҫ�����Ľڵ㣨����β���ǿգ�����pTraverseָ��գ�ifѭ���ж�����ʱ��ת��ִ�г�ջ����
			{
				pTraverse->pAdj = NULL;
				continue;
			}

			if (has_visited(pChild))					//��Ҫ�����Ľڵ��Ѿ���������ת��������ڵ����һ������
			{
				//Ѱ���¸�δ�������Ľڵ�
				while (has_visited(pChild))
				{
					pChild = pChild->pNext;
				}

				if (pChild == NULL)						//����һ�����յ�Ϊ�գ���ջ
				{
					Pop(S);
					if (IsStackEmpty(S))				//��ջΪ����ζ�ű�������������ѭ��
						break;

					//����ͼ�ĸýڵ����һ���ڵ�Ļ���ʼ�ڵ�״̬
					pTraverse = next_vertex(G, Top(S));
				}
				else 
				{	//��Ҫ�����Ľڵ�δ������
					//����ڵ���Ϣ
					printf("%d ", pChild->vertex);

					//�����±������Ľڵ���Ϣ��ջ
					Push(pChild->vertex, S);
					STATUS[pChild->vertex] = 1;

					//Ѱ����һ��������ʼ��
					pTraverse = next_vertex(G, pChild->vertex);
				}
			}
			else
			{	//��Ҫ�����Ľڵ�δ������
				//����ڵ���Ϣ
				printf("%d ", pChild->vertex);

				//�����±������Ľڵ���Ϣ��ջ
				Push(pChild->vertex, S);
				STATUS[pChild->vertex] = 1;

				//Ѱ����һ��������ʼ��
				pTraverse = next_vertex(G, pChild->vertex);
			}
		}
		else
		{	//����һ�����յ�Ϊ�գ���ջ���˻ص���ǰ̽��ڵ����һ���ڵ�
			//����̽���˻ؽڵ����һ���ڵ�
			//��ջΪ����ζ�ű�������������ѭ��
			Pop(S);
			if (IsStackEmpty(S))
				break;

			//����ͼ�ĸýڵ����һ���ڵ�Ļ���ʼ�ڵ�״̬
			pTraverse = next_vertex(G, Top(S));
		}
	}
	printf("\n");
	return;
}

/*
ͼ�Ĺ�����ȱ���
*/
void BFS(Graph G, int Start)
{
	//ͼָ��,����,����ͼ��ʼ�Ľڵ㲢ָ����
	Graph pTraverse = next_vertex(G, Start);

	//�������нṹ�洢�������Ľڵ�
	PQUEUE Q = CreateQueue();

	//��Start�ڵ���Ϊ��ȱ���ɭ�ֵĸ��������Ϊ�ѱ�����
	EnQueue(pTraverse->data, Q);
	STATUS[pTraverse->data] = 1;
	printf("%d ", Front(Q));

	//ֻҪ��������Ԫ�ش��ڣ��ͱ������ڽӽڵ�
	while (!IsQueueEmpty(Q))
	{
		PNODE pChild = pTraverse->pAdj;

		while (pChild != NULL)
		{
			printf("%d ", pChild->vertex);
			EnQueue(pChild->vertex, Q);
			pChild = pChild->pNext;
		}
		DeQueue(Q);
		pTraverse = next_vertex(G, Front(Q));
	}

	printf("\n");
	return;
}
















int main()
{
	Graph G = NULL;
	int flag = 1, C, trav_begin;

	while (flag)
	{
		printf("-------------------------------��������еĲ���-------------------------------\n");
		printf("|                                                                            |\n");
		printf("|                              1.����ͼ                                      |\n");
		printf("|                              2.DFS                                         |\n");
		printf("|                              3.BFS                                         |\n");
		printf("------------------------------------------------------------------------------\n");

		scanf("%d", &C);
		switch (C)
		{
		case 1:
			int start, end;
			printf("�����뻡����ʼ������յ�\n");
			scanf("%d%d", &start, &end);
			G = CreateGraph(start, end, G);
			break;

		case 2:
			printf("�����������ʼ�ڵ�\n");
			scanf("%d", &trav_begin);
			DFS(G, trav_begin);
			break;

		case 3:
			printf("�����������ʼ�ڵ�\n");
			scanf("%d", &trav_begin);
			BFS(G, trav_begin);

		default:
			flag = 0;
			break;
		}
	}
    return 0;
}


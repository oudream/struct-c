#include "stdafx.h"

/*
�ж϶����Ƿ�Ϊ��
*/
int IsEmpty(Queue Q)
{
	return Q->Size == 0;
}

/*
�ж϶����Ƿ�����
*/
int IsFull(Queue Q)
{
	return Q->Size == Q->Capcity;
}

/*
��������
*/
Queue CreateQueue(int MaxElements)
{
	//������д洢�ṹ�ռ�
	Queue Q = (Queue)malloc(sizeof(struct QueueRecord));
	if (NULL == Q)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	//������е�����洢�ṹ�ռ�
	Q->Array = (int *)malloc(MaxElements*sizeof(int));
	if (NULL == Q->Array)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	//��ʼ��
	MakeEmpty(Q);
	Q->Capcity = MaxElements;
	return Q;
}

/*
���ٶ���
*/
void DisposeQueue(Queue Q)
{
	free(Q->Array);
	free(Q);
}

/*
��ն���
*/
void MakeEmpty(Queue Q)
{
	Q->Size = 0;
	Q->Front = 0;
	Q->Rear = 1;
}

/*
���
*/
void Enqueue(ElementType X, Queue Q)
{
	if (IsFull(Q))
	{
		printf("The queue is full.\n");
		exit(-1);
	}
	else
	{
		Q->Size++;
		if (Q->Rear == Q->Capcity - 1)
			Q->Rear = 0;
		else
			Q->Rear++;
		Q->Array[Q->Rear] = X;
	}
}

/*
����
*/
void Dequeue(Queue Q)
{
	if (IsEmpty(Q))
	{
		printf("The queue is empty.\n");
		exit(-1);
	}
	else
	{
		Q->Size--;
		if (Q->Front == Q->Capcity - 1)
			Q->Front = 0;
		else
			Q->Front++;
	}
}

/*
���ض�ͷԪ��
*/
ElementType Front(Queue Q)
{
	if (!IsEmpty(Q))
		return Q->Array[Q->Front];
	else
		printf("When front the Queue, the queue is empty.\n");
	return -1;
}

/*
���ض�ͷԪ�ز�����
*/
ElementType FrontAndDequeue(Queue Q)
{
	ElementType X;

	if (IsEmpty(Q))
	{
		printf("The queue is empty.\n");
		exit(-1);
	}
	else
	{
		Q->Size--;
		if (Q->Front == Q->Capcity - 1)
			Q->Front = 0;
		else
		{
			X = Q->Array[Q->Front];
			Q->Front++;
		}
	}

	return X;
}

//չʾ����Ԫ��
void show(Queue Q)
{
	int i;
	if (Q->Front <= Q->Rear)
	{
		printf("The queue elements is:\n");
		for (i = Q->Front; i <= Q->Rear; i++)
			if(Q->Array[i] > 0)
				printf("%d\t", Q->Array[i]);
		printf("\n");
	}
	else
	{
		printf("The queue elements is:\n");
		for (i = Q->Front; i < Q->Capcity; i++)
			if (Q->Array[i] > 0)
				printf("%d\t", Q->Array[i]);
		for (i = 0; i <= Q->Rear; i++)
			if (Q->Array[i] > 0)
				printf("%d\t", Q->Array[i]);
		printf("\n");
	}
}









int main()
{
	Queue Q = NULL;
	int flag = 1, c, capcity, element;

	while (flag)
	{
		if (Q == NULL)
			printf("The queue basic operate has been here, please input the choice.\n");

		printf("|--------------------------Choices------------------------------|\n");
		printf("|                    1.Create Queue.                            |\n");
		printf("|                    2.Enqueue.                                 |\n");
		printf("|                    3.Deueue.                                  |\n");
		printf("|                    4.Front.                                   |\n");
		printf("|                    5.Front And Dequeue.                       |\n");
		printf("|                    6.Dispose Queue.                           |\n");
		printf("|                    7.exit.                                    |\n");
		printf("|---------------------------------------------------------------|\n");

		printf("Please input the choice:\n");
		scanf("%d", &c);
		switch (c)
		{
		case 1:
			 printf("Please input the capcity.\n");
			 scanf("%d", &capcity);

			 Q = CreateQueue(capcity);
			 printf("Create queue success.\n");
			 break;

		case 2:
			printf("Please input the enqueue element.\n");
			scanf("%d", &element);

			Enqueue(element, Q);
			show(Q);
			break;

		case 3:
			Dequeue(Q);
			show(Q);
			break;

		case 4:
			printf("The front element is: %d\n", Front(Q));
			break;

		case 5:
			printf("Before dequeue element is: %d\n", FrontAndDequeue(Q));
			break;

		case 6:
			DisposeQueue(Q);
			break;

		default:
			flag = 0;
			break;
		}
	}
    return 0;
}


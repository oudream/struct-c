#include "targetver.h"
#include <stdio.h>
#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>


typedef int ElementType;


/*
����ʵ�ֶ��нṹ
*/
typedef struct QueueRecord
{
	int Capcity;
	int Size;
	int Front;
	int Rear;
	ElementType *Array;
}*Queue;


int IsEmpty(Queue Q);					//�ж϶����Ƿ�Ϊ��
int IsFull(Queue Q);					//�ж϶����Ƿ�����
Queue CreateQueue(int MaxElements);		//��������
void DisposeQueue(Queue Q);				//���ٶ���
void MakeEmpty(Queue Q);				//��ն���
void Enqueue(ElementType X, Queue Q);	//���
void Dequeue(Queue Q);					//����
ElementType Front(Queue Q);				//���ض�ͷԪ��
ElementType FrontAndDequeue(Queue Q);	//���ض�ͷԪ�ز�����
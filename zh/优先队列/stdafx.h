#include "targetver.h"
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>


#define ElementType int


/*
���ȶ�������ʵ��
*/
typedef struct HeapStrcut	//�ѽṹ
{
	int Capcity;
	int Size;
	ElementType *Elements;
}*PriorityQueue;


PriorityQueue Initialize(int MaxElements);	//������ʼ�����ȶ���
void Insert(ElementType X, PriorityQueue H);//����
ElementType DeleteMin(PriorityQueue H);		//ɾ����С�ڵ�
int IsEmpty(PriorityQueue H);				//�ж����ȶ����Ƿ�Ϊ��
int IsFull(PriorityQueue H);				//�ж����ȶ����Ƿ�����
#include "stdafx.h"


/*
 * �ṹ���ʣ�
 *         1. ��ȫ��������
 *         2. �߶�ΪlogN��
 *         3. ��ȫ�������й��ɣ���ʹ������ʵ�֣��������2i���Ҷ�����2i+1,������i/2��
 * �������ʣ�
 *         1. С���ѣ��󶥶ѡ�
 *         2. �����ѣ����Ӷ�O(N)��
 *
 *            ֤����https://www.zhihu.com/question/20729324
 * 
 *         3. ���루���ˣ���ɾ�������ˣ������Ӷ�O(logN)��
 * Ӧ�ã� 
 *         1. ѡ�����⣬topK���⡣
 * */


/*
������ʼ�����ȶ���
С���ѣ���СԪ�ڸ��ڵ�
*/
PriorityQueue Initialize(int MaxElements)
{
	PriorityQueue H;
	//�������ȶ��нṹ�ռ�
	H = (PriorityQueue)malloc(sizeof(struct HeapStrcut));
	if(NULL == H)
	{ 
		printf("Out of space.\n");
		exit(-1);
	}
	//����洢��������Elements�ռ�
	H->Elements = (ElementType *)malloc(sizeof(ElementType)*MaxElements);
	if (H->Elements == NULL)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	//��ʼ�����ȶ���
	H->Capcity = MaxElements;
	H->Size = 0;
}

/*
���룬������ʵʩ�ĸ�ֵ���Ϊd+1
*/
void Insert(ElementType X, PriorityQueue H)
{
	int i;

	if(IsFull(H))
	{ 
		printf("The PriorityQueue is full.\n");
		exit(-1);
	}
	
	for (i = ++H->Size; H->Elements[i / 2] > X; i /= 2)
		H->Elements[i] = H->Elements[i / 2];
	H->Elements[i] = X;
}
//�ҵĲ���д����������ʵʩ�ĸ�ֵ���Ϊ3d
void Insert2(ElementType X, PriorityQueue H)
{
	int i, tmp;

	if (IsFull(H))
	{
		printf("The PriorityQueue is full.\n");
		exit(-1);
	}

	H->Elements[++H->Size] = X;
	tmp = H->Elements[H->Size];
	for (i = H->Size; i / 2 > 0; i /= 2)
		if (H->Elements[i / 2] > H->Elements[i])
			H->Elements[i] = H->Elements[i / 2];
		else
			break;
	H->Elements[i] = tmp;
}

/*
ɾ����С�ڵ�
*/
ElementType DeleteMin(PriorityQueue H)
{
	int i, child;
	ElementType MinElement, LastElement;

	if (IsEmpty(H))
	{
		printf("The PriorityQueue is empty.\n");
		exit(-1);
	}
	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];

	for (i = 1; i * 2 <= H->Size; i = child)
	{
		//���ҽ�С���ӽڵ�
		child = i * 2;
		if (child != H->Size && H->Elements[child + 1] < H->Elements[child])
			child++;

		//���˲���
		if (LastElement > H->Elements[child])
			H->Elements[i] = H->Elements[child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}

/*
�ж����ȶ����Ƿ�Ϊ��
*/
int IsEmpty(PriorityQueue H)
{
	return H->Size == 0;
}

/*
�ж����ȶ����Ƿ�����
*/
int IsFull(PriorityQueue H)
{
	return H->Size == H->Capcity;
}

/*
��ʾ���ȶ���Ԫ��
*/
void show(PriorityQueue H)
{
	int i;
	for (i = 1; i <= H->Size; i++)
		printf("%d\t", H->Elements[i]);
	printf("\n");
}







int main()
{
	int max_elements, flag=1, choose, value;

	//�������ȶ���
	printf("��ʼ�������ȶ���\n");
	printf("���������ȶ��д�С��\n");
	scanf("%d", &max_elements);
	PriorityQueue H = Initialize(max_elements);
	
	//���ȶ��в���
	while (flag)
	{
		printf("�����������1.���� 2.ɾ����СԪ 3.��ʾ���ȶ���Ԫ��.\n");
		scanf("%d", &choose);
		switch (choose)
		{
		case 1:
			printf("���������Ԫ��\n");
			scanf("%d", &value);
			Insert(value, H);
			break;

		case 2:
			DeleteMin(H);
			show(H);
			break;

		case 3:
			show(H);
			break;

		default:
			flag = 0;
			break;
		}
	}




    return 0;
}


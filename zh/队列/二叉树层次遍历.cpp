#include "stdafx.h"

/*
����һ�ö�����,��������һ����Ȼ�ķ�ʽ�ǵݹ�ķ���,
ÿ���߶���ĳ���ڵ����ӵ����ĸ��ף���ȥ���ڵ�֮��ÿ���ڵ㶼��һ�����ס�
*/
BTree create_tree()
{
	int val;
	scanf("%d", &val);

	//����������ֵ�ؼ���Ϊ-1�򷵻�NULL
	if (val == -1)
		return NULL;

	//�������������������ʼ���ؼ���
	BTree root = (BTree)malloc(sizeof(struct BTNode));
	if (NULL == root)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	root->data = val;

	//�ݹ鴴��һ����
	printf("������%d�����ӣ�", val);
	root->Left = create_tree();
	printf("������%d���Һ��ӣ�", val);
	root->Right = create_tree();

	return root;
}

/*
�������Ĳ�α���
������д�Ķ���ʹ������ʵ��front��ʼ��Ϊ0,rear��ʼ��Ϊ1������Ӻ����ʱ�ͻᷢ����ַȡ����ֵ������,
���ԣ������α��������Լ�ʵ�ֵĶ��У�Ҫ����ʹ�ñ�׼�Ķ���ADT�Ļ����ʹ������ʵ�ֶ��С�
*/
void levelTraverse(BTree T)
{
	if (NULL == T)
		return;
	
	BTNode *Q[10];
	int front, rear;
	front = rear = 0;
	Q[rear++] = T;
	while (front != rear)
	{
		printf("%d ", Q[front]->data);
		if (NULL != Q[front]->Left)
		{
			Q[rear] = Q[front]->Left;
			rear++;
		}
		if (NULL != Q[front]->Right)
		{
			Q[rear] = Q[front]->Right;
			rear++;
		}
		front++;
		//printf("\n");
	}
}

/*
�������Ĳ�α��������ϵĵݹ鲢�����ã�
*/
//int levelTraverse(BTree T, int level)
//{
//	if (!T || level < 0)
//		return 0;
//	if (level == 0)
//	{
//		printf("%d", T->data);
//		return 1;
//	}
//	//printf("%d", T->data);
//	return levelTraverse(T->Left, level - 1) + levelTraverse(T->Right, level - 1);
//}










int main()
{
	BTree T;

	printf("�����������������Ľڵ���Ϣ��-1�����\n");
	T = create_tree();
	levelTraverse(T);
	
    return 0;
}


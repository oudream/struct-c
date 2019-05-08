#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


//����ƽ�����ṹ����
typedef struct AvlNode
{
	int element;
	struct AvlNode *left;
	struct AvlNode *right;
	int height;
}*Position, *AvlTree;


//������������
AvlTree MakeEmpty(AvlTree T);
Position find(int x, AvlTree T);
Position find_min(AvlTree T);
Position find_max(AvlTree T);
AvlTree insert(int x, AvlTree T);
AvlTree delete_avl(int x, AvlTree T);


/*
���ض���ƽ�����ڵ�ƽ�����Ӹ߶�
*/
static int height(Position P)
{
	if (NULL == P)
		return -1;
	else
		return P->height;
}

/*
�������ֵ����
*/
int max(int h1, int h2)
{
	if (h1 > h2)
		return h1;
	return h2;
}

/*
����һ�ſ���
ʹ�õݹ�ķ�ʽ���µ��Ͻ����е�ÿһ�����ͷſռ䣬
����NULL�����Գ�ʼ��һ�����ڵ㣬����ʹ�õݹ����ѭ���Ķ��塣
*/
AvlTree make_empty(AvlTree T)
{
	if (NULL != T)
	{
		make_empty(T->left);
		make_empty(T->right);
		free(T);
	}
	return NULL;
}

/*
����ƽ������find����
ʹ�õݹ�ķ�ʽ����Ԫ��x������TΪ�գ��򷵻�NULL��
��Ԫ��x�ȵ�ǰԪ��С����ݹ����Ԫ�ؽڵ�����������ң�
��Ԫ��x�ȵ�ǰԪ�ش���ݹ����Ԫ�ؽڵ�����������ң�
��󷵻ز��ҵ���Ԫ��x��
*/
Position find(int x, AvlTree T)
{
	if (NULL == T)
		return NULL;
	if (x < T->element)
		return find(x, T->left);
	else if (x > T->element)
		return find(x, T->right);
	else
		return T;
}

/*
����ƽ������find_min����
��Ϊ����������������ģ�����ֻ��Ҫ�ݹ�Ĳ�����������
�����Ϊ�գ�����NULL�����������Ϊ�գ�����������Ϊ�գ����ظ�T��
����ݹ���ڸ����������в��ң����صݹ鵽���ĸ�Ԫ�ء�
*/
Position find_min(AvlTree T)
{
	if (NULL == T)
		return NULL;
	if (NULL == T->left)
		return T;
	else
		return find_min(T->left);
}

/*
����ƽ������find_max������
ʹ�÷ǵݹ�ķ�ʽ���в��ҡ�
*/
Position find_max(AvlTree T)
{
	if (NULL != T)
	{
		while (NULL != T->right)
			T = T->right;
	}

	return T;
}

/*
����ת����ΪK2��K2��һ������K1��K2����K1������ת��
��ת��K1��ΪK2�ĸ��ڵ㣬K2��ΪK1���Һ��ӣ�K1���Һ��ӱ�ΪK2�����ӣ�
����K2��K1�ĸ߶ȣ������µĸ��ڵ㡣
*/
static Position single_rotate_withleft(Position K2)
{
	//����ת�ĸ�
	Position K1;
	K1 = K2->left;
	K2->left = K1->right;
	K1->right = K2;
	K2->height = max(height(K2->left), height(K2->right)) + 1;
	K1->height = max(height(K1->left), height(K1->right)) + 1;
	return K1;
}

/*
����ת����ΪK1��K1��һ���Һ���K2��K1��K2������ת��
��ת��K2��ΪK1�ĸ��ڵ㣬K1��ΪK2�����ӣ�K2�����ӱ�ΪK1���Һ��ӣ�
����K1��K2�ĸ߶ȣ������µĸ��ڵ㡣
*/
static Position single_rotate_withright(Position K1)
{
	//����ת�ĸ�
	Position K2;
	K2 = K1->right;
	K1->right = K2->left;
	K2->left = K1;
	K1->height = max(height(K1->left), height(K1->right)) + 1;
	K2->height = max(height(K2->left), height(K2->right)) + 1;
	return K2;
}

/*
˫��ת����ΪK3��K3��һ������K1��K1��һ���Һ���K2��
��ת����Ϊ��K1��K2������K2Ϊ���ĵ���ת����K3����ָ��ָ����ת���K2��
Ȼ��K3��K2�ڽ���һ����K2Ϊ���ĵ���ת������K2��
*/
static Position double_rotate_withleft(Position K3)
{
	K3->left = single_rotate_withright(K3->left);
	return single_rotate_withleft(K3);
}

/*
˫��ת����ΪK3��K3��һ���Һ���K1��K1��һ������K2��
��ת����Ϊ��K1��K2������K2Ϊ���ĵ���ת����K3���Һ���ָ����ת���K2��
Ȼ��K3��K2�ڽ���һ����K2Ϊ���ĵ���ת������K2��
*/
static Position double_rotate_withright(Position K3)
{
	K3->right = single_rotate_withleft(K3->right);
	return single_rotate_withright(K3);
}

/*
����ƽ�����Ĳ������,����˼·ͬ���������һ�����ں��ӵݹ���Ҳ�������һЩ���䣬
����ɹ��󣬴��µ��ϵݹ���ж�ÿ���ڵ�ĸ߶ȣ��ж����Ƿ�����ƽ��ԭ���������
����Ҫ������Ӧ����ת���������¶�����ƽ��߶ȣ�����������
*/
AvlTree insert(int x, AvlTree T)
{
	if (NULL == T)		//����Ϊ��������Ҫ����ڵ�ռ䲢��ʼ��
	{
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		if (NULL == T)
		{
			printf("Out of space.\n");
			exit(-1);
		}
		else
		{
			T->element = x;
			T->height = 0;
			T->left = T->right = NULL;
		}
	}
	else if (x < T->element)
	{	//������Ԫ��x�ȵ�ǰ�ڵ�С����ݹ����������������
		//���ݹ鷵�ص�ĳ�ڵ��ýڵ�ƽ�����Ӹ߶ȳ���2����
		//������ýڵ㼰�亢��λ�ã�ͨ����ת����ƽ�����Ӹ߶�
		T->left = insert(x, T->left);
		if (2 == height(T->left) - height(T->right))
		{
			if (x < T->left->element)
				T = single_rotate_withleft(T);
			else
				T = double_rotate_withleft(T);
		}
	}
	else if (x > T->element)
	{	//������Ԫ��x�ȵ�ǰ�ڵ����ݹ����������������
		//���ݹ鷵�ص�ĳ�ڵ��ýڵ�ƽ�����Ӹ߶ȳ���2����
		//������ýڵ㼰�亢��λ�ã�ͨ����ת����ƽ�����Ӹ߶�
		T->right = insert(x, T->right);
		if (2 == height(T->right) - height(T->left))
		{
			if (x > T->right->element)
				T = single_rotate_withright(T);
			else
				T = double_rotate_withright(T);
		}
	}

	//����������ƽ�����Ӹ߶�
	T->height = max(height(T->left), height(T->right)) + 1;

	return T;
}

/*
����ƽ������ɾ��
*/
AvlTree delete_avl(int x, AvlTree T)
{
	//printf("��ʼɾ��Ԫ��\n");
	if (NULL == T)
	{	//������Ϊ��û�нڵ����ɾ�����򷵻�����
		printf("Element not found.\n");
		exit(-1);
	}
	else if (x < T->element)
	{	//��������Ϊ���ҵ�ǰ�ڵ�Ԫ�ر�Ԫ��x��
		//��ݹ鵽�ýڵ���������н���ɾ��
		//���ݹ鷵�ص�ĳ�ڵ��ýڵ�ƽ�����Ӹ߶ȳ���2����
		//������ýڵ㼰�亢��λ�ã�ͨ����ת����ƽ�����Ӹ߶�
		T->left = delete_avl(x, T->left);
		if (2 == height(T->left) - height(T->right))
		{
			if (x < T->left->element)
				T = single_rotate_withleft(T);
			else
				T = double_rotate_withleft(T);
		}
	}
	else if (x > T->element)
	{	//��������Ϊ���ҵ�ǰ�ڵ�Ԫ�ر�Ԫ��xС
		//��ݹ鵽�ýڵ���������н���ɾ��
		//���ݹ鷵�ص�ĳ�ڵ��ýڵ�ƽ�����Ӹ߶ȳ���2����
		//������ýڵ㼰�亢��λ�ã�ͨ����ת����ƽ�����Ӹ߶�
		T->right = delete_avl(x, T->right);
		if (2 == height(T->right) - height(T->left))
		{
			if (x > T->right->element)
				T = single_rotate_withright(T);
			else
				T = double_rotate_withright(T);
		}
	}
	else if (T->left && T->right)
	{	//���ҵ�Ҫɾ���Ľڵ��Ҹýڵ�����������
		//�򽫸ýڵ�������Ԫ��ֵ��С�Ľڵ㸳ֵ���ýڵ�
		//ͬʱ����������С�Ľڵ�ɾ���ͷſռ�
		AvlTree tempCell = find_min(T->right);
		T->element = tempCell->element;
		T->right = delete_avl(T->element, T->right);
	}
	else
	{	//���ҵ�Ҫɾ���Ľڵ��Ҹýڵ���һ�������ӻ���û�к���
		//���ƶ��ýڵ�ָ�뵽���ҽڵ��൱�ڸ��ڵ�ָ���˸ýڵ�,�ͷŸýڵ�ռ�
		//printf("ɾ���ɹ�\n");
		AvlTree tempCell = T;
		if (NULL == T->left)
			T = T->right;
		else if (NULL == T->right)
			T = T->left;
		free(tempCell);
	}

	return T;
}

/*
�������
*/
void in_order_traverse(AvlTree T)
{
	if (NULL != T)
	{
		in_order_traverse(T->left);
		printf("%d->", T->element);
		in_order_traverse(T->right);
	}
}

/*
�������
*/
void pre_order_traverse(AvlTree T)
{
	if (NULL != T)
	{
		printf("%d->", T->element);
		pre_order_traverse(T->left);
		pre_order_traverse(T->right);
	}
}




void main()
{
	//����ƽ�������
	AvlTree T = NULL;
	T = insert(13, T);
	T = insert(7, T);
	T = insert(5, T);
	T = insert(4, T);
	T = insert(6, T);
	T = insert(10, T);
	T = insert(9, T);
	T = insert(8, T);
	T = insert(12, T);
	T = insert(17, T);
	T = insert(15, T); 
	T = insert(14, T);
	T = insert(19, T);
	/* The constructed AVL Tree would be
	      10
	     /  \
	    7    15
	   / \   / \
	  5   9 13 17
	 /\  /  /\  \
	4  6 8 12 14 19 
	*/

	//�������ƽ�������
	pre_order_traverse(T);
	printf("\n");

	//ɾ������ƽ����Ԫ��
	delete_avl(10, T);
	/* The AVL Tree after deletion of 10
	       12
	       / \
	      7  15
	     / \ / \
	    5  9 13 17
	   /\  /  \   \
	  4  6 8  14  19
	*/
	pre_order_traverse(T);

	return;
}


/*
�Ըó��������д����http://www.geeksforgeeks.org/avl-tree-set-2-deletion/
*/

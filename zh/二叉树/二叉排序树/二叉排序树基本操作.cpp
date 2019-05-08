/****************************************************************
����������Ļ���������������һ�����⣬���ʹ��һ��SearchTree
�������ݲ���ʱ�ᱨ��ʹ��Ϊ��ʼ���ı��������ʹ��һ����ʼ����
SearchTreeʱ��ɾ����ʼ����elementʱ����ִ���ֵ��

�����ѽ��һ����
����ͤ����Ĵ���ֿ��п��������ߵ�BST��ʵ��֪��������һ������
��Ϊdelete���ص��Ǹ��ڵ㣬ɾ�����ڵ�󷵻�ֵ�϶��������⡣
1.���ݲ�������ԭ������Ϊcreate�����е���insertʱû�н���insert
�����ķ��ؽ��������ѭ����NULL == T�����

ע��������˼·��Դ�ڡ����ݽṹ���㷨������C����������
    �ڴ˸�л��ͤ����������˼·
****************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>


//����������ṹ
typedef struct TreeNode
{
	int element;
	struct TreeNode *left;
	struct TreeNode *right;
}*SearchTree, *Position;


SearchTree make_empty(SearchTree T);
Position find(int x, SearchTree T);
Position find_min(SearchTree T);
Position find_max(SearchTree T);
SearchTree insert(int x, SearchTree T);
SearchTree delete_tree(int x, SearchTree T);


/*
����һ�ſ���
ʹ�õݹ�ķ�ʽ���µ��Ͻ����е�ÿһ�����ͷſռ䣬
����NULL�����Գ�ʼ��һ�����ڵ㣬����ʹ�õݹ����ѭ���Ķ��塣
*/
SearchTree make_empty(SearchTree T)
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
�����������find����
ʹ�õݹ�ķ�ʽ����Ԫ��x������TΪ�գ��򷵻�NULL��
��Ԫ��x�ȵ�ǰԪ��С����ݹ����Ԫ�ؽڵ�����������ң�
��Ԫ��x�ȵ�ǰԪ�ش���ݹ����Ԫ�ؽڵ�����������ң�
��󷵻ز��ҵ���Ԫ��x��
*/
Position find(int x, SearchTree T)
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
�����������find_min����
��Ϊ����������������ģ�����ֻ��Ҫ�ݹ�Ĳ�����������
�����Ϊ�գ�����NULL�����������Ϊ�գ�����������Ϊ�գ����ظ�T��
����ݹ���ڸ����������в��ң����صݹ鵽���ĸ�Ԫ�ء�
*/
Position find_min(SearchTree T)
{
	if (NULL == T)
		return NULL;
	if (NULL == T->left)
		return T;
	else
		return find_min(T->left);
}

/*
�����������find_max������
ʹ�÷ǵݹ�ķ�ʽ���в��ҡ�
*/
Position find_max(SearchTree T)
{
	if (NULL != T)
	{
		while (NULL != T->right)
			T = T->right;
	}

	return T;
}

/*
����Ԫ�ص������������
����Ϊ���ڵ㣬��Ϊ�������Ϊ�յĻ���Ҫ���봴��һ���ڵ㲢���أ�
���԰Ѳ�������Ϊfind���������ֲ�������Щ���£��������·�������һ�㡣
*/
SearchTree insert(int x, SearchTree T)
{
	if (NULL == T)		//����Ϊ��������Ҫ����ڵ�ռ䲢��ʼ��
	{
		T = (SearchTree)malloc(sizeof(struct TreeNode));
		if (NULL == T)
		{
			printf("Out of space.\n");
			exit(-1);
		}
		T->element = x;
		T->left = T->right = NULL;
	}
	else if (x < T->element)			//������Ԫ��x�ȵ�ǰ�ڵ�С����ݹ����������������
		T->left = insert(x, T->left);
	else if (x > T->element)			//������Ԫ��x�ȵ�ǰ�ڵ����ݹ����������������
		T->right = insert(x, T->right);

	return T;
}

/*
�����������ɾ������,���ҵ�Ԫ��x�Ľڵ�
��Ҫɾ���ڵ���һƬ��Ҷ��������ɾ������Ҫɾ���ڵ���һ�����ӿ������丸�ڵ����ָ��ɾ����
��Ҫɾ���������������ӣ���������������С�Ľڵ����ýڵ㲢��������ɾ����
*/
SearchTree delete_tree(int x, SearchTree T)
{
	if (NULL == T)
	{	//������Ϊ��û�нڵ����ɾ������ʾ�����˳�����
		printf("Element not found.\n");
		exit(-1);
	}
	else if (x < T->element)
	{	//��������Ϊ���ҵ�ǰ�ڵ�Ԫ�ر�Ԫ��x��
		//��ݹ鵽�ýڵ���������н���ɾ��
		T->left = delete_tree(x, T->left);
	}
	else if (x > T->element)
	{	//��������Ϊ���ҵ�ǰ�ڵ�Ԫ�ر�Ԫ��xС
		//��ݹ鵽�ýڵ���������н���ɾ��
		T->right = delete_tree(x, T->right);
	}
	else if (T->left && T->right)
	{	//���ҵ�Ҫɾ���Ľڵ��Ҹýڵ�����������
		//�򽫸ýڵ�������Ԫ��ֵ��С�Ľڵ㸳ֵ���ýڵ�
		//ͬʱ����������С�Ľڵ�ɾ���ͷſռ�
		SearchTree tempCell = find_min(T->right);
		T->element = tempCell->element;
		T->right = delete_tree(T->element, T->right);
	}
	else
	{	//���ҵ�Ҫɾ���Ľڵ��Ҹýڵ���һ�������ӻ���û�к���
		//���ƶ��ýڵ�ָ�뵽���ҽڵ��൱�ڸ��ڵ�ָ���˸ýڵ�,�ͷŸýڵ�ռ�
		SearchTree tempCell = T;
		if (NULL == T->left)
			T = T->right;
		else if (NULL == T->right)
			T = T->left;
		free(tempCell);
	}

	return T;
}

/*
����������Ϊlen��arr���飬��������Ԫ�ع���һ�ö���������
*/
SearchTree create_searchTree(int *arr, int len)
{
	SearchTree T = NULL;
	int i;
	//��˳������ڵ���뵽������������
	for (i = 0; i < len; i++)
		T = insert(arr[i], T);		//ע��˴���Ҫ���˽��ܷ���ֵ�����ѭ����T == NULL
	return T;
}

/*
�������
*/
void in_order_traverse(SearchTree T)
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
void pre_order_traverse(SearchTree T)
{
	if (NULL != T)
	{
		printf("%d->", T->element);
		pre_order_traverse(T->left);
		pre_order_traverse(T->right);
	}
}




/*
ʹ�������ʼ������һ����������������������������֤�Ƿ��Ƕ���������
*/
void main()
{
	int i;
	int num;
	printf("������ڵ������\n");
	scanf("%d", &num);

	//����num������
	int *arr = (int *)malloc(num * sizeof(int));
	printf("������������%d�����������뻥����ȣ���\n", num);
	for (i = 0; i<num; i++)
		scanf("%d", arr + i);

	//��������������
	SearchTree T = create_searchTree(arr, num);
	printf("��������ö����������Ľ����\n");
	in_order_traverse(T);
	printf("\n");

	//���Ҹ�������
	int key;
	printf("������Ҫ���ҵ�������\n");
	scanf("%d", &key);
	Position p = find(key, T);
	if (p)
		printf("���ҳɹ���\n");
	else
		printf("����ʧ�ܡ���\n");

	//�������������
	printf("������Ҫ�����������");
	scanf("%d", &key);
	if (insert(key, T))
	{
		printf("����ɹ���������������������");
		in_order_traverse(T);
		printf("\n");
	}
	else
		printf("����ʧ�ܣ��ö������������Ѿ���������%d\n", key);

	//ɾ������������
	printf("������Ҫɾ����������");
	scanf("%d", &key);
	if (delete_tree(key, T))
	{
		printf("ɾ���ɹ���������������������");
		in_order_traverse(T);
		printf("\n");
	}
	else
		printf("ɾ��ʧ�ܣ��ö����������в���������%d\n", key);

}
#include "targetver.h"

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>


//�������ڵ�����
typedef struct BTNode
{
	int data;
	struct BTNode *pLeft;
	struct BTNode *pRight;
}BTNode, *BTree;

//����һ�ö�����
BTree create_tree();
//��������ǰ��ǵݹ����
void pre_nonrecursive(BTree);
//��������ǰ��ǵݹ����1
void pre_nonrecursive1(BTree);
//��������ǰ��ǵݹ����2
void pre_nonrecursive2(BTree);
//������������ǵݹ����
void in_nonrecursive(BTree);
//������������ǵݹ����1
void in_nonrecursive1(BTree);
//�������ĺ���ǵݹ����
void post_nonrecursive(BTree);
//�������ĺ���ǵݹ����1
void post_nonrecursive1(BTree);
//���������
int depth(BTree);


//����������ڵ��ջ����
typedef struct TSNode		//TreeStackNode
{
	BTree data;
	struct TSNode *next;
}*PNODE, *PSTACK;

//���ջ
void make_empty(PSTACK);
//�ж�ջ�Ƿ�Ϊ��
int is_empty(PSTACK);
//����ջ
PSTACK create_stack();
//��ջ
void push(BTree, PSTACK);
//����ջ��Ԫ��
BTree top(PSTACK);
//��ջ
void pop(PSTACK);
/*
������ο�����ͤ�������Դ�����Hackbuteer1��CSDNר��,�ڴ��ر��л��
���в�α���δ��ɡ�
*/
#include "stdafx.h"


/*
���ջ
*/
void make_empty(PSTACK S)
{
	if (NULL == S)
	{
		printf("Must use create stack first.\n");
		exit(-1);
	}
	else
		while (!is_empty(S))
			pop(S);
}

/*
�ж�ջ�Ƿ�Ϊ��
*/
int is_empty(PSTACK S)
{
	return S->next == NULL;
}

/*
����ջ
*/
PSTACK create_stack()
{
	PSTACK S = (PSTACK)malloc(sizeof(struct TSNode));
	if (NULL == S)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	S->next = NULL;
	make_empty(S);
	return S;
}

/*
��ջ
*/
void push(BTree val, PSTACK S)
{
	PNODE pNew = (PNODE)malloc(sizeof(struct TSNode));
	if (NULL == pNew)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	pNew->data = val;
	pNew->next = S->next;
	S->next = pNew;
	return ;
}

/*
����ջ��Ԫ��
*/
BTree top(PSTACK S)
{
	if (!is_empty(S))
		return S->next->data;
	
	printf("Empty stack.\n");
	return NULL;
}

/*
��ջ
*/
void pop(PSTACK S)
{
	if (is_empty(S))
	{
		printf("Empty stack.\n");
		exit(-1);
	}
	PNODE p = S->next;
	S->next = p->next;
	free(p);
	return;
}

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
	root->pLeft = create_tree();
	printf("������%d���Һ��ӣ�", val);
	root->pRight = create_tree();

	return root;
}

/*
��������ǰ��ǵݹ����
˼·����ջ��������������ջ������������ѭ��ִ�б�������������
����ʱ����Ҫ��һ������ж��Ƿ�Ϊ��
*/
void pre_nonrecursive(BTree T)
{
	if (!T)
		return;

	PSTACK S = create_stack();	//����һ���������ؼ��ֵ�ջ

	while (T)	//�Ӹ��ڵ㿪ʼ����������ֱ����,ȫ��ѹ��ջ��
	{
		push(T, S);
		printf("%d\t", T->data);
		T = T->pLeft;
	}

	while (!is_empty(S))
	{
		BTree temp = top(S)->pRight;	//ջ��Ԫ��������
		pop(S);							//����ջ��Ԫ��
		while (temp)	//ջ��Ԫ�ش��������������������ͬ�������������·����������򷵻���һ����ͬ������
		{
			printf("%d\t", temp->data);
			push(temp, S);
			temp = temp->pLeft;
		}
	}
}

/*
��������ǰ��ǵݹ����
˼·��ֻҪ��ǰָ�벻Ϊ�ջ���ջ��Ϊ�վ�ִ��ѭ����������
*/
void pre_nonrecursive1(BTree T)
{
	if (!T)
		return;

	PSTACK S = create_stack();	//����һ���������ؼ��ֵ�ջ
	BTree pCur = T;				//��������ָ��ǰ���ʽڵ��ָ��

	//ֱ����ǰ�ڵ�pCurΪNULL��ջ��ʱ��ѭ������
	while (pCur || !is_empty(S))
	{
		//�Ӹ��ڵ㿪ʼ�������ǰ�ڵ㣬��������ջ��
		//ͬʱ��������Ϊ��ǰ�ڵ㣬ֱ����û�����ӣ�ֱ��ǰ�ڵ�ΪNULL
		push(pCur, S);
		printf("%d\t", pCur->data);
		pCur = pCur->pLeft;
		//�����ǰ�ڵ�pCurΪNULL��ջ���գ���ջ���ڵ��ջ��
		//ͬʱ�����Һ���Ϊ��ǰ�ڵ�,ѭ���жϣ�ֱ��pCur��Ϊ��
		while (!pCur && !is_empty(S))
		{
			pCur = top(S);
			pop(S);
			pCur = pCur->pRight;
		}
	}
}

/*
��������ǰ��ǵݹ����2,�������˫ջ����ǰ��
*/
void pre_nonrecursive2(BTree T)
{
	if (!T)
		return ;

	PSTACK S = create_stack();
	push(T, S);

	while (!is_empty(S))
	{
		BTree temp = top(S);
		printf("%d\t", temp->data);
		pop(S);
		if (temp->pRight)
			push(temp->pRight, S);
		if (temp->pLeft)
			push(temp->pLeft, S);
	}
}

/*
������������ǵݹ����
���ַ������ã�Ҫ�������ַ���д����������鷳���п���д������
*/
void in_nonrecursive(BTree T)
{
	if (!T)
		return;

	PSTACK S = create_stack();	//����һ���������ؼ��ֵ�ջ
	BTree pCur = T;				//��������ָ��ǰ���ʽڵ��ָ��

	//ֱ����ǰ�ڵ�pCurΪNULL��ջ��ʱ��ѭ������
	while (pCur || !is_empty(S))
	{
		if (pCur->pLeft)
		{
			//��ǰ�ڵ����������Ϊ�գ�������ջ��������ǰָ��ָ��������
			push(pCur, S);
			pCur = pCur->pLeft;
		}
		else
		{
			//���pCur������Ϊ�գ������pCur�ڵ㣬�������Һ�����Ϊ��ǰ�ڵ㣬�����Ƿ�Ϊ��
			printf("%d\t", pCur->data);
			pCur = pCur->pRight;
			//���Ϊ�գ���ջ���գ���ջ���ڵ��ջ��������ýڵ㣬
			//ͬʱ�������Һ�����Ϊ��ǰ�ڵ㣬�����жϣ�ֱ����ǰ�ڵ㲻Ϊ��
			while (!pCur && !is_empty(S))
			{
				pCur = top(S);
				printf("%d\t", pCur->data);
				pop(S);
				pCur = pCur->pRight;
			}
		}
	}
}

/*
������������ǵݹ����1
*/
void in_nonrecursive1(BTree T)
{
	if (!T)
		return;

	PSTACK S = create_stack();	//����һ���������ؼ��ֵ�ջ
	BTree pCur = T;				//��������ָ��ǰ���ʽڵ��ָ��

	while (pCur != NULL || !is_empty(S))
	{
		while (pCur != NULL)
		{
			push(pCur, S);
			pCur = pCur->pLeft;
		}//while  
		if (!is_empty(S))
		{
			pCur = top(S);
			pop(S);
			printf("%d\t", pCur->data);
			pCur = pCur->pRight;
		}
	}
}

/*
�����ĺ���ǵݹ����
*/
void post_nonrecursive(BTree T)
{
	if (!T)
		return;

	PSTACK S = create_stack();	//����һ���������ؼ��ֵ�ջ
	BTree pCur = T;				//��������ָ��ǰ���ʽڵ��ָ��
	BTree pPre = NULL;			//ָ��ǰһ�������ʵĽڵ�

	while (pCur != NULL || !is_empty(S))
	{
		while (pCur != NULL)	// һֱ������ֱ��Ϊ�� 
		{
			push(pCur, S);
			pCur = pCur->pLeft;
		}
		pCur = top(S);
		// ��ǰ�ڵ���Һ������Ϊ�ջ����Ѿ������ʣ�����ʵ�ǰ�ڵ�   
		if (pCur->pRight == NULL || pCur->pRight == pPre)
		{
			printf("%d\t", pCur->data);
			pPre = pCur;
			pop(S);
			pCur = NULL;
		}
		else
			pCur = pCur->pRight; // ��������Һ���
	}
}

/*
�����ĺ���ǵݹ����,˫ջ��
*/
void post_nonrecursive1(BTree T)
{
	PSTACK S1= create_stack();
	PSTACK S2 = create_stack();
	BTree pCur;					// ָ��ǰҪ���Ľڵ�
	push(T, S1);
	while (!is_empty(S1))		// ջ��ʱ����
	{
		pCur = top(S1);
		pop(S1);
		push(pCur, S2);
		if (pCur->pLeft)
			push(pCur->pLeft, S1);
		if (pCur->pRight)
			push(pCur->pRight, S1);
	}
	while (!is_empty(S2))
	{
		printf("%d\t", top(S2)->data);
		pop(S2);
	}
}

/*
���������
*/
int depth(BTree T)
{
	if (!T)
		return 0;

	int d1 = 1 + depth(T->pLeft);
	int d2 = 1 + depth(T->pRight);

	if (d1 > d2)
		return d1;
	return d2;
}








int main()
{
	printf("����һ�ö�����������-1Ϊ��\n");
	BTree T = create_tree();
	int flag = 1, k;
	printf("                     ������ʵ�ֶ������Ļ���������\n");
	while (flag)
	{
		printf("\n");
		printf("|--------------------------------------------------------------|\n");
		printf("|                    �������Ļ�����������:                     |\n");
		printf("|                        1.�ǵݹ��������                      |\n");
		printf("|                        2.�ǵݹ��������                      |\n");
		printf("|                        3.�ǵݹ�������                      |\n");
		printf("|                        4.�����������                        |\n");
		printf("|                        5.�˳�����                            |\n");
		printf("|--------------------------------------------------------------|\n");
		printf("                        ��ѡ���ܣ�");
		scanf("%d", &k);
		switch (k)
		{
		case 1:
			if (T)
			{
				printf("�ǵݹ���������������Ľ��Ϊ��");
				pre_nonrecursive(T);
				printf("\n");
			}
			else
				printf("          ������Ϊ�գ�\n");
			break;
		case 2:
			if (T)
			{
				printf("�ǵݹ���������������Ľ��Ϊ��");
				in_nonrecursive(T);
				printf("\n");
			}
			else
				printf("          ������Ϊ�գ�\n");
			break;
		case 3:
			if (T)
			{
				printf("�ǵݹ��������������Ľ��Ϊ��");
				post_nonrecursive(T);
				printf("\n");
			}
			else
				printf("          ������Ϊ�գ�\n");
			break;
		case 4:
			if (T)
			{
				printf("��������ȣ�");
				printf("depth is:%d", depth(T));
				printf("\n");
			}
			else
				printf("          ������Ϊ�գ�\n");
			break;
		default:
			flag = 0;
			printf("�������н�������������˳���\n");
		}
	}
    return 0;
}


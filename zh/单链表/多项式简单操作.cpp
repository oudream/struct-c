/*
����ʽ�ļ򵥲���������ʽ�ӷ�������ʽ�˷�
����ʽ�ӷ�ֻ��Ҫ���������ǵ�������ʽ�����Ƚ�������ǰ���ָ�����ӵ����������
����ʽ�˷��������㷨����һ�ֱ�����������ʽ��ˣ�������洢��һ������ʽ�����У���
��������Ѱ����ͬ�Ķ���ʽָ�����,���Ӷ�O��M2N2��.�ڶ�����������ʽ��ˣ���ÿ����
��MNȡ���������Ӷ�ΪO��M2N��.��������������ʽ��ˣ�����ϲ�ͬ������Ӷ�O��MNlogMN��
*/
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>



typedef struct Node				//����ʽ�ṹ
{
	int cofficient;				//ϵ��
	int exponent;				//ָ��
	struct Node * next;
}Polynomial, *PtrPolynomial;


/*
��������ʽ
*/
PtrPolynomial create_polynomial()
{
	int cofficient, exponent;
	PtrPolynomial pHead = (PtrPolynomial)malloc(sizeof(Polynomial));
	PtrPolynomial pCurrent = pHead;
	pHead->next = NULL;
	if (NULL == pHead)
	{
		printf("pHead malloc failed.\n");
		exit(-1);
	}

	while (1)
	{
		printf("Please input the cofficient(quit to input -1):\n");
		scanf("%d", &cofficient);
		if (cofficient == -1)
			break;

		printf("Please input the exponent(quit to input -1):\n");
		scanf("%d", &exponent);
		if (exponent == -1)
			break;

		PtrPolynomial pNew = (PtrPolynomial)malloc(sizeof(Polynomial));
		if (NULL == pNew)
		{
			printf("pNew malloc failed.\n");
			exit(-1);
		}
		pNew->cofficient = cofficient;
		pNew->exponent = exponent;
		pNew->next = pCurrent->next;
		pCurrent->next = pNew;
		pCurrent = pCurrent->next;
	}

	return pHead;
}

/*
������ʽ��ָ�����зǵ�������
*/
void sort_cofficient(PtrPolynomial pHead)
{
	int temp;

	PtrPolynomial p, q;
	for (p = pHead->next; p != NULL; p = p->next)
		for (q = p->next; q != NULL; q = q->next)
		{
			if (p->exponent < q->exponent)
			{
				//������������ʽ��ָ��
				temp = p->exponent;
				p->exponent = q->exponent;
				q->exponent = temp;

				//������������ʽ��ϵ��
				temp = p->cofficient;
				p->cofficient = q->cofficient;
				q->cofficient = temp;
			}
		}
		//if (!swap)	//���δ������������˵���Ƿǵ�����
		//	break;
	return;
}

/*
����ʽ�ӷ�
*/
PtrPolynomial add_polynomial(PtrPolynomial p1, PtrPolynomial p2, PtrPolynomial p3)
{
	PtrPolynomial pCurrent1 = p1->next, pCurrent2 = p2->next, pCurrent = p3;
	
	while (NULL != pCurrent1 && NULL != pCurrent2)
	{
		PtrPolynomial temp;
		if (pCurrent1->exponent > pCurrent2->exponent)		//��һ������ʽ����ϵ�����ڵڶ���
		{
			temp = pCurrent1->next;
			pCurrent1->next = pCurrent->next;
			pCurrent->next = pCurrent1;
			free(pCurrent1);

			//��һ��Ҫ����Ķ���ʽ
			pCurrent1 = temp;
		}
		else if (pCurrent1->exponent < pCurrent2->exponent)	//��һ������ʽ����ϵ��С�ڵڶ���
		{
			temp = pCurrent2->next;
			pCurrent2->next = pCurrent->next;
			pCurrent->next = pCurrent2;
			free(pCurrent2);

			//��һ��Ҫ����Ķ���ʽ
			pCurrent2 = temp;
		}
		else							//��һ������ʽ����ϵ�����ڵڶ���
		{
			int sum = pCurrent1->cofficient + pCurrent2->cofficient;

			//��������ʽϵ����Ӳ�Ϊ0,������洢��pCurrent��
			//���������������ʽ������ƶ�
			if (sum != 0)
			{
				temp = pCurrent1->next;
				pCurrent1->cofficient = sum;
				pCurrent1->next = pCurrent->next;
				pCurrent->next = pCurrent1;

				pCurrent1 = temp;

				temp = pCurrent2->next;
				free(pCurrent2);
				pCurrent2 = temp;
			}
			else
			{
				temp = pCurrent1;
				pCurrent1 = pCurrent1->next;
				free(temp);
				temp = pCurrent2;
				pCurrent2 = pCurrent2->next;
				free(temp);
			}

		}
		pCurrent = pCurrent->next;
	}

	//�����һ������ʽ��Ϊ�գ��������ӵ�pCurrent��
	while (NULL != pCurrent1)
	{
		PtrPolynomial temp;
		temp = pCurrent1->next;
		pCurrent1->next = pCurrent->next;
		pCurrent->next = pCurrent1;
		pCurrent1 = temp;
	}
	//����ڶ�������ʽ��Ϊ�գ��������ӵ�pCurrent��
	while (NULL != pCurrent2)
	{
		PtrPolynomial temp;
		temp = pCurrent2->next;
		pCurrent2->next = pCurrent->next;
		pCurrent->next = pCurrent2;
		pCurrent2 = temp;
	}
	
	return p3;
}

/*
����ʽ�˷�����һ�֣�
*/
PtrPolynomial multi_polynomial(PtrPolynomial p1, PtrPolynomial p2, PtrPolynomial p3)
{
	PtrPolynomial pCurrent1, pCurrent2;
	for(pCurrent1=p1->next;NULL != pCurrent1;pCurrent1=pCurrent1->next)
		for (pCurrent2 = p2->next; NULL != pCurrent2; pCurrent2 = pCurrent2->next)
		{
			//�������洢�ռ�
			PtrPolynomial pResult = (PtrPolynomial)malloc(sizeof(Polynomial));
			pResult->next = NULL;
			if (NULL == pResult)
			{
				printf("pResult malloc failed.");
				exit(-1);
			}

			//���ж���ʽ�������
			PtrPolynomial pCurrent=p3;
			pResult->cofficient = pCurrent1->cofficient * pCurrent2->cofficient;
			pResult->exponent = pCurrent1->exponent + pCurrent2->exponent;
			pResult->next = pCurrent->next;
			pCurrent->next = pResult;
			pCurrent = pCurrent->next;
		}

	//��������ʽ�˻��������
	//��exponentָ����ͬ����ʽ�ϲ�
	PtrPolynomial pTraverse, pSearch, pOneResult;
	for (pTraverse = p3->next; NULL != pTraverse; pTraverse = pTraverse->next)
	{
		pOneResult = pTraverse;
		for (pSearch = pTraverse; NULL != pSearch; pSearch = pSearch->next)
		{
			if (NULL != pSearch->next && pSearch->next->exponent == pOneResult->exponent)
			{
				PtrPolynomial temp;
				pOneResult->cofficient = pOneResult->cofficient + pSearch->next->cofficient;
				temp = pSearch->next;
				pSearch->next = temp->next;
				free(temp);
			}
		}
		printf("cofficient=%d, exponent=%d\n", pOneResult->cofficient, pOneResult->exponent);
	}
	
	return p3;
}




void main()
{
	PtrPolynomial p1, p2, p3;
	p3 = (PtrPolynomial)malloc(sizeof(Polynomial));
	p3->next = NULL;

	//��������ʽ
	printf("������һ������ʽ\n");
	p1 =create_polynomial();
	printf("�����ڶ�������ʽ\n");
	p2 = create_polynomial();

	//����ʽ����
	printf("��һ������ʽ����\n");
	sort_cofficient(p1);
	printf("�ڶ�������ʽ����\n");
	sort_cofficient(p2);

	//����ʽ�����㣬ע�����������㲻��ͬʱ���У���Ҫע�͵���һ��
	printf("����ʽ�ӷ�\n");
	PtrPolynomial result= add_polynomial(p1, p2, p3), show=result->next;
	while (NULL != show)
	{
		printf("%dX%d+", show->cofficient, show->exponent);
		show = show->next;
	}
	printf("\n");

	printf("����ʽ�˷�\n");
	PtrPolynomial result2 = multi_polynomial(p1, p2, p3), show2=result2->next;
	while (NULL != show2)
	{
		printf("%dX%d+", show2->cofficient, show2->exponent);
		show2 = show2->next;
	}
	printf("\n");
}

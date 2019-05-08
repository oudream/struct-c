/**********************************************************************
��׺���ʽ��ֵ
**********************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char oprArray[10] = { '+', '-', '*', '/', '(', ')' };	//����������


typedef struct StackChar
{
	char c;
	struct StackChar *next;
}*SC;			//������ջָ�����

typedef struct StackFloat
{
	float f;
	struct StackFloat *next;
}*SF;			//������ջָ�����


				/*
				����������ջ
				*/
SC create_cstack()
{
	//����ջ�ռ�
	SC S = (SC)malloc(sizeof(struct StackChar));
	if (NULL == S)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	S->next = NULL;

	return S;
}

/*
����������ջ
*/
SF create_fstack()
{
	//����ջ�ռ�
	SF S = (SF)malloc(sizeof(struct StackFloat));
	if (NULL == S)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	S->next = NULL;

	return S;
}

/*
��������ջ
*/
void c_push(char c, SC S)
{
	//�����ջԪ�ؿռ��ʼ��
	//opr�������������
	SC opr = (SC)malloc(sizeof(struct StackChar));
	if (NULL == opr)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	opr->c = c;
	opr->next = S->next;
	S->next = opr;
}

/*
��������ջ
*/
void f_push(float f, SF S)
{
	//�����ջԪ�ؿռ��ʼ��
	//opr�������������
	SF opr = (SF)malloc(sizeof(struct StackFloat));
	if (NULL == opr)
	{
		printf("Out of space.\n");
		exit(-1);
	}
	opr->f = f;
	opr->next = S->next;
	S->next = opr;
}

/*
��ջ������ջ��Ԫ��
*/
char c_pop(SC S)
{
	//�ж�ջ�Ƿ�Ϊ��
	if (NULL == S->next)
		printf("The stack is empry.\n");

	//����ջ��Ԫ�أ��ͷſռ�
	SC temp = S->next;
	char c = temp->c;
	S->next = temp->next;
	free(temp);

	return c;
}

/*
��ջ������ջ��Ԫ��
*/
float f_pop(SF S)
{
	//�ж�ջ�Ƿ�Ϊ��
	if (NULL == S->next)
		printf("The stack is empry.\n");

	//����ջ��Ԫ�أ��ͷſռ�
	SF temp = S->next;
	float f = temp->f;
	S->next = temp->next;
	free(temp);

	return f;
}

/*
�ж��ǲ��������ǲ�����
*/
int is_ptr(char element)
{
	int i = 0;
	while (oprArray[i])
	{
		if (element == oprArray[i])
			return 1;
		i++;
	}
	return 0;
	//int i;
	//for (i = 0; i < 6; i++)
	//	if (element == oprArray[i])
	//		return 1;
	//return 0;
}

//������������������
float operate(float a, char opr, float b)
{
	float result;
	switch (opr)
	{
	case '+': return result = a + b;
	case '-': return result = a - b;
	case '*': return result = a * b;
	case '/': return result = a / b;
	default: return 0;
	}
}

/*
�ָ��ַ���,����ָ������
*/
char ** splite(char *expression)
{
	char *token = strtok(expression, ",");
	char static *arrExpression[100];

	int i = 0;
	while (NULL != token)
	{
		arrExpression[i] = token;
		//printf("splite is %s\n", arrExpression[i]);
		token = strtok(NULL, ",");
		i++;
	}

	return arrExpression;
}

/*
���ر��ʽ����
*/
int exp_len(char *expression)
{
	//�����ַ���
	//��ֹpostfix��������ʱ��splite����������ͻ
	//���³���������
	char rl[100];
	strcpy(rl, expression);

	//�ָ��ַ���
	//ÿ�ηָ�һ��count��һ
	char *token = strtok(rl, ",");
	int count = 0;
	while (NULL != token)
	{
		count++;
		token = strtok(NULL, ",");
	}

	return count;
}

/*
�����׺���ʽ
*/
float postfix(char *expression)
{
	float a, b;								//��������a��b��
	float tpResult;							//��ʱ������
	char opr;								//������
	int count = exp_len(expression);			//��ñ��ʽ�ַ����鳤��
	char **elements = splite(expression);	//����ָ��ָ����ʽ�ַ�����
	SF fStack = create_fstack();			//��ʼ��������ջ

											//��׺���ʽ����
	int i;
	for (i = 0; i < count; i++)
	{
		//printf("�����%s\n", *&elements[3]);
		if (!is_ptr(**&elements[i]))				//����ǲ��������ջ
		{
			printf("%d\n", atoi(*&elements[i]));
			f_push(atoi(*&elements[i]), fStack);
		}
		else										//��������ջ��������ջ
		{
			a = f_pop(fStack);
			b = f_pop(fStack);
			opr = **&elements[i];
			tpResult = operate(a, opr, b);
			f_push(tpResult, fStack);
		}
	}

	float x = f_pop(fStack);
	return x;
}

void main()
{
	char exp[100];
	float result;

	printf("�����������Ĳ��������ŵĺ�׺���ʽ(������֮�䶺�ŷָ�)��\n");
	scanf("%s", &exp);
	printf("������ı��ʽΪ��%s\n", exp);
	result = postfix(exp);
	printf("��׺���ʽ������Ϊ%f\n", result);
}
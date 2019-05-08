/**********************************************************************
���ʽ��ֵ,�����������׺���ʽ����׼��ת��Ϊ��׺���ʽ������ֵ
˼·������׸����Դ�ڡ����ݽṹ���㷨������C����������54ҳ
**********************************************************************/
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


char oprArray[6] = { '+', '-', '*', '/', '(', ')' };	//����������


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
�ж��ַ�ջ�Ƿ�Ϊ��
*/
int is_cstack_empty(SC S)
{
	return S->next == NULL;
}

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
char c_top_pop(SC S)
{
	//�ж�ջ�Ƿ�Ϊ��
	if (NULL == S->next)
		printf("When top and pop the stack is empry.\n");

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
float f_top_pop(SF S)
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
��ջ����
*/
void c_pop(SC S)
{
	//�ж�ջ�Ƿ�Ϊ��
	if (NULL == S->next)
		printf("When pop, the stack is empry.\n");

	//����ջ��Ԫ�أ��ͷſռ�
	SC temp = S->next;
	S->next = temp->next;
	free(temp);

	return;
}

/*
����ջ��Ԫ��
*/
char c_top(SC S)
{
	if (!is_cstack_empty(S))
		return S->next->c;
	else
		return '0';
}

/*
�ж��ַ�ջ���Ƿ���ĳ��Ԫ��
*/
int opr_in_cstack(char c, SC S)
{
	SC p = S->next;
	while (NULL != p)
	{
		if (c == p->c)
			return 1;
		p = p->next;
	}

	return 0;
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
}

/*
������������������
*/
float operate(float a, char opr, float b)
{
	float result;
	switch(opr)
	{
		case '+': return result = a + b;
		case '-': return result = a - b;
		case '*': return result = a * b;
		case '/': return result = b / a;
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
���غ�׺���ʽ����
*/
int postfix_len(char *expression)
{	//�����ַ���
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
���ر��ʽ����
*/
int exp_len(char *expression)
{
	return strlen(expression);
}

/*
�ж��������������ȼ��������ȼ���Ĳ�����,����e��ʾ���
֮�󿴵���ϣ��ʱ���Ƿ�����ù�ϣ�ķ�ʽ���ұȽ����ȼ�
*/
char prio_operator(char opr1, char opr2)
{
	//�������������������ȼ�
	int level1, level2;

	//��һ�����������ȼ�
	if (opr1 == '+' || opr1 == '-')
		level1 = 1;
	if (opr1 == '*' || opr1 == '/')
		level1 = 2;
	if (opr1 == '(' || opr1 == ')')
		level1 = 3;
	//�ڶ������������ȼ�
	if (opr2 == '+' || opr2 == '-')
		level2 = 1;
	if (opr2 == '*' || opr2 == '/')
		level2 = 2;
	if (opr2 == '(' || opr2 == ')')
		level2 = 3;

	//�Ƚ����ȼ�
	if (level1 < level2)
		return opr2;
	if(level1 > level2)
		return opr1;
	if(level1 == level2)	//equal���
		return 'e';
}

/*
�����׺���ʽ
*/
float postfix(char *expression)
{
	float a, b;		//��������a��b
	float tpResult;		//��ʱ������
	char opr;		//������

	int count = postfix_len(expression);	//��ñ��ʽ�ַ����鳤��
	char **elements = splite(expression);	//����ָ��ָ����ʽ�ַ�����

	SF fStack = create_fstack();		//��ʼ��������ջ

	//��׺���ʽ����
	int i;
	for (i = 0; i < count; i++)
	{
		if (!is_ptr(**&elements[i]))	//����ǲ��������ջ
		{
			printf("%d\n", atoi(*&elements[i]));
			f_push(float(atoi(*&elements[i])), fStack);
		}
		else		//��������ջ��������ջ
		{
			a = f_top_pop(fStack);
			b = f_top_pop(fStack);
			opr = **&elements[i];
			tpResult = operate(a, opr, b);
			f_push(tpResult, fStack);
		}
	}

	float x = f_top_pop(fStack);
	return x;
}

/*
���ʽ��ֵ
����2��ջ�ṹ��ú�׺���ʽ��ͨ����׺���ʽ��������
*/
float evalute_expression(char *expression)
{
	char prioOpr;					//���ȼ��ߵĲ�����
	char postExpression[100];			//��׺���ʽ
	char *postExp = postExpression;			//��׺���ʽָ��

	int count = exp_len(expression);		//��ñ��ʽ�ַ����鳤��

	SC cStack = create_cstack();			//��ʼ��������ջ

	//���ʽ����
	int i;
	for (i = 0; i < count; i++)			//ѭ���������ʽÿ���ַ�
	{
		if (!is_ptr(expression[i]))		//����ǲ��������䱣������׺���ʽ
		{
			*postExp++ = expression[i];
			if(is_ptr(expression[i+1]) || expression[i + 1] == '\0')
				*postExp++ = ',';
			continue;
		}

		if (!is_cstack_empty(cStack))		//���������ջ��Ϊ�ղ����ǲ�����
		{
			char popOpr;	//��ջ����������

			//�Ƚ�ջ���������͵�ǰ�����������ȼ�
			prioOpr = prio_operator(expression[i], c_top(cStack));
			if (prioOpr == 'e')		//�����ǰ���������ȼ���ջ���������������ջ
			{
				c_push(expression[i], cStack);
				continue;
			}

			if (prioOpr == expression[i] && ')' != expression[i])		//�����ǰ���������ȼ������ջ
			{
				c_push(expression[i], cStack);
				continue;
			}

			if (prioOpr == expression[i] && ')' == expression[i])		//�����ǰ���������ȼ�����Ϊ��������ջ�����������ݵ���׺���ʽ
			{
				while ('(' != c_top(cStack))
				{
					popOpr = c_top_pop(cStack);
					*postExp++ = popOpr;
					*postExp++ = ',';
				}
				//������������
				c_pop(cStack);
				continue;
			}

			if (prioOpr == c_top(cStack) && opr_in_cstack('(', cStack))	//�����ǰ���������ȼ�����ջ֮ǰ�С��������ţ��������ջ
			{
				c_push(expression[i], cStack);
				continue;
			}

			if (prioOpr == c_top(cStack))	//�����ǰ���������ȼ����򽫵�ջ����������׺���ʽ,ֱ����ǰ���������ȼ����ڵ���ջ��
			{
				while ('0' != c_top(cStack) && c_top(cStack) == prio_operator(expression[i], c_top(cStack)))//������!!!!!!!!!
				{
					popOpr = c_top_pop(cStack);
					*postExp++ = popOpr;
					*postExp++ = ',';
				}
				c_push(expression[i], cStack);
				continue;
			}
		}
		else	//���������ջΪ�գ�ֱ�ӽ�ջ
		{
			c_push(expression[i], cStack);
			continue;
		}
	}

	//���ջ��Ϊ�ս�ջ���ַ�����postExp��
	//�����ַ�����β
	while (!is_cstack_empty(cStack))
	{
		*postExp++ = c_top_pop(cStack);
		*postExp++ = ',';
	}
	*postExp++ = '\0';

	printf("postfix is:%s\n", postExpression);
	float result = postfix(postExpression);

	return result;
}







void main()
{
	char exp[100];
	float result;

	//��׺���ʽ
	//printf("�����������Ĳ��������ŵĺ�׺���ʽ(������֮�䶺�ŷָ�)��\n");
	//scanf("%s", &exp);
	//printf("������ı��ʽΪ��%s\n", exp);
	//result = postfix(exp);
	//printf("��׺���ʽ������Ϊ%f\n", result);
	
	//��׺����׼�����ʽ
	printf("������Ҫ����ı��ʽ\n");
	scanf("%s", &exp);
	printf("������ı��ʽΪ��%s\n", exp);
	result = evalute_expression(exp);
	printf("��׺���ʽ������Ϊ%f\n", result);

	//����
	//printf("������Ҫ����ı��ʽ\n");
	//scanf("%s", &exp);
	//printf("������ı��ʽΪ��%s\n", exp);
	//evalute_expression(exp);
}

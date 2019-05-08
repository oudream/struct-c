/*
�������
*/
void printArray(int *array, int N)
{
	int i;
	for (i = 0; i < N; i++)
	{
		printf("%d", array[i]);
	}
	printf("\n");
}

/*
��������
*/
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

/*
ȫ���к����ݹ�ʵ�֣�δ�����ظ�Ԫ�������
*/
void permute(int *array, int i, int length) 
{
	//�ݹ�ĳ��ڣ�û��Ԫ�ؿ��Խ���
	if (length == i)
	{	
		printArray(array, length);
		return;
	}

	//�ݹ齻��
	int j;
	for (j = i; j < length; j++) 
	{
		swap(array + i, array + j);		//��һ��λ�õ�Ԫ�طֱ������λ���ϵ�Ԫ�ؽ���
		permute(array, i + 1, length);	//�ݹ������һ��λ�÷ֱ������λ���ϵ�Ԫ�ؽ���
		swap(array + i, array + j);		//���������״̬
	}
	return;
}

/*
�жϺ����Ƿ��ظ����ֵ�����
*/
int is_swap(int start, int *array, int end)
{
	int i;
	for (i = start; i < end; i++)
		if (array[i] == array[end])
			return 0;
	return 1;
}

/*
ȫ���к����ݹ�ʵ��
ȥ���ظ�����ȥ�ص�ȫ���о��Ǵӵ�һ��������ÿ�����ֱ�����������ظ����ֵ����ֽ���
*/
void permute2(int *array, int i, int length)
{
	//�ݹ�ĳ��ڣ�û��Ԫ�ؿ��Խ���
	if (length == i)
	{
		printArray(array, length);
		return;
	}
	//�ݹ齻��
	int j;
	for (j = i; j < length; j++)
	{
		if (is_swap(i, array, j))
		{
			swap(array + i, array + j);		//��һ��λ�õ�Ԫ�طֱ������λ���ϵ�Ԫ�ؽ���
			permute2(array, i + 1, length);	//�ݹ������һ��λ�÷ֱ������λ���ϵ�Ԫ�ؽ���
			swap(array + i, array + j);		//���������״̬
		}
	}
}




//�����С
#define MAX_NUM 20
//�洢��ϣ�λ��0�����Ҫѡ���ĸ�λ��
int comb[MAX_NUM];

/*
����㷨�ĵݹ�ʵ��

˼·��
��ȷ���ݹ�Ĺ�ģ������C��5��3�����Ǵ�5��ʼ����һ����Ϊ5���ڶ�������Ҫ��1��2��3��4��ѡ����C��4��2����
����ڶ�����Ϊ4����ô����������Ҫ��1��2��3��ѡȡ��C��3��1����
����ڶ�����Ϊ3����ô����������Ҫ��1��2��4��ѡȡ��C��2��1����
����ڶ�����Ϊ2����ô����������Ҫ��1��ѡȡ��C��1��1����
֮��ʹ�4��ʼ�ظ��������̣�ֱ��3������2��1�Ͳ���Ҫִ���ˡ��������ݹ�Ĵ������Ǵ�5��3��

�ܽ᣺��ʼ��ʱ���Ҫ�뵽��Ϻ����еĲ�ͬ��������ϵ�λ����ͬ���ǲ���ͬ���е�����ͨ����������ý����������Ҫ�µĴ洢�ռ䡣
*/
void combination(int m, int n)//��n������ѡ��m��
{
	int i, j;

	//���ݹ����
	for (int i = n; i >= m; i--)
	{
		//�ô洢�����ݽṹ���汾�����е�һ��λ��
		comb[m] = i;
		//��С��ģ
		if (m > 1)
			combination(m - 1, i - 1);
		else
		{
			//̽�⵽һ����ϣ����һ�����
			for (j = comb[0]; j > 0; j--)
				printf("%d", comb[j]);

			printf("\n");
		}
	}

	return;
}






int main()
{
    comb[0] = 3;
    combination(comb[0], 8);
    return 0;
}

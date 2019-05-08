/*
ϣ��������С��������

˼·��ͨ���Ƚ����һ�������Ԫ������ɹ�����ͻ������2�η�ʱ��硣

������ʹ��һ�����У�h1��h2��...ht��ֻҪh1����1����ʹ��hk��һ������󣬶���ÿһ��i������A[i]<=A[i+hk]�����м��hk��Ԫ�ض�
      ����������ķ�ʽ����ֱ�Ӳ�������ht=N/2

�ܽ᣺ϣ�������ʱ�临�Ӷ��������������У��ΪO��N2�������ΪO��N��
*/

//hk�����һ�������ǣ�����hk��hk-1��...N-1�е�ÿһ��λ��i�������ϵ�Ԫ�طŵ�i,i-hk,i-2hk...�м����ȷλ����
void ShellSort(ElementType A[], int N)
{
	int i, j, increment;
	ElementType tmp;

	for(increment = N/2; increment > 0; increment /= 2)//��ѭ������Ϊ��С�����ĸ���
		for (i = increment; i < N; i++)
		{	//������λ��i��ʼ�������ƶ�λ�ã�
			//�ɺ���ǰ�����������С������λ��ΪҪ��������ݣ�
			//����ֱ�Ӳ��������˼���������
			tmp = A[i];
			for (j = i; j >= increment; j -= increment)
				if (A[j - increment] > tmp)
					A[j] = A[j - increment];
				else
					break;
			A[j] = tmp;
		}
}














int main()
{
	int i;
	int a[10] = { 2, 4, 67, 12, 43, 78, 5, 3, 8, 65 };

	ShellSort(a, 10);
	for (i = 0; i < 10; i++)
		printf("%d,", a[i]);

    return 0;
}


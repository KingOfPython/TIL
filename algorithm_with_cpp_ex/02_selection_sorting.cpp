// 제자리 정렬 알고리즘 중 하나
// 첫번째 부터 마지막 까지 차례대로 비교를 한다. 
// 비효율적인 알고리즘
// 10 * (10+1) / 2 = 55
// 최소 55번의 비교 연산을 하게 된다
// ==> N * (N + 1) / 2
// ==> O(N ^ 2) 		

#include <stdio.h>

int main(void)
{
	int arr[10] = {1, 10, 5, 8, 7, 6, 4, 3, 2, 9};
	
	for(auto i = 0; i < 10; i++)
	{
		int min = 0;
		int index = 0;
		
		min = 9999;		// 모든 원소보다 가장 큰 숫자
		for(auto j = i; j < 10; j++)
		{
			if(min > arr[j])
			{
				min = arr[j];
				index = j;
			}
		}
		
		int temp = arr[i];
		arr[i] = arr[index];
		arr[index] = temp;
	}
	
	for(auto i=0; i<10; i++)
	{
		printf("%d ", arr[i]);
	}
	
	return 0;
}
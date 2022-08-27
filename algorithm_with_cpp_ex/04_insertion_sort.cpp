// 삽입 정렬
// 무조건 위치를 바꾸는 방식이 아닌 필요할 때만 위치를 바꾸게 된다.

// 시간 복잡도는  O(N ^ 2) 으로, 버블정렬, 선택정렬과 동일하다.
// 거의 정렬 된 상태라면, 어떤 알고리즘 보다 빠를 수 있다.

#include <stdio.h>

int main(void)
{
	int arr[10] = {1, 10, 5, 8, 7, 6, 4, 3, 2, 9};
	
	for(int i = 0; i < 9; i++)
	{
		int j = i;
		while(arr[j] > arr[j+1])
		{
			int temp = arr[j];
			arr[j] = arr[j+1];
			arr[j+1] = temp;
			j--;
		}
	}
	
	for(int i=0; i<10; i++)
	{
		printf("%d ", arr[i]);
	}

	return 0;
}
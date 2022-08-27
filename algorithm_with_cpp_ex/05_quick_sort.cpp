// 퀵 정렬
// 분할 정복 알고리즘

// 평균 속도가 O(N * logN) 으로 빠르게 동작한다.

// 퀵 정렬은 특정한 값을 기준으로 큰숫자와 작은 숫자를 교환 한뒤에 배열을 반으로 나눈다
// 일반 적으로 퀵정렬에서는 기준 값이 있다.
// 기준 값을 피벗(pivot) 이라고 하는데, 이는 보통 첫번째 값을 사용한다

#include<stdio.h>

int number = 10;
int data[10] = { 1, 10, 5, 8, 7, 6, 4, 3, 2, 9 };

void QuickSort(int data[], int start, int end)
{
	if (start >= end)	// 원소가 1개 인경우
	{
		return;
	}

	int key = start;		// 키는 첫번째 원소
	int i = start + 1;		// 키 값의 오른쪽 부터
	int j = end;			// 마지막 값 (오른쪽 부터 키 값보다 작은 값을 찾기 위함)
	int temp;

	while (i <= j)	// 엇갈리때 까지 반복
	{
		while (data[i] <= data[key]) // 키 값보다 큰 값을 만날 때 까지 오른쪽으로 이동
		{
			i++;
		}
		while (data[j] >= data[key] && j > start)	// 키 값보다 작은 값을 만날 때 까지 왼쪽으로 이동
		{
			j--;
		}
		if (i > j) // 엇갈린 상태면 키 값과 교체
		{
			temp = data[j];
			data[j] = data[key];
			data[key] = temp;
		}
		else
		{
			temp = data[j];
			data[j] = data[i];
			data[i] = temp;
		}
	}

	QuickSort(data, start, j - 1);
	QuickSort(data, j + 1, end);
}

int main(void)
{
	QuickSort(data, 0, number - 1);

	for (int i = 0; i < 10; i++)
	{
		printf("%d ", data[i]);
	}

	return 0;
}
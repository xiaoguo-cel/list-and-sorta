#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 100000


void bubble_sort(int* data, size_t n, int order);
void select_sort(int* data, size_t n, int order);
void insert_sort(int* data, size_t n, int order);
void quick_sort(int* data, size_t n, int order);


int main()
{
	srand(time(NULL));

	//int nums[] = {3, 7, 1, 2, 2, 5, 3, 6, 3, 4};
	int* nums1 = malloc(N * sizeof(int));
	int* nums2 = malloc(N * sizeof(int));
	int* nums3 = malloc(N * sizeof(int));
	int* nums4 = malloc(N * sizeof(int));

	if(nums1 == NULL || nums2 == NULL || nums3 == NULL || nums4 == NULL)
	{
		perror("malloc fail");
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < N; i++)
	{
		// 常规情况
		//nums1[i] = nums2[i] = nums3[i] = nums4[i] = rand() % (99999 - 11111) + 11111 + 1;
		// 最好情况
		//nums1[i] = nums2[i] = nums3[i] = nums4[i] = i;
		
		// 最坏情况
		nums1[i] = nums2[i] = nums3[i] = nums4[i] = N - i;
	}
	
	time_t start_time, end_time;

	
	printf("快速排序算法开始工作...\n");

	time(&start_time);
	quick_sort(nums1, N, 0);	
	time(&end_time);

	printf("快速排序算法完成工作（耗时 %ld 秒）！\n", end_time - start_time);
	

	printf("\n插入排序算法开始工作...\n");

	time(&start_time);
	insert_sort(nums2, N, 0);	
	time(&end_time);

	printf("插入排序算法完成工作（耗时 %ld 秒）！\n", end_time - start_time);


	printf("\n选择排序算法开始工作...\n");

	time(&start_time);
	select_sort(nums3, N, 0);	
	time(&end_time);

	printf("选择排序算法完成工作（耗时 %ld 秒）！\n", end_time - start_time);


	printf("\n冒泡排序算法开始工作...\n");

	time(&start_time);
	bubble_sort(nums4, N, 0);	
	time(&end_time);

	printf("冒泡排序算法完成工作（耗时 %ld 秒）！\n", end_time - start_time);


	/*
	for(int i = 0; i < N; i++)
	{
		printf("%d ", nums[i]);
	}	

	printf("\n");
	*/

	free(nums1);
	free(nums2);
	free(nums3);
	free(nums4);

	return 0;
}



void bubble_sort(int* data, size_t n, int order)  // order 为 0 表示升序，1 表示降序
{
	int i, j;
	int tmp;
	int flag;

	for(i = 0; i < n - 1; i++)  // 轮循环
	{
		flag = 1;

		for(j = 0; j < n - i - 1; j++)  // 每轮内部的比较和交换操作循环
		{
			if(order ? data[j] < data[j + 1] : data[j] > data[j + 1])
			{
				// 交换
				tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;

				flag = 0;
			}
		}

		if(flag) break;
	}

}



void select_sort(int* data, size_t n, int order)  // order 为 0 表示升序，1 表示降序
{
	int i, j, k;
	int tmp;

	for(i = 0; i < n - 1; i++)   // 轮的循环
	{
		k = i;

		for(j = i + 1; j < n; j++)  // 每一轮内部比较操作的循环
		{
			if(order ? data[j] > data[k] : data[j] < data[k]) k = j;
		}

		if(k != i)
		{
			tmp = data[k];
			data[k] = data[i];
			data[i] = tmp;
		}
	}
}



void insert_sort(int* data, size_t n, int order)  // order 为 0 表示升序，1 表示降序
{
	int i, j;
	int k;

	for(i = 1; i < n; i++)
	{
		k = data[i];

		for(j = i - 1; j >= 0; j--)
		{
			if(order ? data[j] >= k : data[j] <= k) break;

			data[j + 1] = data[j];
		}

		data[j + 1] = k;
	}
}



void quick_sort(int* data, size_t n, int order)  // order 为 0 表示升序，1 表示降序
{
	// 一趟快速排序处理
	int i = 0, j = n - 1, k = data[0];

	if(n < 2) return;

	while(i < j)
	{
		while(i < j && (order ? data[j] <= k : data[j] >= k)) j--;

		data[i] = data[j];

		while(i < j && (order ? data[i] >= k : data[i] <= k)) i++;

		data[j] = data[i];
	}

	data[i] = k;

	// 递归处理
	quick_sort(data, i, order);
	quick_sort(data + i + 1, n - i - 1, order);
}


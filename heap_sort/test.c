#include<stdio.h>
#include<stdlib.h>

void Heapadjustdown(int *arr,int start,int end)
{
	int temp = arr[start];
	int i = 2*start + 1;
	while(i <= end)
	{
		if(i+1 <= end && arr[i+1] > arr[i])
			i++;
		if(arr[i] <= temp)
			break;
		arr[start] = arr[i];
		start = i;
		i = 2*start + 1;
	}
	arr[start] = temp;
}

void Heap_sort(int* arr,int len)
{
	int i;
	for(i = len/2 -1;i>=0;i--)
		Heapadjustdown(arr,i,len-1);

	for(i=len-1; i>0; i--)
	{
		int temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;
		Heapadjustdown(arr,0,i-1);
	}
}

int main()
{
	int num;
	printf("请输入要排序的元素的个数: ");
	scanf("%d",&num);

	int i;
	int *arr = (int*)malloc(num*sizeof(int));
	printf("请依次输入这%d个元素（必须为整数）:",num);
	for(i=0;i<num;i++)
	{
		Heap_sort(arr,8);
		//printf("%d",arr[i]);
	}
	printf("\n");
	free(arr);
	arr = 0;
	return 0;
}






















#include<stdio.h>

int partion(int array[], int start, int end)
{
	int i;
	int pIndex = start;
	int pivot = array[end];

	for(i= start; i < end; i++){
		if(array[i] <= pivot){
			int temp = array[pIndex];
			array[pIndex] = array[i];
			array[i] = temp;
			pIndex++;
		}
	}	
	int temp = array[pIndex]; 
	array[pIndex] = array[end];
	array[end] = temp;

	return pIndex;
}

void quickSort(int array[], int start, int end)
{
	if( start < end){
		int pIndex = partion(array, start, end);
		quickSort(array, start, pIndex-1);
		quickSort(array, pIndex+1, end);
	}
}

int main()
{
	int i;
	int input[] = {1,5,4,8,2,5,8,9,5,6,7,8};
	quickSort(input, 0, 11);

	for(i=0; i<11; i++){
		printf("%d ", input[i]);
	}
	printf("\n");
	
	return 0;
}

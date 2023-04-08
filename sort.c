#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void swap(int* a, int* b)
{
 
    int temp = *a;
 
    *a = *b;
 
    *b = temp;
}
 
void heapify(int arr[], int n, int i)
{
 
    int max = i;
 
    int left = 2 * i + 1;
 
    int right = 2 * i + 2;
 
    if (left < n && arr[left] > arr[max])
 
        max = left;
 
    if (right < n && arr[right] > arr[max])
 
        max = right;
 
    if (max != i) {
 
        swap(&arr[i], &arr[max]);
 
        heapify(arr, n, max);
    }
}

void heapSort(int arr[], int n)
{
 
    for (int i = n / 2 - 1; i >= 0; i--)
 
        heapify(arr, n, i);
 
    for (int i = n - 1; i >= 0; i--) {
 
        swap(&arr[0], &arr[i]);
 
        heapify(arr, i, 0);
    }
}

void merge(int pData[], int l, int m, int r) {
    int a, b, c;
    int d1 = m - l + 1;
    int d2 = r - m;
 
    int L[d1], R[d2];
 
    for (a = 0; a < d1; a++)
        L[a] = pData[l + a];
    for (b = 0; b < d2; b++)
        R[b] = pData[m + 1 + b];
 
    a = 0;
    b = 0;
    c = l;
    while (a < d1 && b < d2) {
        if (L[a] <= R[b]) {
            pData[c] = L[a];
            a++;
        }
        else {
            pData[c] = R[b];
            b++;
        }
        c++;
    }
 
    while (a < d1) {
        pData[c] = L[a];
        a++;
        c++;
    }
 
    while (b < d2) {
        pData[c] = R[b];
        b++;
        c++;
    }
}


// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(pData, l, m);
        mergeSort(pData, m + 1, r);
        merge(pData, l, m, r);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt", "input4.txt" };
	
	for (i=0;i<4;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Heap Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		heapSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}

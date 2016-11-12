#include <stdio.h>
#include <stdlib.h>
#define LEN 100000

long merge_and_count(int *, int, int, int);
long sort_and_count(int*, int, int);

int main(void){
	FILE* input = fopen("inversion-array.txt", "r");
	FILE* debug = fopen("debug.txt", "w");
	int arr[LEN], i;
	for(i = 0; i < LEN; ++i)
		fscanf(input, "%d", &arr[i]);
	long ans = sort_and_count(arr, 0, LEN-1);
	printf("Number of inversions: %ld\n", ans);
	
	//DEBUG
	for(i = 0; i < LEN; ++i)
		fprintf(debug, "%d\n", arr[i]);

	return 0;
}

long merge_and_count(int *arr, int p, int q, int r){
	long split_inversions = 0;
	int l_len = q - p + 1;
	int r_len = r - q;
	int *left = (int*)malloc(sizeof(int) * l_len);
	int *right = (int*)malloc(sizeof(int) * r_len);

	if(left == NULL || right == NULL){
		fprintf(stderr, "%s\n", "Malloc error in merge_and_count subroutine.");
		exit(1);
	}

	int i, j, k;
	for(i = 0; i < l_len; ++i)
		left[i] = arr[p+i];
	for(i = 0; i < r_len; ++i)
		right[i] = arr[q+1+i];

	i = j = k = 0;

	for(k = p; k <= r; ++k){
		if(i >= l_len){
			while(j < r_len)
				arr[k++] = right[j++];
		}
		else if(j >= r_len){
			while(i < l_len)
				arr[k++] = left[i++];
		}
		else if(left[i] <= right[j])
			arr[k] = left[i++];
		else{
			split_inversions += (l_len - i);
			arr[k] = right[j++];
		}
	}
	return split_inversions;
}

long sort_and_count(int *arr, int p, int r){
	if(p < r){
		long inversions = 0;
		int q = (p + r)/2;
		inversions += sort_and_count(arr, p, q);
		inversions += sort_and_count(arr, q+1, r);
		inversions += merge_and_count(arr, p, q, r);
		return inversions;
	}
	else
		return 0;
}
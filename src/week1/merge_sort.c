#include <stdio.h>
#include <stdlib.h>

void merge(int*, int, int, int);
void merge_sort(int*, int, int);


void merge(int *arr, int p, int q, int r){
	int l_len = q - p + 1;
	int r_len = r - q;
	int *left = (int*)malloc(sizeof(int)*l_len);
	int *right = (int*)malloc(sizeof(int)*r_len);

	//allocation error check
	if(left == NULL || right == NULL){
		fprintf(stderr, "%s\n", "Allocation error in merge routine!");
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
		else if(left[i] < right[j])
			arr[k] = left[i++];
		else
			arr[k] = right[j++];
	}
}

void merge_sort(int *arr, int p, int r){
	if(p < r){
		int q = (p + r)/2;
		merge_sort(arr, p, q);
		merge_sort(arr, q+1, r);
		merge(arr, p, q, r);
	}
}

//Test
int main(void){
	int nums[] = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
	merge_sort(nums, 0, 9);
	for(int i = 0; i < 10; ++i)
		printf("%d ", nums[i]);
	puts("");
}
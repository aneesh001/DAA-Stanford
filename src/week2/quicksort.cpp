#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using std::vector;

int pick_pivot(vector<int> &arr, int beg, int end){
	int mid = (beg + end - 1)/2;
	
	if(arr[mid] > arr[beg]){
		if(arr[mid] < arr[end-1])
			return mid;
		else{
			if(arr[beg] < arr[end-1])
				return end-1;
			else
				return beg;
		}
	}
	else{
		if(arr[mid] > arr[end-1])
			return mid;
		else{
			if(arr[beg] < arr[end-1])
				return beg;
			else
				return end-1;
		}
	}
}

int partition(vector<int> &arr, int beg, int end){
	int pivot_index = pick_pivot(arr, beg, end);
	
	//Swap pivot with first element; after these 3 lines, pivot is at index 'beg'.
	int tmp = arr[pivot_index];
	arr[pivot_index] = arr[beg];
	arr[beg] = tmp;

	int i = beg+1, j = beg+1;

	for(; j < end; ++j){
		if(arr[j] < arr[beg]){
			int t = arr[j];
			arr[j] = arr[i];
			arr[i] = t;
			++i;
		}
	}

	//Swap the pivot into the correct place.
	tmp = arr[beg];
	arr[beg] = arr[i-1];
	arr[i-1] = tmp;

	//return the pivot index after partition.
	return i-1;
}

long quicksort(vector<int> &arr, int beg, int end){
	if(beg < end){
		//std::cout << "sorting" << std::endl;
		long comparisons = 0;
		comparisons += end - beg - 1;
		int pivot_index = partition(arr, beg, end);
		comparisons += quicksort(arr, beg, pivot_index);
		comparisons += quicksort(arr, pivot_index+1, end);
		return comparisons;
	}
	else
		return 0;
}

int main(void){
	constexpr int arr_len = 10000;
	vector<int> my_arr(arr_len);

	//read arr from file
	std::ifstream in("QuickSort.txt");
	for(int i = 0; i < arr_len; ++i)
		in >> my_arr[i];

	long ans = quicksort(my_arr, 0, arr_len);

	std::cout << ans << std::endl;
	return EXIT_SUCCESS;
}
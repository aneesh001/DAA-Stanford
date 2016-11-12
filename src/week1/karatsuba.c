#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MIN(a, b) ((a < b) ? (a) : (b))

int k_multiply(int, int, int);
int find_len(int);

//Test
int main(void){
	printf("%d\n", k_multiply(1268, 16728, 4));
	return 0;
}

/**
  * Finds the length of a number.
  * big_oh(n) ; n is length of number.
  */
int find_len(int num){
	int ret = 0;
	while(num){
		++ret;
		num /= 10;
	}
	return ret;
}

int k_multiply(int x, int y, int n){
	if(n > 1){
		int p = (int)pow(10, n/2);
		int a = x/p, c = y/p;
		int b = x%p, d = y%p;
		int ac = k_multiply(a, c, MIN(find_len(a), find_len(c)));
		int bd = k_multiply(b, d, n/2);
		int mid_term = k_multiply(a + b, c + d, MIN(find_len(a+b), find_len(c+d)));
		int mid_final = mid_term - ac - bd;

		return (int)pow(10, n)*ac + p*mid_final + bd;
	}
	else
		return x*y;
}
#include<stdlib.h>
#include<stdio.h>

//补充以下函数的参数和代码，构造swap_1函数，实现两个数的交换
void swap_1(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int main() {
	int a = 15;
	int b = 10;
	swap_1(&a, &b);
	printf("%d\t%d", a, b);
	return 0;
}

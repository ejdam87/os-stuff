#include <stdio.h>
#include <stdlib.h>


void swap(int* a, int* b){

	int c = *a;
	*a = *b;
	*b = c;
}


void load_array(int* array, size_t size){
	/*
	Function to load "array" with size "size" with numbers
	*/

	int num;;

	for (size_t i = 0; i < size; i++){
		scanf("%d", &num);
		array[i] = num;	
	}
	
}


void print_array(int* array, size_t size){
	/*
	Function to print array
	*/

	putchar('[');

	for (size_t i = 0; i < size; i++){

		if (i == size - 1){
			printf("%d", array[i]);
			continue;
		}

		printf("%d, ", array[i]);
	}

	putchar(']');
	putchar('\n');

}


void reverse(int* array, size_t size){
	/*
	Function to reverse array
	*/

	for (size_t i = 0; i < size / 2; i++){
		swap(&array[i], &array[size - 1 - i]);
	}
}


// Int-array functions
int sum(int* array, size_t size){

	int res = 0;

	for (size_t i = 0; i < size; i++){
		res += array[i];
	}

	return res;
}


int minmax(int* array, size_t size,  int* min, int* max){

	int min_find = 1;
	int max_find = 1;
	
	if (min == NULL){
		min_find = 0;
	}

	if (max == NULL){
		max_find = 0;
	}

	if (max_find == 0 && min_find == 0){
		return 0;
	}

	if (min_find){
		*min = array[0];		
	}

	if (max_find){
		*max = array[0];		
	}
	
	for (size_t i = 1; i < size; i++){

		if (max_find && array[i] > *max){
			*max = array[i];
		}

		if (min_find && array[i] < *min){
			*min = array[i];
		}
	}

	return max_find + min_find;
}


int maximum(int* array, size_t size){

	int current = array[0];

	for (size_t i = 1; i < size; i++){

		if (array[i] > current){
			current = array[i];
		}
	}

	return current;
}


int gcd(int a, int b){

	if (b == 0){
		return a;
	}

	return gcd(b, a % b);
}


int array_gcd(int* array, size_t size){

	int current = gcd(array[0], array[1]);
	
	for (size_t i = 2; i < size; i++){
		current = gcd(current, array[i]);
	}

	return current;
}

// Sorting
void bubble_sort(size_t length, int *array){

	for (size_t i = length - 1; i > 0; i--){
		for (size_t j = 0; j < i; j++){
			if (array[j] > array[j + 1]){
				swap(&array[j], &array[j + 1]);
			}
		}
	}
}



int main(void)
{

    int array[5] = {1, 2, 3, 4, 5};
    reverse(array, 5);
    print_array(array, 5);

    return EXIT_SUCCESS;

}

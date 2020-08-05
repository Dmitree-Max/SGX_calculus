#include "Enclave_t.h"

int ProtectedNumbers[50];
int i = 0;



int get_number(int number_in_array)
{
	return ProtectedNumbers[number_in_array];
}


void initialize_new_number(int value, int* number_in_array)
{
	ProtectedNumbers[i] = value;
	*number_in_array = i;
	i += 1;
	i = i % 50;
	return;
}


void print_number(int number_in_array)
{
	ocall_print_number(ProtectedNumbers[number_in_array]);
	return;
}



void add_numbers(int dst, int src)
{
	ProtectedNumbers[dst] += ProtectedNumbers[src];
	return;
}


void substract_numbers(int dst, int src)
{
	ProtectedNumbers[dst] -= ProtectedNumbers[src];
	return;
}


void multiple_numbers(int dst, int src)
{
	ProtectedNumbers[dst] *= ProtectedNumbers[src];
	return;
}


void calc_hash(int* arr, size_t len, int* result)
{
	int temp_result = 0;
	int arr_size = len / sizeof(int);
	for (int j = 0; j < arr_size; j++)
	{
		temp_result += arr[j] % (j+1);
	}
	*result = temp_result;
}

void shuffle_array(int* arr, size_t len)
{
	int temp_result = 0;
	int arr_size = len / sizeof(int);
	for (int j = 0; j < arr_size; j++)
	{
		int another_one = j * j * 7 % arr_size;
		int tmp = arr[another_one];
		arr[another_one] = arr[j];
		arr[j] = tmp;
	}
}

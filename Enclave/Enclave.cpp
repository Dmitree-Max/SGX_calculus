#include "Enclave_t.h"

int generate_random_number()
{
    ocall_print("Processing random number generation...");
    return 42;
}

int get_number(int** pointer)
{
	return **pointer;
}

void initialize_new_number(int value, int** pointer)
{
	*pointer = new int(value);
	return;
}


void print_number(int* pointer)
{
	ocall_print_number(*pointer);
	return;
}

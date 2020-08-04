#include <stdio.h>
#include <iostream>
#include "Enclave_u.h"
#include "sgx_urts.h"
#include "sgx_utils/sgx_utils.h"
#include "Securenumber.h"
#include <string>

/* Global EID shared by multiple threads */
sgx_enclave_id_t global_eid = 0;

// OCall implementations
void ocall_print(const char* str) {
    printf("%s\n", str);
}


void ocall_print_number(int number) {
    std::cout << number << std::endl;
}


int main(int argc, char const *argv[]) {
//    if(sgx_is_capable(&updated) != SGX_ENABLED)
//    {
//            printf("Error %#x: SGX is not enabled on this device\n", ret);
//            return -1;
//    }



    if (initialize_enclave(&global_eid, "enclave.token", "enclave.signed.so") < 0) {
        std::cout << "Fail to initialize enclave." << std::endl;
        return 1;
    }
    int ptr;
    sgx_status_t status = generate_random_number(global_eid, &ptr);
    std::cout << status << std::endl;
    if (status != SGX_SUCCESS) {
        std::cout << "error" << std::endl;
    }

    int example_array[] = {1, 4, 5, 7};
	std::cout << "array: ";
	for (int i = 0; i<4; i++)
		std::cout << example_array[i];
	std::cout << std::endl;
    int size = sizeof(int)*4;
    int hash = 0;
    status = calc_hash(global_eid, example_array, size, &hash);
	if (status != SGX_SUCCESS)
	{
		std::cout << "error" << std::endl;
	}
	else
	{
		std::cout << "hash: " << hash <<std::endl;
	}
    status = shuffle_array(global_eid, example_array, size);
	if (status != SGX_SUCCESS)
	{
		std::cout << "error" << std::endl;
	}
	else
	{
		std::cout << "shuffled: ";
		for (int i = 0; i<4; i++)
			std::cout << example_array[i];
		std::cout << std::endl;
	}
    status = calc_hash(global_eid, example_array, size, &hash);
	if (status != SGX_SUCCESS)
	{
		std::cout << "error" << std::endl;
	}
	else
	{
		std::cout << "hash: " << hash <<std::endl;
	}


    // Seal the hash
    size_t sealed_size = sizeof(sgx_sealed_data_t) + sizeof(hash);
    uint8_t* sealed_data = (uint8_t*)malloc(sealed_size);

    sgx_status_t ecall_status;
    status = seal(global_eid, &ecall_status,
            (uint8_t*)&hash, sizeof(hash),
            (sgx_sealed_data_t*)sealed_data, sealed_size);





    if (!is_ecall_successful(status, "Sealing failed :(", ecall_status)) {
        return 1;
    }

    SecureNumber a = SecureNumber(global_eid, 7);
    SecureNumber b = SecureNumber(global_eid, 8);
    a += b;
    std::cout << a;
    b += b;
    std::cout << b;
    a *= b;
    std::cout << a;


    int unsealed;
    status = unseal(global_eid, &ecall_status,
            (sgx_sealed_data_t*)sealed_data, sealed_size,
            (uint8_t*)&unsealed, sizeof(unsealed));

    if (!is_ecall_successful(status, "Unsealing failed :(", ecall_status)) {
        return 1;
    }

    std::cout << "Seal round trip success! Receive back hash: " << unsealed << std::endl;

    return 0;
}

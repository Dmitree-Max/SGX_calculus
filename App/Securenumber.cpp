#include "Securenumber.h"

SecureNumber::SecureNumber(sgx_enclave_id_t enclave_id, int value)
{
	this->enclave_id = enclave_id;
	int* pointer;
	std::cout << "pointer: " << pointer << std::endl;
	sgx_status_t status =  initialize_new_number(enclave_id, value, &pointer);
	std::cout << "pointer: " << pointer << std::endl;
    if (status != SGX_SUCCESS)
    {
    	this->in_enclave_value = nullptr;
        std::cout << "can't initialize number in enclave" << std::endl;
    }
    else
    {
    	this->in_enclave_value = pointer;
    }
}


SecureNumber::~SecureNumber() {
	// TODO Auto-generated destructor stub
}


std::ostream& operator<< (std::ostream &out, const SecureNumber &number)
{
	int ptr;
	std::cout << number.in_enclave_value << std::endl;
	int* tmp = number.in_enclave_value;
	sgx_status_t status = get_number(number.enclave_id, &ptr, &(tmp));
    if (status != SGX_SUCCESS)
    {
        out << "can't print number from enclave" << std::endl;
    }
    else
    {
    	out << ptr << std::endl;
    }

    return out;
}

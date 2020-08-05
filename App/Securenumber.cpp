#include "Securenumber.h"

SecureNumber::SecureNumber(sgx_enclave_id_t enclave_id, int value)
{
	this->enclave_id = enclave_id;
	int number_in_array = 0;
	sgx_status_t status =  initialize_new_number(enclave_id, value, &number_in_array);
    if (status != SGX_SUCCESS)
    {
    	this->in_enclave_place = 0;
        std::cout << "can't initialize number in enclave" << std::endl;
    }
    else
    {
    	this->in_enclave_place = number_in_array;
    }
}


SecureNumber::~SecureNumber() {
	// TODO Auto-generated destructor stub
}


std::ostream& operator<< (std::ostream &out, const SecureNumber &number)
{
	int ptr;
	sgx_status_t status = get_number(number.enclave_id, &ptr, number.in_enclave_place);
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


void operator+= (SecureNumber &dst, const SecureNumber &src)
{
	if (dst.enclave_id != src.enclave_id)
	{
		std::cout << "Can't add numbers from different enclaves\n";
		return;
	}

	sgx_status_t status = add_numbers(dst.enclave_id, dst.in_enclave_place, src.in_enclave_place);
    if (status != SGX_SUCCESS)
    {
        std::cout << "Addition in enclave is unsuccessful" << std::endl;
    }

}


void operator-= (SecureNumber &dst, const SecureNumber &src)
{
	if (dst.enclave_id != src.enclave_id)
	{
		std::cout << "Can't add numbers from different enclaves\n";
		return;
	}

	sgx_status_t status = substract_numbers(dst.enclave_id, dst.in_enclave_place, src.in_enclave_place);
    if (status != SGX_SUCCESS)
    {
        std::cout << "Addition in enclave is unsuccessful" << std::endl;
    }

}


void operator*= (SecureNumber &dst, const SecureNumber &src)
{
	if (dst.enclave_id != src.enclave_id)
	{
		std::cout << "Can't add numbers from different enclaves\n";
		return;
	}

	sgx_status_t status = multiple_numbers(dst.enclave_id, dst.in_enclave_place, src.in_enclave_place);
    if (status != SGX_SUCCESS)
    {
        std::cout << "Addition in enclave is unsuccessful" << std::endl;
    }

}


//void SecureNumber::native_print()
//{
//	std::cout << "This print shouldn't work: " << this->in_enclave_place << std::endl;
//}

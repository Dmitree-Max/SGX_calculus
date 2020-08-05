#include "sgx_urts.h"
#include "sgx_utils/sgx_utils.h"
#include "Enclave_u.h"
#include <iostream>


#ifndef SECURENUMBER_H_
#define SECURENUMBER_H_

class SecureNumber {
private:
	sgx_enclave_id_t enclave_id;
	int in_enclave_place;
public:
	SecureNumber(sgx_enclave_id_t enclave_id, int value);
	virtual ~SecureNumber();
	friend std::ostream& operator<< (std::ostream &out, const SecureNumber &number);
	friend void operator+= (SecureNumber &dst, const SecureNumber &src);
	friend void operator-= (SecureNumber &dst, const SecureNumber &src);
	friend void operator*= (SecureNumber &dst, const SecureNumber &src);
};

#endif

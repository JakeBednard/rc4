#include <iostream>
#include <string>
#include "openssl/evp.h"

#ifndef JakeRC4_H
#define JakeRC4_H

class JakeRC4 {

public:
	JakeRC4();
	int encrypt(char* password, int passwordLength, char* ifile, char* ofile);
	int decrypt(char* password, char* ifile, char* ofile);

};

#endif
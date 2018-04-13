#include <iostream>
#include <string>
#include "openssl/rc4.h"

#ifndef JakeRC4_H
#define JakeRC4_H

class JakeRC4 {

public:
	int encrypt(std::string password, std::string ifile, std::string ofile);
	int decrypt(std::string password, std::string ifile, std::string ofile);

};

#endif
/**
Command line parser for entrypoint into the RC4 implementation.
Takes care of verifying that the user has given the correct parameters
and if not, it displays an usage message. 

J.Bednard 2018-04-13
*/

#include <iostream>
#include <string>
#include "jake_rc4.h"

int main(int argc, char *argv[]) {

	std::string operationType = "";
	std::string passwordType = "";
	std::string password = "";
	std::string ifile = "";
	std::string ofile = "";

	const char *usageMsg = 
		"\nInvalid parameters! Usage:\n\n"
		"\tjakeRC4 <-e|-d> -pass password:salt -in ifile -out ofile\n\n"
		"Flags:\n\n"
		"\t-e : Use to encrypt a plaintext file using RC4\n"
		"\t-d : Use to decrypt an encrypted file using RC4\n"
		"\t-pass : Password:Salt to generate an RC4 keystream used in -e,-d\n"
		"\t-in : File containing encrypted/plaintext input file\n"
		"\t-out : File to place encryped/plaintext after operation\n\n";

	// Verify the correct number of arguments
	if (argc < 8) {
		std::cout << usageMsg;
		return 1;
	}

	// Loop through parameters and parse in arguments
	std::string temp;
	for (int i = 1; i < argc; ++i) {

		temp = std::string(argv[i]);

		if (temp == "-e" || temp == "-d") {
			operationType = temp;
		}

		else if (temp == "-pass") {
		
			temp = std::string(argv[++i]);

			int passwordSplit = temp.find(":");
			if (passwordSplit > 0) {
				passwordType = temp.substr(0,passwordSplit);
				password = temp.substr(passwordSplit + 1);
			}

			else {
				std::cout << "No salt provided! Please provide your -pass in password:salt form\n";
				std::cout << usageMsg;
				return 1;
			}

		}

		else if (temp == "-in") {
			ifile = std::string(argv[++i]);
		}

		else if (temp == "-out") {
			ofile = std::string(argv[++i]);
		}

		else {
			std::cout << "Unknown parameter: " << temp << "\n";
			std::cout << usageMsg;
			return 1;
		}

	}

	// Verify that all arguments have been set, if so proceed
	if (
		operationType == "" ||
		passwordType == "" ||
		password == "" ||
		ifile == "" ||
		ofile == ""
	) {
		std::cout << usageMsg;
		return 1;
	}
	
	// Everythings set, lets proceed
	else {
		JakeRC4().encrypt(&password[0u], password.length(), &ifile[0u], &ofile[0u]);
		std::cout << "\nOperation Type: " << operationType << "\n";
		std::cout << "Password Type: " << passwordType << "\n";
		std::cout << "Password: " << password << "\n";
		std::cout << "Input File: " << ifile << "\n";
		std::cout << "Output File: " << ofile << "\n";
	}

	return 0;

}
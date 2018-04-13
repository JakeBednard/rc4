#include <iostream>
#include <string>
//#include "rc4.h"

int main(int argc, char *argv[]) {

	std::string operation_type = "";
	std::string password = "";
	std::string salt = "";
	std::string ifile = "";
	std::string ofile = "";

	const char *usageMsg = 
		"\nInvalid parameters! Usage:\n\n"
		"Example:\n\n"
		"jakeRC4 <-e|-d> -pass password:salt -in ifile -out ofile\n\n"
		"Flags:\n\n"
		"\t-e : Use to encrypt a plaintext file using RC4\n"
		"\t-d : Use to decrypt an encrypted file using RC4\n"
		"\t-pass : Password:Salt to generate an RC4 keystream used in -e,-d\n"
		"\t-in : File containing encrypted/plaintext input file\n"
		"\t-out : File to place encryped/plaintext after operation\n";

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
			operation_type = temp;
		}

		else if (temp == "-pass") {
		
			temp = std::string(argv[++i]);

			int passSaltSplit = temp.find(":");
			if (passSaltSplit > 0) {
				password = temp.substr(0,passSaltSplit);
				salt = temp.substr(passSaltSplit + 1);
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
			ifile = std::string(argv[++i]);
		}

		else {
			std::cout << usageMsg;
			return 1;
		}

	}

	// Verify that all arguments have been set, if so proceed
	if (
		operation_type == "" ||
		password == "" ||
		salt == "" ||
		ifile == "" ||
		ofile == ""
	) {
		std::cout << usageMsg;
		return 1;
	}
	
	// Everythings set, lets proceed
	else {
		std::cout << "Operation Type: " << operation_type << "\n";
		std::cout << "Password: " << password << "\n";
		std::cout << "Salt: " << salt << "\n";
		std::cout << "Input File: " << ifile << "\n";
		std::cout << "Output File: " << ofile << "\n";
	}

	return 0;

}
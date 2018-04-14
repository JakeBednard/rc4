#include "jake_rc4.h"
#include <iomanip>

JakeRC4::JakeRC4() {
	return;
}

int JakeRC4::encrypt(char *password, int passwordLength, char *ifile, char *ofile) {

	unsigned char *key = new unsigned char[32];
	unsigned char salt[] = {'1','2','3','4','5','6','7','8'};
	unsigned char header[] = {'S','a','l','t','e','d','_','_'};
	EVP_CIPHER_CTX ctx;

	unsigned char inbuf[1024];
	unsigned char outbuf[1024 + EVP_MAX_BLOCK_LENGTH];
	int inlen, outlen;
	
	FILE *in = fopen(ifile, "rb");
	FILE *out = fopen(ofile, "wb");

	int keylength = EVP_BytesToKey(EVP_rc4(), EVP_md5(), salt, (const unsigned char*)password, passwordLength, 1, key, NULL);

	EVP_CIPHER_CTX_init(&ctx);
	
	EVP_EncryptInit_ex(&ctx, EVP_rc4(), NULL, key, NULL);

	fwrite(header, 1, 8, out);
	fwrite(salt, 1, 8, out);

	for(;;) {
		
		inlen = fread(inbuf, 1, 1024, in);
		
		if (inlen <= 0) {
			break;
		}

		if (!EVP_CipherUpdate(&ctx, outbuf, &outlen, inbuf, inlen)) {
			EVP_CIPHER_CTX_cleanup(&ctx);
			return 0;
		}

		fwrite(outbuf, 1, outlen, out);

	}

	if (!EVP_CipherFinal_ex(&ctx, outbuf, &outlen)) {
		EVP_CIPHER_CTX_cleanup(&ctx);
		return 0;
	}

	fwrite(outbuf, 1, outlen, out);

	fclose(in);
	fclose(out);

	std::cout << "\nKey: ";
	for(int i = 0; i < keylength; ++i) {
		std::cout << std::hex << (int)key[i];
	}
	std::cout << "\nSalt: ";
	for(int i = 0; i < 8; ++i) {
		std::cout << std::hex << (int)salt[i];
	}

	delete(key);

	return 0;

}
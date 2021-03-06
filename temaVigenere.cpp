#include "stdafx.h"
#include <stdio.h>
#include<stdlib.h>
#include <string.h>


void encryptVigenere(const char* plainText, char* encryptedText, int len, const char* key)
{
	for (int i = 0; i < len; i++)
		encryptedText[i] = 'A' + (plainText[i] - 'A' + key[i] - 'A') % 26;
}

void decryptVigenere(const char* encryptedText, char* plainText, int len, const char* key)
{
	for (int i = 0; i < len; i++)
		plainText[i] = 'A' + (26 + encryptedText[i] - key[i]) % 26;
}

int main()
{
	char plainText[50];
	char cipher[30];
	char decipher[30];
	char key[30];

	printf("text1: ");
	gets_s(plainText, sizeof(plainText));

	printf("key: ");
	gets_s(key, sizeof(plainText));

	int length = strlen(plainText);

	encryptVigenere(plainText, cipher, length, key);

	cipher[length] = '\0';


	printf("encrypted Text: %s\n", cipher);

	decryptVigenere(cipher, decipher, length, key);

	decipher[length] = '\0';

	printf("text1: %s", decipher);
	return 0;
}
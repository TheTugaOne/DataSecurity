#include <stdafx.h>
#include <stdio.h>
#include<stdlib.h>
#include <string.h>

void generateMatrix(const char* key, int keylen, char matrix[5][5])
{
	char freq[26];
	int nr = 0;
	memset(freq, 0, sizeof(freq));
	for (int i = 0; i < keylen; ++i)
	{
		if (freq[key[i] - 'A'] == 0)
		{
			freq[key[i] - 'A'] = 1;

			if (key[i] == 'I')
			{
				freq['J' - 'A'] = 1;
			}
			else if (key[i] == 'J')
			{
				freq['I' - 'A'] = 1;
			}

			matrix[nr / 5][nr % 5] = key[i];
			++nr;
		}
	}

	for (int i = 0; i < 26; ++i)
	{
		if (freq[i] == 0)
		{
			matrix[nr / 5][nr % 5] = i + 'A';
			++nr;
		}
	}
}

void encryptplayfair(const char* plainText, char* encryptedText, int len, const char* key,int keylen)
{
	char matrix[5][5];
	char pos_letter[26][2];

	generateMatrix(key, keylen, matrix);

	for(int i=0;i<5;++i)
		for (int j = 0; j < 5; ++j)
		{
			pos_letter[matrix[i][j] - 'A'][0] = i;
			pos_letter[matrix[i][j] - 'A'][1] = j;
		}


	memcpy(encryptedText, plainText, len);


	for (int i = 0; i < len; i += 2)
	{
		if (encryptedText[i] == encryptedText[i + 1])
			encryptedText[i + 1] = 'X';

		printf("%c%c ", encryptedText[i], encryptedText[i + 1]);

		int a = encryptedText[i] - 'A';
		int b = encryptedText[i + 1] - 'A';


		if (pos_letter[a][0] == pos_letter[b][0])
		{
			encryptedText[i] = matrix[pos_letter[a][0]][(pos_letter[a][1] + 1) % 5];
			encryptedText[i+1] = matrix[pos_letter[b][0]][(pos_letter[b][1] + 1) % 5];
		}
		else if (pos_letter[a][1] == pos_letter[b][1])
		{
			encryptedText[i] = matrix[(pos_letter[a][0] + 1) % 5][pos_letter[a][1]];
			encryptedText[i + 1] = matrix[(pos_letter[b][0] + 1) % 5][pos_letter[b][1]];
		}
		else
		{
			encryptedText[i] = matrix[pos_letter[a][0]][pos_letter[b][1]];
			encryptedText[i+1] = matrix[pos_letter[b][0]][pos_letter[a][1]];
		}


	}
	

}

void decryptplayfair(const char* encryptedText, char* plainText, int len, const char* key, int keylen)
{
	char matrix[5][5];
	char pos_letter[26][2];

	generateMatrix(key, keylen, matrix);

	for (int i = 0; i<5; ++i)
		for (int j = 0; j < 5; ++j)
		{
			pos_letter[matrix[i][j] - 'A'][0] = i;
			pos_letter[matrix[i][j] - 'A'][1] = j;
		}

	memcpy(plainText, encryptedText, len);


	for (int i = 0; i < len; i += 2)
	{
		int a = encryptedText[i] - 'A';
		int b = encryptedText[i + 1] - 'A';


		if (pos_letter[a][0] == pos_letter[b][0])
		{
			plainText[i] = matrix[pos_letter[a][0]][(5 + pos_letter[a][1] - 1) % 5];
			plainText[i + 1] = matrix[pos_letter[b][0]][(5 + pos_letter[b][1] - 1) % 5];
		}
		else if (pos_letter[a][1] == pos_letter[b][1])
		{
			plainText[i] = matrix[(5 + pos_letter[a][0] - 1) % 5][pos_letter[a][1]];
			plainText[i + 1] = matrix[(5 + pos_letter[b][0] - 1) % 5][pos_letter[b][1]];
		}
		else
		{
			plainText[i] = matrix[pos_letter[a][0]][pos_letter[b][1]];
			plainText[i+1] = matrix[pos_letter[b][0]][pos_letter[a][1]];
		}


	}
}

int main()
{
	char plainText[50];
	char cipher[30];
	char decipher[30];
	char key[30];

	printf("Plain Text: ");
	gets_s(plainText, sizeof(plainText));

	printf("Key: ");
	gets_s(key, sizeof(plainText));

	int length = strlen(plainText);

	encryptplayfair(plainText, cipher, length, key,strlen(key));

	if (length % 2 == 1)
		++length;
	cipher[length] = '\0';


	printf("Encrypted Text: %s\n", cipher);

	decryptplayfair(cipher, decipher, length, key, strlen(key));

	decipher[length] = '\0';

	printf("Decrypted Text: %s", decipher);
	return 0;
}
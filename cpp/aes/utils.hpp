#ifndef UTILS_HPP
#define UTILS_HPP

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

unsigned short hexStringToUCharArray(const char *dataIn, unsigned short dataInSize, 
	unsigned char* dataOut, unsigned short dataOutSize, unsigned short padVal);
unsigned short uCharArrayToHexString(unsigned char *dataIn, unsigned short dataInSize, 
	char* dataOut, unsigned short dataOutSize);
void initArray(unsigned char *arr, unsigned short size);
void removeCharacter(char *arr, char c);
short getValuesFromFile(FILE *file, char *key, unsigned short keySize,
	char *plaintext, unsigned short plaintextSize,
	char *iv, unsigned short ivSize,
	char *ciphertext, unsigned short ciphertextSize);

#endif
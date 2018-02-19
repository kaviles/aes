#include "utils.hpp"

unsigned short hexStringToUCharArray(const char *dataIn, unsigned short dataInSize, 
	unsigned char* dataOut, unsigned short dataOutSize, unsigned short padVal) {

	dataOut[0] = '\0';
	unsigned short charCount = 0;
	unsigned short rem = 0;
	unsigned short retSize = 0;
	char charp[3] = {};

	unsigned short i = 0;
	while (i < dataInSize && charCount < dataOutSize) {

		// strncpy(charp, &dataIn[i], 2);
		charp[0] = dataIn[i];
		charp[1] = dataIn[i+1];
		char c = (char) strtol(charp, NULL, 16);
		// strncat((char*) dataOut, &c, 1);
		dataOut[charCount] = c;
		charCount++;

		i += 2;
	}

	retSize = charCount;

	rem = charCount % padVal;
	if (rem) {
		retSize = charCount + padVal - rem;
	}

	return retSize;
}

unsigned short uCharArrayToHexString(unsigned char *dataIn, unsigned short dataInSize, 
	char* dataOut, unsigned short dataOutSize) {

	dataOut[0] = '\0';
	unsigned short charCount = 0;
	char strp[3] = {};

	unsigned short i = 0;
	while (i < dataInSize && charCount < dataOutSize) {

		sprintf(strp, "%02x", dataIn[i]);
		// strncat(dataOut, strp, 2);
		dataOut[charCount] = strp[0];
		dataOut[charCount+1] = strp[1];
		charCount += 2;

		i++;
	}

	return charCount;
}

void initArray(unsigned char *arr, unsigned short size) {

	unsigned short i;
	for (i = 0; i < size; i++) {
		arr[i] = 0;
	}
}

void removeCharacter(char *arr, char c) {

	char *tmp = strrchr(arr, c);
    if (tmp) {
        *tmp = '\0';
    }
}

short getValuesFromFile(FILE *file, char *key, unsigned short keySize,
	char *plaintext, unsigned short plaintextSize,
	char *iv, unsigned short ivSize,
	char *ciphertext, unsigned short ciphertextSize) {

	if (fgets(key, keySize, file)) {

        removeCharacter(key, '\n');
        removeCharacter(key, '\r');
    }
    else {
        return 0;
    }

    if (iv) {

	    if (fgets(iv, ivSize, file)) {

	        removeCharacter(iv, '\n');
	        removeCharacter(iv, '\r');
	    }
	    else {
	        return 0;
	    }
    }

    if (fgets(plaintext, plaintextSize, file)) {

        removeCharacter(plaintext, '\n');
        removeCharacter(plaintext, '\r');
    }
    else {
        return 0;
    }

    if (fgets(ciphertext, ciphertextSize, file)) {

        removeCharacter(ciphertext, '\n');
        removeCharacter(ciphertext, '\r');
    }
    else {
        return 0;
    }

    return 1;
}
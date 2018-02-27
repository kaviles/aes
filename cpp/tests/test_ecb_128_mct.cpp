#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <string.h>

#include "catch.hpp"
#include "../aes/aes.hpp"
#include "../aes/utils.hpp"

TEST_CASE( "ecb_128_mct", "[ecb, 128, mct]" ) {
    
    unsigned short filenamesSize = 1;
    const char filenames[5][32] = {
        "mct/ECBMCT128"
    };

    const char relative[32] = "../../test_files/ecb/";
    const char extension[32] = ".txt";
    char filename[128];

    char sectionName[32];

    unsigned short CHUNK = 1024; /* buffer size of 1024 bytes */
    
    char key[CHUNK];
    char nextKey[CHUNK];
    char nextKeyData[CHUNK];
    char plaintext[CHUNK];
    char ciphertext[CHUNK];
    char ctRes[CHUNK];
    char ctResData[CHUNK];

    unsigned short keyLen = 0;
    unsigned short ptLen = 0;
    unsigned short ctLen = 0;
    unsigned short ctResLen = 0;

    FILE *file;
    size_t nread;

    unsigned short i, j, k, m, n = 0;

    while (i < filenamesSize) {

        filename[0] = '\0';
        sprintf(filename, "%s%s%s", relative, filenames[i], extension);

        file = fopen(filename, "r");

        if (file) {

            fgets(key, CHUNK, file); // Reads first line which is set to "[ENCRYPT]"

            j = 0;
            while (1) {

                sectionName[0] = '\0';
                sprintf(sectionName, "%s %hu", filenames[i], j);
                // printf("%s\n", sectionName);

                // This doesn't work for some reason.
                // SECTION ( sectionName ) { 

                    if (getValuesFromFile(file, key, CHUNK, plaintext, CHUNK, 0, CHUNK, ciphertext, CHUNK)) {

                        keyLen = strlen(key);
                        ptLen = strlen(plaintext);
                        ctLen = strlen(ciphertext);
                        ctResLen = ctLen;
                        j += 3;
                    }
                    else {
                        break;
                    }

                    for (m = 0; m < 100; m++) {

                        for (n = 0; n < 1000; n++) {
                            aes_encrypt(plaintext, ptLen, ctRes, ctResLen, key, keyLen, 0, 0, 0, 0);
                            memcpy(plaintext, ctRes, ctResLen);
                        }

                        for (k = 0; k < ctLen; k++) {
                            REQUIRE(ctRes[k] == ciphertext[k]);
                        }

                        // Since this is a 128-bit test...

                        hexStringToUCharArray((const char*) key, keyLen, (unsigned char*) nextKeyData, keyLen / 2, 16);
                        hexStringToUCharArray((const char*) ctRes, ctResLen, (unsigned char*) ctResData, ctResLen / 2, blockSize);

                        for (k = 0; k < blockSize; k++) {
                            nextKeyData[k] = nextKeyData[k] ^ ctResData[k];
                        }

                        uCharArrayToHexString((unsigned char*) nextKeyData, keyLen / 2, nextKey, keyLen);

                        if (getValuesFromFile(file, key, CHUNK, plaintext, CHUNK, 0, CHUNK, ciphertext, CHUNK)) {

                            keyLen = strlen(key);
                            ptLen = strlen(plaintext);
                            ctLen = strlen(ciphertext);
                            ctResLen = ctLen;
                            j += 3;
                        }
                        else {
                            break;
                        }

                        for (k = 0; k < keyLen; k++) {
                            REQUIRE(nextKey[k] == key[k]);
                        }
                    }

                // }
            }
        }

        fclose(file);
        i++;
    }
}
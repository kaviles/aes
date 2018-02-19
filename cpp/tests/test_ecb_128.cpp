#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <string.h>

#include "catch.hpp"
#include "../aes/aes.hpp"
#include "../aes/utils.hpp"

TEST_CASE( "ecb_128", "[ecb, 128, kat, mmt]" ) {
    
    unsigned short filenamesSize = 5;
    const char filenames[5][32] = {
        "kat/ECBGFSbox128",
        "kat/ECBKeySbox128",
        "kat/ECBVarKey128",
        "kat/ECBVarTxt128",
        "mmt/ECBMMT128"
    };

    const char relative[32] = "../../test_files/ecb/";
    const char extension[32] = ".txt";
    char filename[128];

    char sectionName[32];

    unsigned short CHUNK = 1024; /* buffer size of 1024 bytes */
    
    char key[CHUNK];
    char plaintext[CHUNK];
    char ciphertext[CHUNK];
    char ctRes[CHUNK];

    unsigned short keyLen = 0;
    unsigned short ptLen = 0;
    unsigned short ctLen = 0;
    unsigned short ctResLen = 0;

    FILE *file;
    size_t nread;

    unsigned short i, j, k = 0;

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

                        aes_encrypt(plaintext, ptLen, ctRes, ctResLen, key, keyLen, 0, 0, 0, 0);

                        for (k = 0; k < ctLen; k++) {
                            REQUIRE(ctRes[k] == ciphertext[k]);
                        }   
                    }
                    else {
                        break;
                    }

                // }

                j += 3;
            }
        }

        fclose(file);
        i++;
    }
}
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <string.h>

#include "catch.hpp"
#include "../aes/aes.hpp"
#include "../aes/utils.hpp"

TEST_CASE( "cfb_128", "[cfb, 128, kat, mmt]" ) {
    
    // unsigned short filenames128Size = 5;
    unsigned short filenames128Size = 0;
    const char filenames128[5][32] = {
        "kat/CFB128GFSbox128",
        "kat/CFB128KeySbox128",
        "kat/CFB128VarKey128",
        "kat/CFB128VarTxt128",
        "mmt/CFB128MMT128"
    };

    unsigned short filenames8Size = 5;
    const char filenames8[5][32] = {
        "kat/CFB8GFSbox128",
        "kat/CFB8KeySbox128",
        "kat/CFB8VarKey128",
        "kat/CFB8VarTxt128",
        "mmt/CFB8MMT128"
    };

    // unsigned short filenames1Size = 5;
    unsigned short filenames1Size = 0;
    const char filenames1[5][32] = {
        "kat/CFB1GFSbox128",
        "kat/CFB1KeySbox128",
        "kat/CFB1VarKey128",
        "kat/CFB1VarTxt128",
        "mmt/CFB1MMT128"
    };

    const char relative[32] = "../../test_files/cfb/";
    const char extension[32] = ".txt";
    char filename[128];

    char sectionName[32];

    unsigned short CHUNK = 1024; /* buffer size of 1024 bytes */
    
    char key[CHUNK];
    char iv[CHUNK];
    char plaintext[CHUNK];
    char ciphertext[CHUNK];
    char ctRes[CHUNK];

    unsigned short keyLen = 0;
    unsigned short ivLen = 0;
    unsigned short ptLen = 0;
    unsigned short ctLen = 0;
    unsigned short ctResLen = 0;

    FILE *file;
    size_t nread;

    unsigned short i, j, k = 0;

    SECTION ( "CFB128" ) {

        while (i < filenames128Size) {

            filename[0] = '\0';
            sprintf(filename, "%s%s%s", relative, filenames128[i], extension);

            file = fopen(filename, "r");

            if (file) {

                fgets(key, CHUNK, file); // Reads first line which is set to "[ENCRYPT]"

                j = 0;
                while (1) {

                    sectionName[0] = '\0';
                    sprintf(sectionName, "%s %hu", filenames128[i], j);
                    // printf("%s\n", sectionName);

                    // This doesn't work for some reason.
                    // SECTION ( sectionName ) { 

                        if (getValuesFromFile(file, key, CHUNK, plaintext, CHUNK, iv, CHUNK, ciphertext, CHUNK)) {

                            keyLen = strlen(key);
                            ivLen = strlen(iv);
                            ptLen = strlen(plaintext);
                            ctLen = strlen(ciphertext);
                            ctResLen = ctLen;

                            aes_encrypt(plaintext, ptLen, ctRes, ctResLen, key, keyLen, iv, ivLen, 0, 2);

                            for (k = 0; k < ctLen; k++) {
                                REQUIRE(ctRes[k] == ciphertext[k]);
                            }   
                        }
                        else {
                            break;
                        }

                    // }

                    j += 4;
                }
            }

            fclose(file);
            i++;
        }
    }

    // SECTION ( "CFB8" ) {

    //     i=4;

    //     while (i < filenames8Size) {

    //         filename[0] = '\0';
    //         sprintf(filename, "%s%s%s", relative, filenames8[i], extension);

    //         file = fopen(filename, "r");

    //         if (file) {

    //             fgets(key, CHUNK, file); // Reads first line which is set to "[ENCRYPT]"

    //             j = 0;
    //             while (1) {

    //                 sectionName[0] = '\0';
    //                 sprintf(sectionName, "%s %hu", filenames8[i], j);
    //                 printf("%s\n", sectionName);

    //                 // This doesn't work for some reason.
    //                 // SECTION ( sectionName ) { 

    //                     if (getValuesFromFile(file, key, CHUNK, plaintext, CHUNK, iv, CHUNK, ciphertext, CHUNK)) {

    //                         keyLen = strlen(key);
    //                         ivLen = strlen(iv);
    //                         ptLen = strlen(plaintext);
    //                         ctLen = strlen(ciphertext);
    //                         ctResLen = ctLen;

    //                         aes_encrypt(plaintext, ptLen, ctRes, ctResLen, key, keyLen, iv, ivLen, 0, 2);

    //                         for (k = 0; k < ctLen; k++) {
    //                             REQUIRE(ctRes[k] == ciphertext[k]);
    //                         }   
    //                     }
    //                     else {
    //                         break;
    //                     }

    //                 // }

    //                 j += 4;
    //             }
    //         }

    //         fclose(file);
    //         i++;
    //     }
    // }

    // SECTION ( "CFB1" ) {

    //     while (i < filenames1Size) {

    //         filename[0] = '\0';
    //         sprintf(filename, "%s%s%s", relative, filenames1[i], extension);

    //         file = fopen(filename, "r");

    //         if (file) {

    //             fgets(key, CHUNK, file); // Reads first line which is set to "[ENCRYPT]"

    //             j = 0;
    //             while (1) {

    //                 sectionName[0] = '\0';
    //                 sprintf(sectionName, "%s %hu", filenames1[i], j);
    //                 // printf("%s\n", sectionName);

    //                 // This doesn't work for some reason.
    //                 // SECTION ( sectionName ) { 

    //                     if (getValuesFromFile(file, key, CHUNK, plaintext, CHUNK, iv, CHUNK, ciphertext, CHUNK)) {

    //                         keyLen = strlen(key);
    //                         ivLen = strlen(iv);
    //                         ptLen = strlen(plaintext);
    //                         ctLen = strlen(ciphertext);
    //                         ctResLen = ctLen;

    //                         aes_encrypt(plaintext, ptLen, ctRes, ctResLen, key, keyLen, iv, ivLen, 0, 2);

    //                         for (k = 0; k < ctLen; k++) {
    //                             REQUIRE(ctRes[k] == ciphertext[k]);
    //                         }   
    //                     }
    //                     else {
    //                         break;
    //                     }

    //                 // }

    //                 j += 4;
    //             }
    //         }

    //         fclose(file);
    //         i++;
    //     }
    // }
}
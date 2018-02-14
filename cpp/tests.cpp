#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <math.h>

#include "catch.hpp"
#include "aes.hpp"


TEST_CASE( "bit_count", "[bit, count]" ) {
    
    SECTION( "counting bits" ) {

        REQUIRE(bit_count(0) == 0);

        unsigned char value = 1;
        unsigned char i;
        for (i = 1; i < 8; i++) {
            
            REQUIRE(bit_count(value) == i);
            value = (value << 1);
        }
    }
}

TEST_CASE( "multiply", "[multiply, modular]" ) {
    
    SECTION( "testing modular multiplication function" ) {

        REQUIRE(mod_multiply(0x5, 0x10) == 0x50);
        REQUIRE(mod_multiply(0x10, 0x5) == 0x50);
        REQUIRE(mod_multiply(0x80, 0x80) == 0x4000);
        REQUIRE(mod_multiply(0xa5, 0xa5) == 0x4411);
        REQUIRE(mod_multiply(0x3c, 0xa5) == 0x194c);
    }
}

TEST_CASE( "galoi_mult", "[galoi, multiply]" ) {
    
    SECTION( "testing galoi multiply function" ) {


        int i;
        for (i = 1; i < 16; i++) {
            REQUIRE(galoi_mult(pow(2, i-1)) == rcons[i]);
        }
    }
}

TEST_CASE( "expand_key", "[expand, key]" ) {
    
    unsigned char keySize = 16;
    unsigned char rounds = 11;
    unsigned char exKeySize = rounds * keySize;

    SECTION( "testing key expansion 1" ) {

        // Test cases take from http://www.samiam.org/key-schedule.html
        
        unsigned char key[] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f};
        unsigned char exKey[exKeySize];
        unsigned char exKeyAns[] = {
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 
            0xd6, 0xaa, 0x74, 0xfd, 0xd2, 0xaf, 0x72, 0xfa, 0xda, 0xa6, 0x78, 0xf1, 0xd6, 0xab, 0x76, 0xfe, 
            0xb6, 0x92, 0xcf, 0x0b, 0x64, 0x3d, 0xbd, 0xf1, 0xbe, 0x9b, 0xc5, 0x00, 0x68, 0x30, 0xb3, 0xfe, 
            0xb6, 0xff, 0x74, 0x4e, 0xd2, 0xc2, 0xc9, 0xbf, 0x6c, 0x59, 0x0c, 0xbf, 0x04, 0x69, 0xbf, 0x41, 
            0x47, 0xf7, 0xf7, 0xbc, 0x95, 0x35, 0x3e, 0x03, 0xf9, 0x6c, 0x32, 0xbc, 0xfd, 0x05, 0x8d, 0xfd, 
            0x3c, 0xaa, 0xa3, 0xe8, 0xa9, 0x9f, 0x9d, 0xeb, 0x50, 0xf3, 0xaf, 0x57, 0xad, 0xf6, 0x22, 0xaa, 
            0x5e, 0x39, 0x0f, 0x7d, 0xf7, 0xa6, 0x92, 0x96, 0xa7, 0x55, 0x3d, 0xc1, 0x0a, 0xa3, 0x1f, 0x6b, 
            0x14, 0xf9, 0x70, 0x1a, 0xe3, 0x5f, 0xe2, 0x8c, 0x44, 0x0a, 0xdf, 0x4d, 0x4e, 0xa9, 0xc0, 0x26, 
            0x47, 0x43, 0x87, 0x35, 0xa4, 0x1c, 0x65, 0xb9, 0xe0, 0x16, 0xba, 0xf4, 0xae, 0xbf, 0x7a, 0xd2, 
            0x54, 0x99, 0x32, 0xd1, 0xf0, 0x85, 0x57, 0x68, 0x10, 0x93, 0xed, 0x9c, 0xbe, 0x2c, 0x97, 0x4e, 
            0x13, 0x11, 0x1d, 0x7f, 0xe3, 0x94, 0x4a, 0x17, 0xf3, 0x07, 0xa7, 0x8b, 0x4d, 0x2b, 0x30, 0xc5};

        expand_key(key, keySize, exKey, exKeySize);

        int i;
        for (i = 0; i < exKeySize; i++) {
            REQUIRE(exKey[i] == exKeyAns[i]);
        }
    }

    SECTION( "testing key expansion 2" ) {

        // Test cases take from http://www.samiam.org/key-schedule.html

        unsigned char key[] = {0x69, 0x20, 0xe2, 0x99, 0xa5, 0x20, 0x2a, 0x6d, 0x65, 0x6e, 0x63, 0x68, 0x69, 0x74, 0x6f, 0x2a};
        unsigned char exKey[exKeySize];

        unsigned char exKeyAns[] = {
            0x69, 0x20, 0xe2, 0x99, 0xa5, 0x20, 0x2a, 0x6d, 0x65, 0x6e, 0x63, 0x68, 0x69, 0x74, 0x6f, 0x2a, 
            0xfa, 0x88, 0x07, 0x60, 0x5f, 0xa8, 0x2d, 0x0d, 0x3a, 0xc6, 0x4e, 0x65, 0x53, 0xb2, 0x21, 0x4f, 
            0xcf, 0x75, 0x83, 0x8d, 0x90, 0xdd, 0xae, 0x80, 0xaa, 0x1b, 0xe0, 0xe5, 0xf9, 0xa9, 0xc1, 0xaa, 
            0x18, 0x0d, 0x2f, 0x14, 0x88, 0xd0, 0x81, 0x94, 0x22, 0xcb, 0x61, 0x71, 0xdb, 0x62, 0xa0, 0xdb, 
            0xba, 0xed, 0x96, 0xad, 0x32, 0x3d, 0x17, 0x39, 0x10, 0xf6, 0x76, 0x48, 0xcb, 0x94, 0xd6, 0x93, 
            0x88, 0x1b, 0x4a, 0xb2, 0xba, 0x26, 0x5d, 0x8b, 0xaa, 0xd0, 0x2b, 0xc3, 0x61, 0x44, 0xfd, 0x50, 
            0xb3, 0x4f, 0x19, 0x5d, 0x09, 0x69, 0x44, 0xd6, 0xa3, 0xb9, 0x6f, 0x15, 0xc2, 0xfd, 0x92, 0x45, 
            0xa7, 0x00, 0x77, 0x78, 0xae, 0x69, 0x33, 0xae, 0x0d, 0xd0, 0x5c, 0xbb, 0xcf, 0x2d, 0xce, 0xfe, 
            0xff, 0x8b, 0xcc, 0xf2, 0x51, 0xe2, 0xff, 0x5c, 0x5c, 0x32, 0xa3, 0xe7, 0x93, 0x1f, 0x6d, 0x19, 
            0x24, 0xb7, 0x18, 0x2e, 0x75, 0x55, 0xe7, 0x72, 0x29, 0x67, 0x44, 0x95, 0xba, 0x78, 0x29, 0x8c, 
            0xae, 0x12, 0x7c, 0xda, 0xdb, 0x47, 0x9b, 0xa8, 0xf2, 0x20, 0xdf, 0x3d, 0x48, 0x58, 0xf6, 0xb1};

        expand_key(key, keySize, exKey, exKeySize);

        int i;
        for (i = 0; i < exKeySize; i++) {
            REQUIRE(exKey[i] == exKeyAns[i]);
        }
    }
}

TEST_CASE( "add_roud_key", "[add, round, key]" ) {

    unsigned char exKeySize = 176;

    unsigned char block[] = {0x8d, 0x96, 0x4e, 0x53, 0xb9, 0x1f, 0x73, 0x68, 0x99, 0x14, 0xca, 0xdd, 0xea, 0x6b, 0x5e, 0xe9};
    unsigned char exKey[] = {
        0x69, 0x20, 0xe2, 0x99, 0xa5, 0x20, 0x2a, 0x6d, 0x65, 0x6e, 0x63, 0x68, 0x69, 0x74, 0x6f, 0x2a, 
        0xfa, 0x88, 0x07, 0x60, 0x5f, 0xa8, 0x2d, 0x0d, 0x3a, 0xc6, 0x4e, 0x65, 0x53, 0xb2, 0x21, 0x4f, 
        0xcf, 0x75, 0x83, 0x8d, 0x90, 0xdd, 0xae, 0x80, 0xaa, 0x1b, 0xe0, 0xe5, 0xf9, 0xa9, 0xc1, 0xaa, 
        0x18, 0x0d, 0x2f, 0x14, 0x88, 0xd0, 0x81, 0x94, 0x22, 0xcb, 0x61, 0x71, 0xdb, 0x62, 0xa0, 0xdb, 
        0xba, 0xed, 0x96, 0xad, 0x32, 0x3d, 0x17, 0x39, 0x10, 0xf6, 0x76, 0x48, 0xcb, 0x94, 0xd6, 0x93, 
        0x88, 0x1b, 0x4a, 0xb2, 0xba, 0x26, 0x5d, 0x8b, 0xaa, 0xd0, 0x2b, 0xc3, 0x61, 0x44, 0xfd, 0x50, 
        0xb3, 0x4f, 0x19, 0x5d, 0x09, 0x69, 0x44, 0xd6, 0xa3, 0xb9, 0x6f, 0x15, 0xc2, 0xfd, 0x92, 0x45, 
        0xa7, 0x00, 0x77, 0x78, 0xae, 0x69, 0x33, 0xae, 0x0d, 0xd0, 0x5c, 0xbb, 0xcf, 0x2d, 0xce, 0xfe, 
        0xff, 0x8b, 0xcc, 0xf2, 0x51, 0xe2, 0xff, 0x5c, 0x5c, 0x32, 0xa3, 0xe7, 0x93, 0x1f, 0x6d, 0x19, 
        0x24, 0xb7, 0x18, 0x2e, 0x75, 0x55, 0xe7, 0x72, 0x29, 0x67, 0x44, 0x95, 0xba, 0x78, 0x29, 0x8c, 
        0xae, 0x12, 0x7c, 0xda, 0xdb, 0x47, 0x9b, 0xa8, 0xf2, 0x20, 0xdf, 0x3d, 0x48, 0x58, 0xf6, 0xb1};

    SECTION( "testing add round key 0" ) {

        add_round_key(block, exKey, exKeySize, 0);

        unsigned char ansBlock[] = {0xe4, 0xb6, 0xac, 0xca, 0x1c, 0x3f, 0x59, 0x05, 0xfc, 0x7a, 0xa9, 0xb5, 0x83, 0x1f, 0x31, 0xc3};

        int i;
        for (i = 0; i < blockSize; i++) {
            REQUIRE(block[i] == ansBlock[i]);
        }
    }

    SECTION( "testing add round key 5" ) {

        add_round_key(block, exKey, exKeySize, 5);

        unsigned char ansBlock[] = {0x05, 0x8d, 0x04, 0xe1, 0x03, 0x39, 0x2e, 0xe3, 0x33, 0xc4, 0xe1, 0x1e, 0x8b, 0x2f, 0xa3, 0xb9};

        int i;
        for (i = 0; i < blockSize; i++) {
            REQUIRE(block[i] == ansBlock[i]);
        }
    }


    SECTION( "testing add round key 10" ) {

        add_round_key(block, exKey, exKeySize, 10);

        unsigned char ansBlock[] = {0x23, 0x84, 0x32, 0x89, 0x62, 0x58, 0xe8, 0xc0, 0x6b, 0x34, 0x15, 0xe0, 0xa2, 0x33, 0xa8, 0x58};

        int i;
        for (i = 0; i < blockSize; i++) {
            REQUIRE(block[i] == ansBlock[i]);
        }
    }
}

// Assume this works correctly. It is entirely dependent on the hard coded SBox.
// TEST_CASE( "substitute", "[substitute, sbox]" ) {

//     SECTION( "testing substitute" ) {
//     }
// }

TEST_CASE("shift_rows_left", "[shift, rows, left]") {
    
    unsigned char block[] = {0x8d, 0x96, 0x4e, 0x53, 0xb9, 0x1f, 0x73, 0x68, 0x99, 0x14, 0xca, 0xdd, 0xea, 0x6b, 0x5e, 0xe9};

    SECTION( "testing shift_rows_left" ) {

        // Test cases take from http://www.samiam.org/key-schedule.html

        shift_rows_left(block);

        unsigned char ansBlock[] = {0x8d, 0x1f, 0xca, 0xe9, 0xb9, 0x14, 0x5e, 0x53, 0x99, 0x6b, 0x4e, 0x68, 0xea, 0x96, 0x73, 0xdd};

        int i;
        for (i = 0; i < blockSize; i++) {
            REQUIRE(block[i] == ansBlock[i]);
        }
    }
}

TEST_CASE("mix_columns", "[mix, rows]") {
    
    unsigned char block[] = {0x8d, 0x96, 0x4e, 0x53, 0xb9, 0x1f, 0x73, 0x68, 0x99, 0x14, 0xca, 0xdd, 0xea, 0x6b, 0x5e, 0xe9};

    SECTION( "testing mix columns" ) {

        mix_columns(block);

        unsigned char ansBlock[] = {0xbd, 0x3b, 0x72, 0xf2, 0x53, 0x7a, 0xf8, 0x6c, 0x02, 0x29, 0x7e, 0xcf, 0xc5, 0x37, 0x1d, 0xd9};

        int i;
        for (i = 0; i < blockSize; i++) {
            REQUIRE(block[i] == ansBlock[i]);
        }
    }
}

TEST_CASE("aes_encrypt_block", "[aes, encrypt]") {
    
    unsigned char rounds = 11;

    unsigned char keySize = 16;
    unsigned char key[] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c};
    
    unsigned char exKeySize = keySize * rounds;
    unsigned char exKey[exKeySize];

    unsigned char block[] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};

    SECTION( "testing aes encrypt block 1" ) {

        expand_key(key, keySize, exKey, exKeySize);

        aes_encrypt_block(block, exKey, exKeySize, rounds);

        unsigned char ansBlock[] = {0x39, 0x25, 0x84, 0x1d, 0x02, 0xdc, 0x09, 0xfb, 0xdc, 0x11, 0x85, 0x97, 0x19, 0x6a, 0x0b, 0x32};

        int i;
        for (i = 0; i < blockSize; i++) {
            REQUIRE(block[i] == ansBlock[i]);
        }
    }
}
#include "aes.hpp"
#include "utils.hpp"

using namespace std;

unsigned short mod_multiply(unsigned short value1, unsigned short value2) {

    unsigned short temp;
    unsigned short product;
    unsigned short i;

    if (value1 < value2) {
        temp = value1;
        value1 = value2;
        value2 = temp;
    }

    temp = value2;
    product = 0;

    i = 0;
    while (temp > 0) {
        if (temp & 1) {

            // TODO: How to avoid cases where overflow occurs?
            // Overflow will likely never occur because the input values will always 
            // be unsigned chars which take up 1/2 space that shorts take up.
            product = product ^ (value1 << i); 
        }

        temp = temp >> 1;
        i++;
    }

    return product;
}

unsigned char bit_count(unsigned short value) {

  unsigned char count = 0;

    while (value > 0) {
        value = value >> 1;

        count++;
    }

    return count;
}

unsigned char galoi_mult(unsigned short value) {
    
    unsigned char bcv = bit_count(value);
    unsigned char bcp = bit_count(poly);

    while (bcv >= bcp) {
        value = value ^ (poly << (bcv - bcp));
        bcv = bit_count(value);
    }

    return (unsigned char) value;

}

void expand_key(unsigned char *key, unsigned char keySize, unsigned char *exKey, unsigned char exKeySize) {

    // Copy intial key to the beginning of expanded key.
    unsigned char i = 0;
    while (i < keySize) {
        exKey[i] = key[i];
        i++;
    }

    // Generate the rest of the expanded key.
    unsigned char round = 1; // Should this be 0 or 1?
    while (i < exKeySize) {

        // For the first four bytes of current round key... 
        // copy the previous four bytes, 
        // shift them left with wrapping, sbox substitution, 
        // XOR with the first four bytes of previous round 
        // finally, XOR rcon with first byte.
        exKey[i] = sbox[exKey[i-3]] ^ exKey[i - keySize] ^ rcons[round];
        exKey[i+1] = sbox[exKey[i-2]] ^ exKey[i - keySize + 1];
        exKey[i+2] = sbox[exKey[i-1]] ^ exKey[i - keySize + 2];
        exKey[i+3] = sbox[exKey[i-4]] ^ exKey[i - keySize + 3];
        i += 4;

        // Fill out the rest of the current round key.
        // TODO: Use a more efficient mod function.
        while (i % keySize) { 
            exKey[i] = exKey[i - keySize] ^ exKey[i-4];
            i++;
        }

        round++;
    }
}

void add_round_key(unsigned char *block, unsigned char *exKey, unsigned char exKeySize, unsigned char round) {

    unsigned char i = 0;
    for (i = 0; i < blockSize; i++) {
        block[i] = block[i] ^ exKey[round*blockSize + i];
    }

}

void substitute(unsigned char *block) {

    unsigned char i = 0;
    for (i = 0; i < blockSize; i++) {
        block[i] = sbox[block[i]];
    }
}

void shift_rows_left(unsigned char *block) {
    
    unsigned char temp1;
    unsigned char temp2;

    // Row 0 stays the same

    // Row 1 is shifted left one with wrapping.
    temp1 = block[1];
    block[1] = block[5];
    block[5] = block[9];
    block[9] = block[13];
    block[13] = temp1;

    // Row 2 is shifted left two with wrapping.
    temp1 = block[2];
    temp2 = block[6];
    block[2] = block[10];
    block[6] = block[14];
    block[10] = temp1;
    block[14] = temp2;

    // Row 3 is shifted left three with wrapping.
    // This can also be done by shifting to the right one over.
    temp1 = block[15];
    block[15] = block[11];
    block[11] = block[7];
    block[7] = block[3];
    block[3] = temp1;
}

void mix_columns(unsigned char *block) {

    unsigned char i = 0;
    unsigned char j;
    unsigned char k;
    unsigned char l;

    for (j = 0; j < blockSize; j+=4) {
        unsigned char temp1[] = {block[j], block[j+1], block[j+2], block[j+3]};

        for (k = 0; k < blockSize; k+=4) {
            unsigned char temp2[] = {mix[k], mix[k+1], mix[k+2], mix[k+3]};

            unsigned char val = 0;

            for (l = 0; l < 4; l++) {
                val = val ^ galoi_mult(mod_multiply(temp1[l], temp2[l]));
            }

            block[i] = val;
            i++;
        }
    }
}

void aes_encrypt_block(unsigned char *block, unsigned char *exKey, unsigned char exKeySize, unsigned char rounds) {

    unsigned char i;

    for (i = 0; i < rounds-1; i++) {

        // Add Round Key
        add_round_key(block, exKey, exKeySize, i);

        // SBox Substitution
        substitute(block);

        // Shift Rows Left
        shift_rows_left(block);

        if (i < rounds-2) {
            // Mix Columns
            mix_columns(block);
        }
    }

    // Add Round Key - Final Round
    add_round_key(block, exKey, exKeySize, i);
}

void aes_ecb_encrypt(unsigned char *plaintext, unsigned short plaintextSize, 
    unsigned char *ciphertext, unsigned short ciphertextSize, 
    unsigned char *key, unsigned char keySize) {

    unsigned short i, j, charCount;

    unsigned char exKeySize = 176;
    unsigned char rounds = 11;
    unsigned char exKey[exKeySize];
    initArray(exKey, exKeySize);
    unsigned char block[blockSize];
    initArray(block, blockSize);

    expand_key(key, keySize, exKey, exKeySize);

    i = 0;
    charCount = 0;
    while (i < plaintextSize && charCount < ciphertextSize) {

        for (j = i; j < (i + blockSize) && j < plaintextSize; j++) {
            block[j % blockSize] = plaintext[j];
        }

        aes_encrypt_block(block, exKey, exKeySize, rounds);
        // strncat((char*) ciphertext, (char*) block, blockSize);

        for (j = 0; j < blockSize && charCount < ciphertextSize; j++) {
            ciphertext[charCount] = block[j];
            charCount++;
        }

        i += blockSize;
    }
}

void aes_cbc_encrypt(unsigned char *plaintext, unsigned short plaintextSize, 
    unsigned char *ciphertext, unsigned short ciphertextSize, 
    unsigned char *key, unsigned char keySize, unsigned char *iv) {

    unsigned short i, j, charCount = 0;

    unsigned char exKeySize = 176;
    unsigned char rounds = 11;
    unsigned char exKey[exKeySize];
    initArray(exKey, exKeySize);
    unsigned char block[blockSize];
    initArray(block, blockSize);

    expand_key(key, keySize, exKey, exKeySize);

    for (j = 0; j < blockSize; j++) {
        block[j] = plaintext[j] ^ iv[j];
    }

    aes_encrypt_block(block, exKey, exKeySize, rounds);

    for (j = 0; j < blockSize && charCount < ciphertextSize; j++) {
        ciphertext[charCount] = block[j];
        charCount++;
    }

    i = blockSize;
    while (i < plaintextSize && charCount < ciphertextSize) {

        for (j = i; j < (i + blockSize) && j < plaintextSize; j++) {
            block[j % blockSize] = plaintext[j] ^ ciphertext[charCount-blockSize + (j % blockSize)];
        }

        aes_encrypt_block(block, exKey, exKeySize, rounds);

        for (j = 0; j < blockSize && charCount < ciphertextSize; j++) {
            ciphertext[charCount] = block[j];
            charCount++;
        }

        i += blockSize;
    }
}


void aes_cfb_encrypt(unsigned char *plaintext, unsigned short plaintextSize, 
    unsigned char *ciphertext, unsigned short ciphertextSize, 
    unsigned char *key, unsigned char keySize, unsigned char *iv) {

    unsigned short i, j, charCount = 0;

    unsigned char exKeySize = 176;
    unsigned char rounds = 11;
    unsigned char exKey[exKeySize];
    initArray(exKey, exKeySize);
    unsigned char block[blockSize];
    initArray(block, blockSize);

    expand_key(key, keySize, exKey, exKeySize);

    for (j = 0; j < blockSize; j++) {
        block[j] = iv[j];
    }

    aes_encrypt_block(block, exKey, exKeySize, rounds);

    for (j = 0; j < blockSize; j++) {
        block[j] = block[j] ^ plaintext[j];
    }

    for (j = 0; j < blockSize && charCount < ciphertextSize; j++) {
        ciphertext[charCount] = block[j];
        charCount++;
    }

    i = blockSize;
    while (i < plaintextSize && charCount < ciphertextSize) {

        for (j = 0; j < blockSize; j++) {
            block[j] = ciphertext[charCount-blockSize + j];
        }

        aes_encrypt_block(block, exKey, exKeySize, rounds);

        for (j = i; j < (i + blockSize) && j < plaintextSize; j++) {
            block[j % blockSize] = block[j % blockSize] ^ plaintext[j];
        }

        for (j = 0; j < blockSize && charCount < ciphertextSize; j++) {
            ciphertext[charCount] = block[j];
            charCount++;
        }

        i += blockSize;
    }
}

unsigned char aes_encrypt(const char *plaintext, unsigned short plaintextSize, 
    char *ciphertext, unsigned short ciphertextSize, 
    const char *key, unsigned char keySize, 
    const char *iv, unsigned char ivSize,
    unsigned char t, unsigned char m) {

    unsigned short i;

    unsigned short ptDataSize = plaintextSize + blockSize;
    unsigned char ptData[ptDataSize];
    initArray(ptData, ptDataSize);

    unsigned short ctDataSize = ciphertextSize + blockSize;
    unsigned char ctData[ctDataSize];
    initArray(ctData, ctDataSize);

    unsigned short keyDataSize = keySize + blockSize;
    unsigned char keyData[keyDataSize];
    initArray(keyData, keyDataSize);

    unsigned short ivDataSize = ivSize + blockSize;
    unsigned char ivData[ivDataSize];
    initArray(ivData, ivDataSize);

    if (t == 0)  { // Hex String

        ptDataSize = hexStringToUCharArray(plaintext, plaintextSize, ptData, ptDataSize, blockSize);
        ctDataSize = ptDataSize;
        keyDataSize = hexStringToUCharArray(key, keySize, keyData, keyDataSize, blockSize);

        if (iv) {
            ivDataSize = hexStringToUCharArray(iv, ivSize, ivData, ivDataSize, blockSize);
        }
    }
    // else if (t == 1 || t == 2) { // String or Bytes
        
        // Untested
        // for (i = 0; i < plaintextSize; i++) {
        //     ptData[i] = (unsigned char) plaintext[i];
        // }

        // ptDataSize = i;
        // ctDataSize = ptDataSize;

        // for (i = 0; i < keySize; i++) {
        //     keyData[i] = (unsigned char) key[i];
        // }

        // keyDataSize = i;

        // if (iv) {

        //     for (i = 0; i < blockSize; i++) {
        //         ivData[i] = (unsigned char) iv[i];
        //     }

        //     ivDataSize = i;
        // }
    // }
    else {
        return 0;
    }

    if (m == 0) { // ECB
        aes_ecb_encrypt(ptData, ptDataSize, ctData, ctDataSize, keyData, keyDataSize);
    }
    else if (m == 1) { // CBC
        aes_cbc_encrypt(ptData, ptDataSize, ctData, ctDataSize, keyData, keyDataSize, ivData);
    }
    else if (m == 2) { // CFB
        aes_cfb_encrypt(ptData, ptDataSize, ctData, ctDataSize, keyData, keyDataSize, ivData);
    }
    else {
        return 0;
    }

    if (t == 0) {
        uCharArrayToHexString(ctData, ctDataSize, ciphertext, ciphertextSize);
    }
    // else if (t == 1 || t == 2) {

        // Untested
        // ciphertext[0] = '\0';
        // char cd[1];
        // for (i = 0; i < ctDataSize; i++) {
        //     // TODO: Get rid of string function calls. They are more trouble than they are worth.
        //     char cs = (char) ctData[i];
        //     strncpy(cd, &cs, 1);
        //     strncat((char*) ciphertext, cd, 1);
        // }
    // }

    return 1;
}
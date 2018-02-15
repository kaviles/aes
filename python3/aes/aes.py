from constants import *
from utils import *

def mod_multiply(value1, value2):

    if value1 < value2:
        temp = value1
        value1 = value2
        value2 = temp

    temp = value2
    product = 0

    i = 0
    while temp > 0:

        if temp & 1:
            product = product ^ (value1 << i)

        temp = temp >> 1
        i = i + 1

    return product

def bit_count(value):

    count = 0

    while value > 0:
        value = value >> 1
        count = count + 1

    return count

def galoi_mult(value):
    
    bcv = bit_count(value)
    bcp = bit_count(poly)

    while bcv >= bcp:
        value = value ^ (poly << (bcv - bcp))
        bcv = bit_count(value)

    return value

def expand_key(key, keySize, exKeySize):

    exKey = []

    # Copy intial key to the beginning of expanded key.
    for i in range(0, keySize):
        exKey.append(key[i])

    # Generate the rest of the expanded key.
    r = 1 # Round. Should this be 0 or 1?
    while len(exKey) < exKeySize:

        # For the first four bytes of current round key... 
        # copy the previous four bytes, 
        # shift them left with wrapping, sbox substitution, 
        # XOR with the first four bytes of previous round 
        # finally, XOR rcon with first byte.

        t = []
        t.append(sbox[exKey[-3]] ^ exKey[-keySize] ^ rcons[r])
        t.append(sbox[exKey[-2]] ^ exKey[-keySize + 1])
        t.append(sbox[exKey[-1]] ^ exKey[-keySize + 2])
        t.append(sbox[exKey[-4]] ^ exKey[-keySize + 3])
        exKey.extend(t)

        # Fill out the rest of the current round key.
        # TODO: Use a more efficient mod function.
        while len(exKey) % keySize:
            exKey.append(exKey[-keySize] ^ exKey[-4])

        r = r + 1

    return exKey

def add_round_key(block, exKey, exKeySize, rounds):

    for i in range(0, blockSize):
        block[i] = block[i] ^ exKey[rounds*blockSize + i]

def substitute(block):

    for i in range(0, blockSize):
        block[i] = sbox[block[i]]

def shift_rows_left(block):

    # Row 0 stays the same

    # Row 1 is shifted left one with wrapping.
    temp1 = block[1]
    block[1] = block[5]
    block[5] = block[9]
    block[9] = block[13]
    block[13] = temp1

    # Row 2 is shifted left two with wrapping.
    temp1 = block[2]
    temp2 = block[6]
    block[2] = block[10]
    block[6] = block[14]
    block[10] = temp1
    block[14] = temp2

    # Row 3 is shifted left three with wrapping.
    # This can also be done by shifting to the right one over.
    temp1 = block[15]
    block[15] = block[11]
    block[11] = block[7]
    block[7] = block[3]
    block[3] = temp1

def mix_columns(block):

    i = 0
    for j in range(0, blockSize, 4):
        temp1 = [block[j], block[j+1], block[j+2], block[j+3]]

        for k in range(0, blockSize, 4):
            temp2 = [mix[k], mix[k+1], mix[k+2], mix[k+3]]

            val = 0
            for l in range(0, 4):
                val = val ^ galoi_mult(mod_multiply(temp1[l], temp2[l]))

            block[i] = val
            i = i + 1

def aes_encrypt_block(block, exKey, exKeySize, rounds):

    for i in range(0, rounds-1):

        # Add Round Key
        add_round_key(block, exKey, exKeySize, i)

        # SBox Substitution
        substitute(block)

        # Shift Rows Left
        shift_rows_left(block)

        if i < rounds-2:
            # Mix Columns
            mix_columns(block)

    i = i + 1

    # Add Round Key - Final Round
    add_round_key(block, exKey, exKeySize, i)

def aes_ecb_encrypt(plaintext, key, keySize):

    ptlen = len(plaintext)
    exKeySize = 176
    rounds = 11
    exKey = expand_key(key, keySize, exKeySize)

    ciphertext = []

    i = 0
    while i < ptlen:
        block = [0] * blockSize

        for j in range(i, min(i+blockSize, ptlen)):
            block[j % blockSize] = plaintext[j]

        aes_encrypt_block(block, exKey, 176, rounds)
        ciphertext.extend(block)

        i = i + blockSize

    return ciphertext


def aes_encrypt(plaintext, key, keySize, iv=None, t='hs', m='ecb'):

    ptData = [0] * blockSize
    keyData = [0] * keySize
    ivData = [0] * blockSize

    if t == 'hs': # Hex String
        ptData = hexStringToIntList(plaintext, blockSize)
        keyData = hexStringToIntList(key, keySize)
        
        if iv:
            ivData = hexStringToIntList(iv, blockSize)
        
    elif t == 's' or t == 'b': # String or Bytes
        ptData = stringToIntList(plaintext, blockSize)
        keyData = stringToIntList(key, keySize)
        
        if iv:
            ivData = bytesToIntList(iv, blockSize)
    else:
        raise ValueError("Invalid input type: " + str(t))

    ciphertext = []
    if m == 'ecb':
        ciphertext = aes_ecb_encrypt(ptData, keyData, keySize)
    elif m == 'cbc':
        pass
    elif m == 'cbf':
        pass
    else:
        raise ValueError("Invalid mode of encryption: " + str(m))

    if t == 'hs':
        return intListToHexString(ciphertext)

    elif t == 's' or t == 'b':
        return intListByteString(ciphertext)

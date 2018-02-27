import os
import unittest

from aes.aes import *

class Test_CBC128_MCT(unittest.TestCase):

    def setUp(self):

        dirname = os.path.abspath(os.path.dirname(__file__))
        self.path = os.path.join(dirname, "../../test_files/cbc/")

        self.filenames = [
            "mct/CBCMCT128"
        ]

        self.extension = ".txt";

    # Note this test will take anywhere from 3 - 5 minutes to complete.
    def test_CBC_MCT(self):

        for filename in self.filenames:

            with open(self.path + filename + self.extension, "r") as f:

                f.readline() # Read the first [ENCRYPT] line.

                key, iv, plaintext, ciphertext = getValuesFromFile(f, iv=True) # Read first set of data

                if key and iv and plaintext and ciphertext:

                    for i in range(0, 100):

                        for j in range(0, 1000):

                            if j == 0:

                                ctRes = aes_encrypt(plaintext, key, 16, iv, m='cbc')
                                plaintext = iv

                            else:

                                ctPrev = ctRes
                                ctRes = aes_encrypt(plaintext, key, 16, iv=ctPrev, m='cbc')
                                plaintext = ctPrev

                        self.assertEqual(ctRes, ciphertext)

                        # Since this is a 128-bit test...

                        nextKeyData = hexStringToIntList(key, 16)
                        ctData = hexStringToIntList(ctRes, blockSize)

                        for j in range(0, 16):
                            nextKeyData[j] = nextKeyData[j] ^ ctData[j]

                        nextKey = intListToHexString(nextKeyData)
                        nextIV = ctRes
                        nextPt = ctPrev

                        key, iv, plaintext, ciphertext = getValuesFromFile(f, iv=True)

                        if not key and not plaintext and not ciphertext:
                            break

                        self.assertEqual(nextKey, key)
                        self.assertEqual(nextIV, iv)
                        self.assertEqual(nextPt, plaintext)

if __name__ == '__main__':
    unittest.main()
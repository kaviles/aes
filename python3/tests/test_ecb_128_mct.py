import os
import unittest

from aes.aes import *

class Test_ECB128_MCT(unittest.TestCase):

    def setUp(self):

        dirname = os.path.abspath(os.path.dirname(__file__))
        self.path = os.path.join(dirname, "../../test_files/ecb/")

        self.filenames = [
            "mct/ECBMCT128"
        ]

        self.extension = ".txt";

    # Note this test will take at least 3 minutes to complete
    def test_ECB_MCT(self):

        for filename in self.filenames:

            with open(self.path + filename + self.extension, "r") as f:

                f.readline() # Read the first [ENCRYPT] line.

                key, iv, plaintext, ciphertext = getValuesFromFile(f) # Read first set of data

                if key and plaintext and ciphertext:

                    for i in range(0, 100):

                        for j in range(0, 1000):
                            ctRes = aes_encrypt(plaintext, key, 16)
                            plaintext = ctRes

                        self.assertEqual(ctRes, ciphertext)

                        # Since this is a 128-bit test...

                        nextKeyData = hexStringToIntList(key, 16)
                        ctResData = hexStringToIntList(ctRes, blockSize)

                        for j in range(0, 16):
                            nextKeyData[j] = nextKeyData[j] ^ ctResData[j]

                        nextKey = intListToHexString(nextKeyData)

                        key, iv, plaintext, ciphertext = getValuesFromFile(f)

                        if not key and not plaintext and not ciphertext:
                            break

                        self.assertEqual(nextKey, key)

if __name__ == '__main__':
    unittest.main()
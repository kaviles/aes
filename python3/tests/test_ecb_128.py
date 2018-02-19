import os
import unittest

from aes.aes import *

class Test_ECB128(unittest.TestCase):

    def setUp(self):

        dirname = os.path.abspath(os.path.dirname(__file__))
        self.path = os.path.join(dirname, "../../test_files/ecb/")

        self.filenames = [
            "kat/ECBGFSbox128",
            "kat/ECBKeySbox128",
            "kat/ECBVarKey128",
            "kat/ECBVarTxt128",
            "mmt/ECBMMT128"
        ]

        self.extension = ".txt";

    def test_ECB(self):

        for filename in self.filenames:

            with open(self.path + filename + self.extension, "r") as f:

                f.readline() # Read the first [ENCRYPT] line.

                while True:

                    key, iv, plaintext, ciphertext = getValuesFromFile(f)

                    if key and plaintext and ciphertext:

                        ctRes = aes_encrypt(plaintext, key, 16)
                        self.assertEqual(ctRes, ciphertext)

                    else:
                        break

if __name__ == '__main__':
    unittest.main()
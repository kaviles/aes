import os
import unittest

from aes.aes import *

class Test_ECB128(unittest.TestCase):

    def setUp(self):

        dirname = os.path.abspath(os.path.dirname(__file__))
        self.path = os.path.join(dirname, "../../test_files/cbc/")

        self.filenames = [
            "kat/CBCGFSbox128",
            "kat/CBCKeySbox128",
            "kat/CBCVarKey128",
            "kat/CBCVarTxt128",
            "mmt/CBCMMT128"
        ]

        self.extension = ".txt";

    def test_CBC(self):

        for filename in self.filenames:

            with open(self.path + filename + self.extension, "r") as f:

                f.readline() # Read the first [ENCRYPT] line.

                while True:

                    key, iv, plaintext, ciphertext = getValuesFromFile(f, iv=True)

                    if key and plaintext and ciphertext:

                        ctRes = aes_encrypt(plaintext, key, 16, iv, m='cbc')
                        self.assertEqual(ctRes, ciphertext)

                    else:
                        break

if __name__ == '__main__':
    unittest.main()
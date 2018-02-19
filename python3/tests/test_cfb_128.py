import os
import unittest

from aes.aes import *

class Test_CFB128(unittest.TestCase):

    def setUp(self):

        dirname = os.path.abspath(os.path.dirname(__file__))
        self.path = os.path.join(dirname, "../../test_files/cfb/")

        self.filenames128 = [
            "kat/CFB128GFSbox128",
            "kat/CFB128KeySbox128",
            "kat/CFB128VarKey128",
            "kat/CFB128VarTxt128",
            "mmt/CFB128MMT128"
        ]

        self.filenames8 = [
            "kat/CFB8GFSbox128",
            "kat/CFB8KeySbox128",
            "kat/CFB8VarKey128",
            "kat/CFB8VarTxt128",
            "mmt/CFB8MMT128"
        ]

        self.filenames1 = [
            "kat/CFB1GFSbox128",
            "kat/CFB1KeySbox128",
            "kat/CFB1VarKey128",
            "kat/CFB1VarTxt128",
            "mmt/CFB1MMT128"
        ]

        self.extension = ".txt";

    def test_CFB128(self):

        for filename in self.filenames128:

            with open(self.path + filename + self.extension, "r") as f:

                f.readline() # Read the first [ENCRYPT] line.

                while True:

                    key, iv, plaintext, ciphertext = getValuesFromFile(f, iv=True)

                    if key and plaintext and ciphertext:

                        ctRes = aes_encrypt(plaintext, key, 16, iv, m='cfb', b=128)
                        self.assertEqual(ctRes, ciphertext)

                    else:
                        break

    def test_CFB8(self):

        for filename in self.filenames8:

            with open(self.path + filename + self.extension, "r") as f:

                f.readline() # Read the first [ENCRYPT] line.

                while True:

                    key, iv, plaintext, ciphertext = getValuesFromFile(f, iv=True)

                    if key and plaintext and ciphertext:

                        ctRes = aes_encrypt(plaintext, key, 16, iv, m='cfb', b=8)
                        self.assertEqual(ctRes, ciphertext)

                    else:
                        break

    def test_CFB1(self):

        for filename in self.filenames1:
            print(filename)

            with open(self.path + filename + self.extension, "r") as f:

                f.readline() # Read the first [ENCRYPT] line.

                while True:

                    key, iv, plaintext, ciphertext = getValuesFromFile(f, iv=True)

                    if key and plaintext and ciphertext:

                        ctRes = aes_encrypt(plaintext, key, 16, iv, m='cfb', b=1)
                        self.assertEqual(ctRes, ciphertext)

                    else:
                        break

if __name__ == '__main__':
    unittest.main()
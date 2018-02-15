import unittest
from aes.aes import *
from cbc_128_kat_res import *

class Test_CBC128KAT(unittest.TestCase):

	def test_CBCGFSbox128(self):

		for item in CBCGFSbox128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cbc')
			self.assertEqual(ciphertext, item[3])

	def test_CBCKeySbox128(self):

		for item in CBCKeySbox128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cbc')
			self.assertEqual(ciphertext, item[3])

	def test_CBCVarKey128(self):

		for item in CBCVarKey128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cbc')
			self.assertEqual(ciphertext, item[3])

	def test_CBCVarText128(self):

		for item in CBCVarText128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cbc')
			self.assertEqual(ciphertext, item[3])
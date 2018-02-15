import unittest
from aes.aes import *
from ecb_128_kat_res import *

class Test_ECB128KAT(unittest.TestCase):

	def test_ECBGFSbox128(self):

		for item in ECBGFSbox128:

			ciphertext = aes_encrypt(item[1], item[0], 16)
			self.assertEqual(ciphertext, item[2])

	def test_ECBKeySbox128(self):

		for item in ECBKeySbox128:

			ciphertext = aes_encrypt(item[1], item[0], 16)
			self.assertEqual(ciphertext, item[2])

	def test_ECBVarKey128(self):

		for item in ECBVarKey128:

			ciphertext = aes_encrypt(item[1], item[0], 16)
			self.assertEqual(ciphertext, item[2])

	def test_ECBVarText128(self):

		for item in ECBVarText128:

			ciphertext = aes_encrypt(item[1], item[0], 16)
			self.assertEqual(ciphertext, item[2])
import unittest
from aes.aes import *
from cfb_128_kat_res import *

class Test_CFB128128KAT(unittest.TestCase):

	def test_CFB128GFSbox128(self):

		for item in CFB128GFSbox128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])

	def test_CFB128KeySbox128(self):

		for item in CFB128KeySbox128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])

	def test_CFB128VarKey128(self):

		for item in CFB128VarKey128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])

	def test_CFB128VarText128(self):

		for item in CFB128VarText128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])

class Test_CFB8128KAT(unittest.TestCase):

	def test_CFB8GFSbox128(self):

		for item in CFB8GFSbox128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])

	def test_CFB8KeySbox128(self):

		for item in CFB8KeySbox128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])

	def test_CFB8VarKey128(self):

		for item in CFB8VarKey128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])

	def test_CFB8VarText128(self):

		for item in CFB8VarText128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])


class Test_CFB1128KAT(unittest.TestCase):

	def test_CFB1GFSbox128(self):

		for item in CFB1GFSbox128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])

	def test_CFB1KeySbox128(self):

		for item in CFB1KeySbox128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])

	def test_CFB1VarKey128(self):

		for item in CFB1VarKey128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])

	def test_CFB1VarText128(self):

		for item in CFB1VarText128:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])









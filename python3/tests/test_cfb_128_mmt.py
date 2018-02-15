import unittest
from aes.aes import *
from cfb_128_mmt_res import *

class Test_CFB128MMT(unittest.TestCase):

	def test_CFBMMT128(self):

		for item in CFB128MMT:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])


class Test_CFB8MMT(unittest.TestCase):

	def test_CFBMMT8(self):

		for item in CFB8MMT:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])


class Test_CFB1MMT(unittest.TestCase):

	def test_CFBMMT1(self):

		for item in CFB1MMT:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cfb')
			self.assertEqual(ciphertext, item[3])

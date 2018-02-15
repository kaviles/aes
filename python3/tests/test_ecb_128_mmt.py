import unittest
from aes.aes import *
from ecb_128_mmt_res import *

class Test_ECB128MMT(unittest.TestCase):

	def test_ECBMMT128(self):

		for item in ECB128MMT:

			ciphertext = aes_encrypt(item[1], item[0], 16)
			self.assertEqual(ciphertext, item[2])

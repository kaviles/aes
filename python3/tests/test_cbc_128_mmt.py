import unittest
from aes.aes import *
from cbc_128_mmt_res import *

class Test_CBC128MMT(unittest.TestCase):

	def test_CBCMMT128(self):

		for item in CBC128MMT:

			ciphertext = aes_encrypt(item[2], item[0], 16, item[1], m='cbc')
			self.assertEqual(ciphertext, item[3])

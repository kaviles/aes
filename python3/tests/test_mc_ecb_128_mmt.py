# Monte Carlo- ECB Validation function 

# Request file profivdes KEY and PLAINTEXT

import unittest
from aes.aes import *
from constants import *
from utils import *

from ecb_128_mmt_res import *


class TEST_MC_ECB(unittest.TestCase):

	def test_MCECBMMT128(self):

		for item in ECB128MMT:

			KEY = item[0]
			PLAINTEXT = item[1]

			Keys = []
			CIPHER []
			PLAIN = []

			Keys[0] = KEY
			PLAIN[0] = PLAINTEXT

			for i in range(100):
				print Keys[i]
				print PLAIN[0]

				for j in range(1000):
					CIPHER[j] = aes_encrypt(PLAIN[j], Keys[i], 16)

					PLAIN[j+1] = CIPHER[j]

				print CIPHER[j]

				Keys[i+1] = Keys[i] ^ CIPHER[j]

				PLAIN[0] = CIPHER[j]

# Monte Carlo- ECB Validation function 

# Request file profivdes KEY and PLAINTEXT

import unittest
from aes.aes import *

from cbc_128_mmt_res import *

class Test_MCCBCMMT128(unittest.TestCase):

	def test_MCCBCMMT128(self):

		for item in CBC128MMT:

			KEY = item[0]
			PLAINTEXT = item[2]
			IV = item[1]

			Keys = []
			CIPHER []
			PLAIN = []
			INVEC = []

			Keys[0] = KEY
			PLAIN[0] = PLAINTEXT
			INVEC[0] - IV

			for i in range(100):
				print "".join(Keys[i])
				print "".join(INVEC[i])
				print "".join(PLAIN[0])

				for j in range(1000):
					if(j ==0):
						CIPHER[j] = aes_encrypt(PLAIN[j], Keys[i], 16, INVEC[i], m = 'cbc')
						PLAIN[j+1] = INVEC[i]
					else:
						CIPHER[j] = aes_encrypt(PLAIN[j], Keys[i], 16)
						PLAIN[j+1] = CIPHER[j-1]


				print "".join(CIPHER[j])

				Keys[i+1] = Keys[i] ^ CIPHER[j]

				INVEC[i+1] = CIPHER[j]

				PLAIN[0] = CIPHER[j-1]

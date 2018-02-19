def genPaddedList(length, padVal):

	div = length // padVal
	rem = length % padVal
	
	l = [0] * padVal * div

	if rem:
		l.extend([0] * padVal)

	return l

def intListToHexString(data):

	s = ''

	for i in range(0, len(data)):
		s = s + hex(data[i])[2:].rjust(2, '0')

	return s

def intListToByteString(data):

	return bytes(data)

def hexStringToIntList(data, padVal):

	l = len(data)
	intList = []
	for i in range(0, l, 2):
		intList.append(int(data[i:i+2], 16))

	l = len(intList)
	rem = l % padVal
	if rem:
		intList.extend([0] * (padVal - rem))

	return intList

def binStringToIntList(data, bitVal):

	l = len(data)
	intList = []
	for i in range(0, l, 8):
		intList.append(int(data[i:i+8].ljust(8, '0')))

	# l = len(intList)
	# rem = l % 8
	# if rem:
	# 	intList.extend([0] * (8 - rem))

	return intList

def bytesToIntList(data, padVal):

	l = len(data)

	intList = genPaddedList(l, padVal)

	for i in range(0, l):
		intList[i] = ord(data[i])

	return intList

def removeCharacter(string, c):

	return string.replace(c, "")

def getValuesFromFile(file, iv=None):

	key = file.readline() # Delete newline (\r\n) characters

	if key:
		key = removeCharacter(key, "\n")

	if iv:

		iv = file.readline()
		if iv:
			iv = removeCharacter(iv, "\n")

	plaintext = file.readline()
	if plaintext:
		plaintext = removeCharacter(plaintext, "\n")

	ciphertext = file.readline()
	if ciphertext:
		ciphertext = removeCharacter(ciphertext, "\n")

	return (key, iv, plaintext, ciphertext)


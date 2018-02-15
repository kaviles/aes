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
	if l % padVal:
		intList.extend([0] * (padVal - l))

	return intList

def bytesToIntList(data, padVal):

	l = len(data)

	intList = genPaddedList(l, padVal)

	for i in range(0, l):
		intList[i] = ord(data[i])

	return intList

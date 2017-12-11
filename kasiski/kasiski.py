#!/usr/bin/python

import sys
import fractions

def kasiski_get_len(input, digram_len):
	intervals = []

	for i in xrange(0, len(input)):
		for j in xrange(i + 1, len(input)):
			if (input[i:i + digram_len] == input[j:j + digram_len]):
				intervals.append(j - i)

	if (len(intervals) == 0):
		return 0
	if (len(intervals) == 1):
		return intervals[0]

	gcds = {}
	for i in xrange(0, len(intervals)):
		for j in xrange(i + 1, len(intervals)):
			agcd = fractions.gcd(intervals[i], intervals[j])
			if (gcds.has_key(agcd)):
				gcds[agcd] += 1
			else:
				gcds[agcd] = 1

	if (len(gcds.items()) == 0):
		return 0
	if (len(gcds.items()) == 1):
		return gcds.items()[0][0]

	if (gcds.has_key(1)):
		del gcds[1]
	# print gcds

	keylen1 = max(gcds.items(), key = lambda item: item[1])
	del gcds[keylen1[0]]
	keylen2 = max(gcds.items(), key = lambda item: item[1])
	del gcds[keylen2[0]]
	keylen3 = max(gcds.items(), key = lambda item: item[1])

	return [keylen1, keylen2, keylen3]

if (len(sys.argv) < 3):
	print "Usage: kasiski.py <file> <digram_len>"
else:
	f = open(sys.argv[1])
	text = f.read()
	print kasiski_get_len(text, int(sys.argv[2]))

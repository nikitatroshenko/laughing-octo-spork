#!/usr/bin/python

import sys
import collections

etalon_freqs = {
	'A': 0.08167,
	'B': 0.01492,
	'C': 0.02782,
	'D': 0.04253,
	'E': 0.12702,
	'F': 0.0228,
	'G': 0.02015,
	'H': 0.06094,
	'I': 0.06966,
	'J': 0.00153,
	'K': 0.00772,
	'L': 0.04025,
	'M': 0.02406,
	'N': 0.06749,
	'O': 0.07507,
	'P': 0.01929,
	'Q': 0.00095,
	'R': 0.05987,
	'S': 0.06327,
	'T': 0.09056,
	'U': 0.02758,
	'V': 0.00978,
	'W': 0.0236,
	'X': 0.0015,
	'Y': 0.01974,
	'Z': 0.00074
}

def get_diff(selection1, selection2):
	diffs = map(lambda i: abs(selection2[i] - selection1[i]), xrange(0, len(selection1)))
	return max(diffs);

def analyse(input_str, keylen):
	actual_freqs = []
	ekey = []
	key = []

	for i in xrange(0, keylen):
		actual_freqs.append(dict(map(lambda c: (c, 0), etalon_freqs.keys())))
		textlen = 0
		for j in xrange(i, len(input_str), keylen):
			char = input_str[j]
			if (not etalon_freqs.has_key(char)):
				continue
			if (actual_freqs[i].has_key(char)):
				actual_freqs[i][char] += 1
			else:
				actual_freqs[i][char] = 1
			textlen += 1

		# print actual_freqs[i]
		# print map(lambda item: (item[0], item[1] * textlen), etalon_freqs.items())
		# print "sum: " + str(reduce(lambda item1, item2: item1 + item2, map(lambda item: item[1], actual_freqs[i].items())))
		
		# normalize actual histogram
		actual_freqs[i] = sorted(map(lambda item: (item[0], float(item[1]) / textlen), actual_freqs[i].items()), key = lambda item: item[0])

		mindiff = 1
		# actual_histogram = collections.deque(map(lambda item: item[1], sorted(actual_freqs[i].items(), key = lambda item: item[0])))
		etalon_histogram = collections.deque(map(lambda item: item[1], sorted(etalon_freqs.items(), key = lambda item: item[0])))
		probable_key = actual_freqs[i][0][0]
		
		print "For " + str(i) + "th:"
		for actual_key in actual_freqs[i]:
			actual_histogram = collections.deque(map(lambda item: item[1], actual_freqs[i]))
			actual_histogram.rotate(-ord(actual_key[0]) + ord(actual_freqs[i][0][0]))

			to_print = collections.deque(map(lambda item: item[0], actual_freqs[i]))
			to_print.rotate(-ord(actual_key[0]) + ord(actual_freqs[i][0][0]))
			# print to_print

			currdiff = get_diff(actual_histogram, etalon_histogram)
			# actual_histogram.rotate(-1)
			print str((actual_key[0], currdiff))
			if currdiff < mindiff:
				mindiff = currdiff
				probable_key = actual_key[0]

		# mindelta = 1
		# ekey.append(('N', 'N'))
		# for item in actual_freqs[i]:
		# 	for eitem in etalon_freqs.items():
		# 		if (abs(item[1] - eitem[1]) < mindelta):
		# 			mindelta = abs(item[1] - eitem[1])
		# 			ekey[i] = (item[0], eitem[0])

		# emaxfreq = max(etalon_freqs.items(), key = lambda item: item[1])[0]
		# amaxfreq = max(actual_freqs[i].items(), key = lambda item: item[1])[0]
		amaxfreq = probable_key
		emaxfreq = etalon_freqs.keys()[0]
		key.append(chr((ord(amaxfreq) - ord(emaxfreq)) % len(etalon_freqs.items()) + ord('A')))

	return key

def main():
	if (len(sys.argv) < 3):
		print "Usage: kasiski.py <file> <keylen>"
	else:
		f = open(sys.argv[1])
		text = f.read()
		print analyse(text, int(sys.argv[2]))

if __name__ == '__main__':
	main()
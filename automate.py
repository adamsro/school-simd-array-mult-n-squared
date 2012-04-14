#!/bin/pyhton
import os
import sys

def main():
	step = [1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000,
			512000, 1024000, 2048000, 4096000, 8192000]
	for n in step:
		os.system("g++  -DNUM=%d  -o arraymult  arraymult.cpp simd.o  -lm -fopenmp" % (n))
		os.system("./arraymult")

if __name__ == "__main__":
	main()

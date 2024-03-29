#!/bin/pyhton
import os
import sys

def main():
	step = [1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000, 256000,
			512000, 1024000, 2048000, 4096000, 8192000]
	n = 32
	for n in range(32, 10000, n**2):
		os.system("g++  -DNUM=%d  -o autocorrelation autocorrelation.cpp simd.o  -lm -fopenmp" % (n))
		os.system("./autocorrelation")

if __name__ == "__main__":
	main()

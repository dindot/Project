Assignment 7 - Lempel-Ziv Compression

To use this program the user must enter the desired program of either encode or decode, which will compress and decompress a given infile to outfile, respectively. To run the desired program, user must type in ./encode or ./decode followed by supported options of -i, -o, -v. -i will allow user to enter a desired file to be read in as input, while -o will allow the user to enter a file to which output will be written to. -v results in displaying statistics of the compression and decompression of percentages of before and after encoding/decoding. The user must enter both the -i and -o in either of the encode or decode. This would be ./encode -i infile -o outfile to allow to program to run. Additionally, the user can use io redirection to feed in a file desired to be ouput to another file, using ./encode < infile > outfile as an example.

The program does the appropriate encoding, but includes an additional character when compared to the provided test files of the actual encoded file, causing it to be slightly off. 
To build program type in make or make all. From make infer: The memory leak error is later resolved,because the word is getting calloc, which returns a pointer that will be accessible. The error of trie.c:33: DEADSTORE, is off because in trie.c on line 47 and line 72, next gets used as its address is being assigned to curr. The NULL DEREFERNCE error that occurs in encode and decode, which is in the part of the algorithm given, are handled in when they get passed into triestep and word append functions.


Built in UNIX timeshare terminal

Author: Din Bostandzic

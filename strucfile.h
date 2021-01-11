#pragma once
#include "memFile.h"
#include <iostream>

using namespace std;
extern memFileCls* fileData;
struct strucfile {
	memFileObj lsFile;
	void open(char * defile);
	void close();
	unsigned int lsrgllength(char * deregel);
//	unsigned int lsdergllength(char * deregel, unsigned int *regelno);
	unsigned int lsdergllength(char * deregel, unsigned int *regelno);
	unsigned int lsfilelngth(char * lsfile);
	unsigned int stwebfile(const char * demap, uint8_t * demaplength, const char * defile, uint8_t * defilelength, char * stuur, char* voeging, uint8_t voeginglen);
	void beginregel(const char * demap, uint8_t* demaplength, const char * defile, uint8_t* defilelength);
	void fopen(const char * demap, uint8_t * demaplength, const char * defile, uint8_t * defilelength);
};

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
	unsigned int stwebfile(char * demap, unsigned __int8 * demaplength, char * defile, unsigned __int8 * defilelength, char * stuur, char* voeging, unsigned __int8 voeginglen);
	void beginregel(char * demap, unsigned __int8* demaplength, char * defile, unsigned __int8* defilelength);
	void fopen(char * demap, unsigned __int8 * demaplength, char * defile, unsigned __int8 * defilelength);
};

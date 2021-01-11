#include "strucfile.h"

using namespace std;

void strucfile::fopen(const char * demap, uint8_t * demaplength, const char * defile, uint8_t * defilelength) {
	char stfile[64] = { "" };
	int8_t stfilelen = 0;
	if (*demaplength > 0) {
		strncpy_s(&stfile[stfilelen], *demaplength + 1, demap, *demaplength);
		stfilelen = stfilelen + *demaplength; stfile[stfilelen++] = '/';
	}
	strncpy_s(&stfile[stfilelen], *defilelength + 1, defile, *defilelength); stfilelen = stfilelen + *defilelength;
	stfile[stfilelen++] = '\0';
	open(stfile); 
}
void strucfile::beginregel(const char * demap, uint8_t* demaplength, const char * defile, uint8_t* defilelength) {
	fopen(demap, demaplength, defile, defilelength);
}
void strucfile::open(char * defile) {
	lsFile.openStr(defile, fileData);
}
void strucfile::close() {
}
//unsigned int strucfile::lsdergllength(char * deregel, unsigned int *regelno) {
	//unsigned int lslength = 0;
	//bool eerst = 1;
	//char thischar = '~';
	//for (unsigned int tel = 0; tel < *regelno; tel++) {
	//	while (thischar != '\n') {
		//	thischar = bestand.get();
		//}
		//thischar = '~';
	//}
	//thischar = '~';
	//while (!bestand.eof()) {
	//	if (!eerst) {
		//	*(deregel + lslength++) = thischar;
		//}
		//else {
//			eerst = 0;
		//}
		//thischar = bestand.get();
		//cout << thischar;
//		if (thischar == '\n') {
//			break;
//		}
//	}
//	*(deregel + lslength) = '\0'; 
//	return lslength;
//}
unsigned int strucfile::lsrgllength(char * deregel) {
	strbasprc bas;
	return bas.charPLen(bas.charPLsR(deregel, lsFile.file, lsFile.loc));
}
unsigned int strucfile::lsdergllength(char * deregel, unsigned int *regelno) {
	strbasprc bas;
	return bas.charPLen(bas.charPLsDR(*regelno, deregel, lsFile.file, lsFile.loc));
}

unsigned int strucfile::stwebfile(const char * demap, uint8_t * demaplength, const char * defile, uint8_t * defilelength, char * stuur, char* voeging, uint8_t voeginglen) {
	unsigned int uitkomst = 0;
	uint8_t idtel = 0;
	char thischar = '~';
	fopen(demap, demaplength, defile, defilelength);
	//cout << demap << "\nLen: " << *demaplength << defile << "\nLen: " << *defilelength << "\n\n";
	while (thischar = lsFile.get()) switch (idtel) {
	case 0:
		if (thischar == '!') {
			idtel++;
		}
		else {
			*(stuur + uitkomst++) = thischar;
		}
		break;
	case 1:
		if (thischar == '!') {
			idtel++;
		}
		else {
			*(stuur + uitkomst++) = '!';
			*(stuur + uitkomst++) = thischar;
			idtel = 0;
		}
		break;
	case 2:
		if (thischar == 'I') {
			idtel++;
		}
		else {
			*(stuur + uitkomst++) = '!';
			*(stuur + uitkomst++) = '!';
			*(stuur + uitkomst++) = thischar;
			idtel = 0;
		}
		break;
	case 3:
		if (thischar == 'D') {
			strncpy_s(stuur + uitkomst, voeginglen + 1, voeging, voeginglen); uitkomst = uitkomst + voeginglen;
		}
		else {
			*(stuur + uitkomst++) = '!';
			*(stuur + uitkomst++) = '!';
			*(stuur + uitkomst++) = 'I';
			*(stuur + uitkomst++) = thischar;
		}
		idtel = 0;
		break;
	}
	return uitkomst;
}

unsigned int strucfile::lsfilelngth(char * lsfile) {
	strbasprc bas; unsigned int l = bas.charPLen(lsFile.file); 
	strncpy_s(lsfile, l + 1, lsFile.file, l);
	return l;
}

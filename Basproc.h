#pragma once
#include <stdint.h>
#include "Custom/custom_string.h"

struct strbasprc {
	static char* charPHeap(char* x, unsigned int len, unsigned int& vloc, unsigned int, unsigned int& vTLen);
	static char* charPHeapVgDel(char* del, unsigned long& len, char* voeg, unsigned int& vloc, unsigned int vlen, unsigned int fac, unsigned int& vTLen);
	static bool vergCharP(const char* x, const char* y);
	static char* remCommCharP(char* x);
	static bool vergCharPH(const char* x, const char* y);
	static bool vergCharPH_path(const char* x, const char* y);
	static unsigned int charPLen(const char* x);
	static char* charPvoeg(char* x, char* voeg);
	static unsigned int charPVI(char* x, const char* voeg);
	static char* charPVC(char* x, char* voeg, unsigned int len);
	static unsigned int charPVCI(char* x, char* voeg, unsigned int len);
	static char* charPLsR(char* bf, char* fl, unsigned long& cnt);
	static char* charPLsDR(unsigned int rlNo, char* bf, char* fl, unsigned long& cnt);
	static int indChar(char x, const char* y);
	static bool hfdlttr(char * devar, char&& letter);
	static bool hfdlttr_pp(char* devar, char* letter);
	static bool hfdLttr(char devar, char letter);
	static bool verg8(char* een, unsigned int* eenlen, char* twee, uint8_t* tweelen, bool&& hfd);
	static uint8_t cv16waarde(char* char0);
	static char cv16char0(unsigned int& waarde);
	static char cv16char1(unsigned int& waarde);
	static bool isStelsel60(char x) { if ((x >= '0' && x <= '9') || (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'w')) return true; return false; };
	static bool isNo(char x) { if (x >= '0' && x <= '9') return true; return false; };
	static unsigned int cvcharlngth(uint8_t stelsel, unsigned long getal, char* stuur);
	static unsigned long macht(uint8_t stelsel, unsigned int demacht);
	static char cvintcharchar(uint8_t aant);
	static char cvintcharint(char x);
	static unsigned long cvintcharStr(char* x) {
		uint8_t len = charPLen(x); unsigned long y = 0; for (uint8_t tel = 0; tel < len; tel++) y += cvintcharint(*(x + tel)) * (macht(60, len - 1 - tel)); return y;
	};
	static unsigned int toStringF (int64_t INg, char* TO) {
		int UIT = 0, TIEN = 0;
		if (INg < 0) INg *= -1, TO[UIT++] = '-';
		for (int FAC = 10; INg / FAC; FAC *= 10) TIEN++;
		int64_t DL = 1; for (int T = 0; T < TIEN; T++) DL *= 10;
		for (int T = 0; T < TIEN; T++, DL /= 10) TO[UIT++] = INg / DL % 10 + '0';
		TO[UIT++] = INg % 10 + '0';
		return UIT;
	};

};
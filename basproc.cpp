#include "basproc.h"
#include <string>

char* strbasprc::charPHeap(char* x, unsigned int len, unsigned int& vloc , unsigned int fac, unsigned int& vTLen) {
	char* y = new char[len + 1];
	for (unsigned int t = 0; t < len; (vloc += 1) %= fac) y[len + t++] = x[vloc]; y[(len += len)] = '\0';
	if ((vTLen -= len) < vloc) for (unsigned int t = 0; t < vTLen || (vloc = 0); t++) x[t] = x[vloc + t];
	return x;
}

char* strbasprc::charPHeapVgDel(char* del, unsigned long& len, char* voeg, unsigned int& vloc, unsigned int vlen, unsigned int fac, unsigned int& vTLen) {
	char* x = new char[len + vlen + 1]; for (unsigned long t = 0; t < len; t++) x[t] = del[t]; delete[len + 1] del; 
	for (unsigned int t = 0; t < vlen; (vloc += 1) %= fac) x[len + t++] = voeg[vloc]; x[(len += vlen)] = '\0';
	if ((vTLen -= vlen) < vloc) for (unsigned int t = 0; t < vTLen || (vloc = 0); t++) voeg[t] = voeg[vloc + t];
	return x;
}

bool strbasprc::vergCharP(char* x, char* y) {
	unsigned int z = charPLen(x); 
	
	if (z != charPLen(y)) return false; for (unsigned int t = 0; t < z; t++) if (x[t] != y[t]) return false;
	return true;
}

char* strbasprc::remCommCharP(char* x) {
	int sk = indChar('/', x);
	if (sk != -1 && indChar('/', x + sk + 1) != -1) x[sk] = '\0';
	return x;
}

bool strbasprc::vergCharPH(char* x, char* y) {
	unsigned int z = charPLen(x);
	if (z != charPLen(y)) return false; for (unsigned int t = 0; t < z; t++) if (!hfdLttr(x[t], y[t])) return false;
	return true;
}

unsigned int strbasprc::charPLen(char* x) {
	unsigned int tel = 0; 
	while 
		(x[tel] != '\0') 
		tel++; 
	return tel;
}

char* strbasprc::charPvoeg(char* x, char* voeg) {
	unsigned int y = charPLen(voeg);
	strncpy_s(x + charPLen(x), y + 1, voeg, y);
	return x;
}

unsigned int strbasprc::charPVI(char* x, char* voeg) {
	unsigned int y = charPLen(voeg), z = charPLen(x);
	strncpy_s(x + z, y + 1, voeg, y);
	return z + y;
}

unsigned int strbasprc::charPVCI(char* x, char* voeg, unsigned int len) {
	unsigned int y = charPLen(voeg);
	strncpy_s(x + len, y + 1, voeg, y);
	return len + y;
}

char* strbasprc::charPVC(char* x, char* voeg, unsigned int len) {
	unsigned int y = charPLen(voeg);
	strncpy_s(x + len, y + 1, voeg, y);
	return x;
}

char* strbasprc::charPLsR(char* bf, char* fl, unsigned long& cnt) {
	bool flag = false, flag2 = false; unsigned int Cnt = 0; 
	int x = indChar('\n', fl + cnt), 
		y = indChar('\r', fl + cnt); 
	if (y != -1) if (x != -1) if (x > y && (flag = true)) Cnt = y; else Cnt = x; else Cnt = y; else if (x != -1) Cnt = x; else { flag2 = true, Cnt = indChar('\0', fl + cnt); }
	strncpy_s(bf, Cnt + 1, fl + cnt, Cnt); unsigned __int8 tt = 0; if (flag && fl[cnt + Cnt + 1] == '\n') tt = 2; else if (!flag2) tt = 1;
	cnt += Cnt + tt; return bf;
}

char* strbasprc::charPLsDR(unsigned int rlNo, char* bf, char* fl, unsigned long& cnt) {
	bool flag = false, flag2 = false; 
	unsigned int Cnt = 0;
	for (unsigned int t = 0; t < rlNo; t++) {
		int x = indChar('\n', fl + cnt), y = indChar('\r', fl + cnt);
		if (y != -1)
			if (x != -1)
				if (x > y)
					if (x - y == 1) cnt += x + 1;
					else cnt += y + 1;
				else cnt += x + 1;
			else cnt += y + 1;
		else if (x != -1) cnt += x + 1;
		else { cnt += indChar('\0', fl + cnt); break; }
	}
	int x = indChar('\n', fl + cnt), y = indChar('\r', fl + cnt);
	if (y != -1) if (x != -1) if (x > y && (flag = true)) Cnt = y; else Cnt = x; else Cnt = y; else if (x != -1) Cnt = x; else { flag2 = true, Cnt = indChar('\0', fl + cnt); }
	strncpy_s(bf, Cnt + 1, fl + cnt, Cnt); unsigned __int8 tt = 0; if (flag && fl[cnt + Cnt + 1] == '\n') tt = 2; else if (!flag2) tt = 1;
	cnt += Cnt + tt; 
	return bf;
}

int strbasprc::indChar(char x, char* y) {
	for (unsigned int tel = 0, max = charPLen(y); tel < max || x == '\0'; tel++) if (x == y[tel]) return tel; return -1;
}

bool strbasprc::hfdlttr(char* devar, char&& letter) {
	if (letter >= 'A' && letter <= 'Z') {
		if (letter == *devar || (letter - 'A') + 'a' == *devar) {
			return true;
		}
		return false;
	}
	else if (letter >= 'a' && letter <= 'z') {
		if (letter == *devar || (letter - 'a') + 'A' == *devar) {
			return true;
		}
		return false;
	}
	else {
		if (letter == *devar) {
			return true;
		}
		return false;
	}
}

bool strbasprc::hfdLttr(char devar, char letter) {
	if (letter >= 'A' && letter <= 'Z') {
		if (letter == devar || (letter - 'A') + 'a' == devar) {
			return true;
		}
		return false;
	}
	else if (letter >= 'a' && letter <= 'z') {
		if (letter == devar || (letter - 'a') + 'A' == devar) {
			return true;
		}
		return false;
	}
	else {
		if (letter == devar) {
			return true;
		}
		return false;
	}
}

bool strbasprc::hfdlttr_pp(char* devar, char* letter) {
	if (*letter >= 'A' && *letter <= 'Z') {
		if (*letter == *devar || (*letter - 'A') + 'a' == *devar) {
			return true;
		}
		return false;
	}
	else if (*letter >= 'a' && *letter <= 'z') {
		if (*letter == *devar || (*letter - 'a') + 'A' == *devar) {
			return true;
		}
		return false;
	}
	else {
		if (*letter == *devar) {
			return true;
		}
		return false;
	}
}



bool strbasprc::verg8(char* een, unsigned int* eenlen, char* twee, unsigned __int8* tweelen, bool&& hfd) {
	if (*eenlen == *tweelen) {
		for (unsigned __int8 tel = 0; tel < *eenlen; tel++) {
			if (hfd) {
				if (!hfdlttr_pp(een + tel, twee + tel)) {
					return 0;
				}
			}
			else {
				if (*(een + tel) != *(twee + tel)) {
					return 0;
				}
			}
		}
		return 1;
	}
	return 0;
}

char strbasprc::cv16char0(unsigned int& waarde) {
	unsigned __int8 reken = waarde / 16;
	if (reken >= 10) {
		return reken - 10 + 'a';
	}
	else {
		return reken + '0';
	}
}

char strbasprc::cv16char1(unsigned int& waarde) {
	unsigned __int8 reken = waarde % 16;
	if (reken >= 10) {
		return reken - 10 + 'a';
	}
	else {
		return reken + '0';
	}
}

unsigned __int8 strbasprc::cv16waarde(char* char0) {
	unsigned __int8 uitkomst;
	if (*(char0 + 1) >= 'a' && *(char0 + 1) <= 'f') {
		uitkomst = 10 + (*(char0 + 1) - 'a');
	}
	else {
		uitkomst = *(char0 + 1) - '0';
	}
	if (*char0 >= 'a' && *char0 <= 'f') {
		uitkomst = uitkomst + ((10 + (*char0 - 'a')) * 16);
	}
	else {
		uitkomst = uitkomst + ((*char0 - '0') * 16);
	}
	return uitkomst;
}

unsigned int strbasprc::cvcharlngth(unsigned __int8 stelsel, unsigned long getal, char* stuur) {
	unsigned int dec = 0;
	{
		unsigned long x = getal;
		do {
			dec++;
		} while (x /= stelsel);

	}
	for (unsigned int t = dec; t--; *(stuur + t) = cvintcharchar(getal % 60), getal /= 60);

	return dec;
}

unsigned long strbasprc::macht(unsigned __int8 stelsel, unsigned int demacht) {
	unsigned long uitkomst = 1;
	for (unsigned __int8 ttl = 0; ttl < demacht; ttl++) {
		uitkomst = uitkomst * stelsel;
	}
	return uitkomst;
}

char strbasprc::cvintcharchar(unsigned __int8 aant) {
	if (aant < 10) {
		return aant + '0';
	}
	else {
		if (aant < 36) {
			return aant + 55;
		}
		else {
			return aant + 61;
		}
	}
}

char strbasprc::cvintcharint(char x) {
	if (x <= '9') {
		return x - '0';
	}
	else {
		if (x <= 'Z') {
			return x - 55;
		}
		else {
			return x - 61;
		}
	}
}
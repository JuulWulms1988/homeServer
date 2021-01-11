#include "nSite.h"

void clsNSite::func::voegAN(bool x) {
	buf[4] = 'N', buf[5] = 'O';
	bufLen -= 2;
	strncpy_s(buf + 21, bufLen + 1, buf + 2, bufLen); 
	strncpy_s(buf, 21, "Apparaten/00/Nummers", 20); 
	buf[10] = buf[21], buf[11] = buf[22], buf[20] = '/';
	strncpy_s(buf + 21 + bufLen, 5, ".txt", 4); voegC('\''); 
	if (fileObj.open(buf)) {
		char* c = fileObj.file;
		voegC('N'); for (int8_t t = 0; t < 3; t++) voegC(*c++);
	} voeg("\', ", 3); if (x) voeg("true", 4); else voeg("false", 5);
}

void clsNSite::func::voegAD(uint8_t x) {
	buf[4] = 'N', buf[5] = 'O';
	bufLen -= 2;
	strncpy_s(buf + 21, bufLen + 1, buf + 2, bufLen);
	strncpy_s(buf, 21, "Apparaten/00/Nummers", 20);
	buf[10] = buf[21], buf[11] = buf[22], buf[20] = '/';
	strncpy_s(buf + 21 + bufLen, 5, ".txt", 4); voegC('\'');
	if (fileObj.open(buf)) {
		char* c = fileObj.file;
		voegC('D'); for (int8_t t = 0; t < 3; t++) voegC(*c++);
	} voeg("\', ", 3); { bool al = false; for (uint8_t t = 100, r; t; t /= 10) if ((r = x / t % 10) || al || t == 1) al = true, voegC(r + '0'); }
}

void clsNSite::func::stwzF(char* nGet, int nLen) {
	if ([&] { if (nLen != 5) return true; for (char t = 0, c; t < 5; t++) if ((t != 3 && ((c = nGet[t]) > '9' || c < '0')) || (t == 3 && nGet[t] != '=')) return true; return false; }()) return;
	strncpy_s(buf, 17, "Site/Nummers/cat", 16), buf[16] = *nGet, strncpy_s(buf + 17, 5, ".txt", 4);
	if (!fileObj.open(buf)) return;
	mainThreadCls::trLisHomeCls& p = threadCls->webLisHome;
	mainThreadCls::clsExMes& pE = *p.exMes;
	if (!(bufLen = strbasprc::charPLen(strbasprc::charPLsDR((nGet[1] - '0') * 10 + (nGet[2] - '0'), buf, fileObj.file, fileObj.loc)))) return;
	char * B; int8_t Now; bool oTel = true;
	if (!(*nGet - '0')) {
		oTel = false;
		if (nGet[4] == '0') {
			bool uit = true; int t = bufLen; char c;
			while (--t >= 0) if ((c = buf[t]) < '0' || c > '9') return;
			else if (c != '9') {
				buf[t]++, uit = false;
				break;
			}
			if (uit) return;
		}
	}
	else if (nGet[4] == '1') buf[2] = 'A', buf[3] = 'N'; else buf[2] = 'U', buf[3] = 'T';
	Now = pE.getStr(B);
	strncpy_s(B, bufLen + 1, buf, bufLen);
	pE.exCls.voeg(mainThreadCls::clsExMes::var{ B, Now, (uint8_t) bufLen, (int8_t)-(2 + oTel * 1) });
}


void clsNSite::func::stwzdF(char* nGet, int nLen) {
	if ([&] { if (nLen != 6) return true; for (char t = 0, c; t < 6; t++) if ((t != 3 && ((c = nGet[t]) > '9' || c < '0') && !(t > 3 && c >= 'a' && c <= 'f')) || (t == 3 && nGet[t] != '=')) return true; return false; }()) return;
	strncpy_s(buf, 21, "Site/Nummers/Dim/cat", 20), buf[20] = *nGet, strncpy_s(buf + 21, 5, ".txt", 4);
	if (!fileObj.open(buf)) return;
	mainThreadCls::trLisHomeCls& p = threadCls->webLisHome;
	mainThreadCls::clsExMes& pE = *p.exMes;
	if (!(bufLen = strbasprc::charPLen(strbasprc::charPLsDR((nGet[1] - '0') * 10 + (nGet[2] - '0'), buf, fileObj.file, fileObj.loc)))) return;
	char * B; int8_t Now; bool oTel = true;
	if (!(*nGet - '0')) {
		oTel = false;
		return;
	}
	buf[2] = nGet[4], buf[3] = nGet[5];
	Now = pE.getStr(B);
	strncpy_s(B, bufLen + 1, buf, bufLen);
	pE.exCls.voeg(mainThreadCls::clsExMes::var{ B, Now, (uint8_t)bufLen, (int8_t)-(2 + oTel * 1) });
}
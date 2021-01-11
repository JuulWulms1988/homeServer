#include "nSite.h"
#include "Statvars.h"

extern statvars* p_statvars;

void clsNSite::func::voegTmp() {
	uint8_t c = p_statvars->tempCnt;
	map<uint8_t, statvars::strtemp*>& mptemp = p_statvars->mptemp;
	if (!fileObj.open("Overige/Temp.txt")) return;
	strbasprc::charPLsDR(c, buf, fileObj.file, fileObj.loc);
	for (uint8_t t = 0, m = p_statvars->tempCnt; t < m; t++) {
		if (!t) voeg("[\'", 2); else voeg(", [\'", 4);
		voeg(buf, strbasprc::charPLen(strbasprc::charPLsR(buf, fileObj.file, fileObj.loc)));
		voeg("\', web.vT(", 10);
		int8_t te = mptemp.find(t)->second->temp.load();
		if (te < 0) voegC('-'), te *= -1;
		{
			bool al = false; for (uint8_t T = 100, v; T; T /= 10)
				if (((v = te / T % 10) && (al || (al = true))) || al) voegC(v + '0');
			if (!al) voegC('0');
		}
		voeg(")]", 2);
	}
}

void clsNSite::func::voegLdPl() {
	if (!fileObj.open("Site/LedPlVar.txt")) return;
	for (uint8_t t = 0; t < LEDPL_CNT; t++) {
		if (t) voeg(", ", 2);
		voeg("web.vLP(", 8);
		voeg(buf, strbasprc::charPLen(strbasprc::charPLsR(buf, fileObj.file, fileObj.loc)));
		voeg(", ", 2);
		{
			bool al = false;
			for (uint8_t T = 100; T; T /= 10) if (al || (t / T && (al = true))) voegC(t / T % 10 + '0'); if (!al) voegC('0');
		}
		voeg(", [", 3);
		ledPlFVF(t);
		voeg("])", 2);
	}
}

void clsNSite::func::voegUp() {
	voeg("{ N: [", 6);
	for (uint8_t cat = 1; true; cat++)
	{
		strncpy_s(buf, 17, "Site/Nummers/cat", 16), buf[16] = cat + '0', strncpy_s(buf + 17, 5, ".txt", 4);
		if (!fileObj.open(buf)) break;
		if (cat != 1) voeg(", [", 3); else voegC('[');
		char* i = fileObj.file; unsigned long ii = bufLen = 0; bool kom = false; unsigned int tel = 0;
		do {
			if (bufLen) {
				if (!kom) kom = true; else voeg(", ", 2);
				if (threadCls->statVar[(cat - 1) * 100 + tel++].load()) voeg("true", 4); else voeg("false", 5);
			}
			strbasprc::charPLsR(buf, i, ii), bufLen = strbasprc::charPLen(buf);
		} while (bufLen);
		voegC(']');
	}
	voeg("], D: [", 7);
	for (uint8_t cat = 1; true; cat++)
	{
		strncpy_s(buf, 21, "Site/Nummers/Dim/cat", 20), buf[20] = cat + '0', strncpy_s(buf + 21, 5, ".txt", 4);
		if (!fileObj.open(buf)) break;
		if (cat != 1) voeg(", [", 3); else voegC('[');
		char* i = fileObj.file; unsigned long ii = bufLen = 0; bool kom = false; unsigned int tel = 0;
		do {
			if (bufLen) {
				if (!kom) kom = true; else voeg(", ", 2);
				(void)[&](uint8_t XX) {
					bool al = false;
					for (uint8_t T = 100, v; T; T /= 10) if (((v = (XX / T) % 10) && (al || (al = true))) || al) voegC(v + '0'); if (!al) voegC('0');
				} (threadCls->statDimVar[(cat - 1) * 100 + tel++].load());
			}
			strbasprc::charPLsR(buf, i, ii), bufLen = strbasprc::charPLen(buf);
		} while (bufLen);
		voegC(']');
	}
	voeg("], Te: [", 8);
	{
		bool all = false;
		for (map<uint8_t, statvars::strtemp*>::iterator it = p_statvars->mptemp.begin(), m = p_statvars->mptemp.end(); it != m; it++) {
			if (all) voeg(", ", 2); else all = true;
			int8_t te = it->second->temp.load();
			if (te < 0) voegC('-'), te *= -1;
			bool al = false; for (uint8_t T = 100, v; T; T /= 10)
				if (((v = te / T % 10) && (al || (al = true))) || al) voegC(v + '0');
			if (!al) voegC('0');
		}
	}
	voeg("], LdPl: [", 10);
	for (uint8_t t = 0; t < LEDPL_CNT; t++) {
		if (!t) voegC('['); else voeg(", [", 3);
		ledPlFVF(t);
		voegC(']');
	}
	voegC(']');
	streamUp();
	voeg(" }", 2);

}

void clsNSite::func::voegNm() {
	if (!fileObj.open("Site/Categorienaam.txt")) return; strncpy_s(buf, 4, ", \'", 3); char* i = fileObj.file; unsigned long ii = bufLen = 0;
	do {
		if (bufLen) buf[bufLen++] = '\'', voeg(buf, bufLen);
		strbasprc::charPLsR(buf + 3, i, ii), bufLen = 3 + strbasprc::charPLen(buf + 3);
	} while (bufLen > 3);
}

void clsNSite::func::voegNo() {
	for (uint8_t cat = 0; true; cat++)
	{
		strncpy_s(buf, 17, "Site/Nummers/cat", 16), buf[16] = cat + '0', strncpy_s(buf + 17, 5, ".txt", 4);
		if (!fileObj.open(buf)) return;
		if (cat != 0) voeg(", [", 3); else voegC('[');
		char* i = fileObj.file; unsigned long ii = bufLen = 0; bool kom = false; unsigned int tel = 0;
		do {
			if (bufLen) {
				if (!kom) kom = true, voegC('['); else voeg(", [", 3);
				if (!cat) voegNo0(); else voegNo1((cat) * 100 + tel++); voegC(']');
			}
			strbasprc::charPLsR(buf, i, ii), bufLen = strbasprc::charPLen(buf);
		} while (bufLen);
		voegC(']');
	}
}

void clsNSite::func::voegNoD() {
	for (uint8_t cat = 0; true; cat++)
	{
		strncpy_s(buf, 21, "Site/Nummers/Dim/cat", 20), buf[20] = cat + '0', strncpy_s(buf + 21, 5, ".txt", 4);
		if (!fileObj.open(buf)) return;
		if (cat != 0) voeg(", [", 3); else voegC('[');
		char* i = fileObj.file; unsigned long ii = bufLen = 0; bool kom = false; unsigned int tel = 0;
		do {
			if (bufLen) {
				if (!kom) kom = true, voegC('['); else voeg(", [", 3);
				if (cat) voegNoD1((cat) * 100 + tel++); voegC(']');
			}
			strbasprc::charPLsR(buf, i, ii), bufLen = strbasprc::charPLen(buf);
		} while (bufLen);
		voegC(']');
	}
}

void clsNSite::func::voegNo0() {
	for (char t = 0, c = *buf; t < 4; c = buf[++t]) if ([&] { if (c >= '0' && c <= '9') return false; else return true; }()) return;
	unsigned int nR = 1; { char* b = buf; for (int t = 1000; t; t /= 10) nR += (*b++ - '0') * t; }
	for (unsigned int t = bufLen; t; t--) buf[13 + t] = buf[t - 1];
	strncpy_s(buf, 14, "Actions/Namen", 13); buf[13] = '/';
	strncpy_s(buf + bufLen + 14, 5, ".txt", 4); voegC('\''); if (fileObj.open(buf)) {
		char* t = fileObj.file;
		for (char c = *t; c != '\r' && c != '\n' && c; c = *++t) voegC(c);
	} voeg("\', [", 4);
	{
		bufLen += 5; unsigned int t = 0; char* C = buf + 14;
		for (char* c = buf + 8; t++ < bufLen; c++) *c = *C++;
	}
	voegNo02(false);
	{ char* b = buf + 8; for (int t = 1000; t; t /= 10) *b++ = nR / t + '0'; }
	strncpy_s(buf, 8, "Actions/Namen", 7); buf[7] = '/'; strncpy_s(buf + 12, 5, ".txt", 4);
	voeg("], [", 4); voegNo02(false);
	voegC(']');
}

bool clsNSite::func::voegNo02(bool kom) {
	if (!fileObj.open(buf)) return kom;
	char* i = fileObj.file; unsigned long ii = bufLen = 0;
	do {
		uint8_t Ot = 0;
		while (bufLen) {
			uint8_t A = 0;
			if (buf[0] == 'U' && buf[1] == 'V')
				if (buf[4] == 'A' && buf[5] == 'N') A = 1;
				else if (buf[4] == 'U' && buf[5] == 'T') A = 2;
				else if (((buf[4] >= '0' && buf[4] <= '9') || (buf[4] >= 'a' && buf[4] <= 'f')) && ((buf[5] >= '0' && buf[5] <= '9') || (buf[5] >= 'a' && buf[5] <= 'f'))) A = 3;
				else break;
			else if (buf[0] == 'S' && buf[1] == 'P') { Ot = 1; break; }
			else if (buf[0] == 'N' && buf[1] == 'A' && (A = bufLen = 4)) for (int8_t t = 0; t < 4; t++) buf[t] = buf[t + 2];
			else break;
			if (A == 4) {
				for (unsigned int t = 4; t; t--) buf[7 + t] = buf[t - 1];
				strncpy_s(buf, 8, "Actions/Namen", 7); buf[7] = '/';
				strncpy_s(buf + 12, 5, ".txt", 4);
				kom = voegNo02(kom);
				break;
			}
			if (!kom) kom = true, voegC('['); else voeg(", [", 3);
			switch (A) {
			case 1: voegAN(true); break;
			case 2: voegAN(false); break;
			case 3: voegAD(strbasprc::cv16waarde(buf + 4)); break;
			}
			voegC(']');
			break;
		}
		strbasprc::charPLsDR(Ot, buf, i, ii), bufLen = strbasprc::charPLen(buf);
	} while (bufLen); return kom;
}

void clsNSite::func::voegNo1(unsigned int N) {
	strncpy_s(buf + 19, bufLen + 1, buf, bufLen); strncpy_s(buf, 19, "Apparaten/00/Namen", 18); buf[10] = buf[19], buf[11] = buf[20], buf[18] = '/';
	strncpy_s(buf + 19 + bufLen, 5, ".txt", 4); voegC('\''); if (fileObj.open(buf)) {
		char* t = fileObj.file;
		for (char c = *t; c != '\r' && c != '\n' && c; c = *++t) voegC(c);
	} voeg("\', ", 3);
	voeg("web.v(", 6); if ([](unsigned int N) { if (threadCls->statVar[N - 100].load()) return true; else return false; }(N)) voeg("true", 4); else voeg("false", 5);
	voeg(", ", 2); {
		bool al = false;
		if (N / 100 && (al = true)) voegC(N / 100 + '0');
		if (al || N / 10) voegC(N / 10 % 10 + '0');
		voegC(N % 10 + '0');
	} voegC(')');
}

void clsNSite::func::voegNoD1(unsigned int N) {
	strncpy_s(buf + 19, bufLen + 1, buf, bufLen); strncpy_s(buf, 19, "Apparaten/00/Namen", 18); buf[10] = buf[19], buf[11] = buf[20], buf[18] = '/';
	strncpy_s(buf + 19 + bufLen, 5, ".txt", 4); voegC('\''); if (fileObj.open(buf)) {
		char* t = fileObj.file;
		for (char c = *t; c != '\r' && c != '\n' && c; c = *++t) voegC(c);
	} voeg("\', ", 3);
	voeg("web.vD(", 7);
	{ bool al = false; for (unsigned int t = 100, v = threadCls->statDimVar[N - 100].load(), v2; t; t /= 10) if (((v2 = (v / t) % 10) && (al || (al = true))) || al) voegC(v2 + '0'); if (!al) voegC('0'); }
	voeg(", ", 2); {
		bool al = false;
		if (N / 100 && (al = true)) voegC(N / 100 + '0');
		if (al || N / 10) voegC(N / 10 % 10 + '0');
		voegC(N % 10 + '0');
	} voegC(')');
}
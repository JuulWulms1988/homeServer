#include "Statvars.h"
#include "strucfile.h"
#include "Basproc.h"

statvars::statvars(void) {
	strucfile statfile;
	{
		char bufFF[] = { 'S', 'i', 't', 'e', '/', 'N', 'u', 'm', 'm', 'e', 'r', 's', '/', 'D', 'i', 'm', '/', 'c', 'a', 't', '0', '.', 't', 'x', 't', '\0' };
		class fDat {
		public:
			char* file;
			unsigned long loc;
			fDat(const char* f) { 
				memFileObj O(fileData); if (O.open(f)) file = O.file, loc = O.loc; else file = NULL, loc = 0; }
		} fDC(bufFF), fDD(bufFF + 25);
		char buf[32]; unsigned int bufLen;
		for (unsigned int t = 0; fDC.file; [&] { if (bufLen) t++; else t = (t / 100 + 1) * 100, bufFF[17] = 'c', bufFF[20] = t / 100 + '0', fDC = fDat(bufFF); }()) {
			if (bufLen = strbasprc::charPLen(strbasprc::charPLsR(buf, fDC.file, fDC.loc))) 
				bufLen = strbasprc::charPLen(strbasprc::charPLsR(buf, [&] { if (!(t % 100)) bufFF[17] = 'd', fDD = fDat(bufFF); return fDD.file; }(), fDD.loc));
			else continue;
			mpdimcat.insert(pair<unsigned int, char*>(t, new char[bufLen + 1]));
			strncpy_s(mpdimcat.find(t)->second, bufLen + 1, buf, bufLen);
		}
	}


	unsigned int regelno;
	char ls[32];
	char filebuf[8];
	uint8_t flen[2] = { 24, 7 };
	strncpy_s(&filebuf[3], 5, ".txt", 4);
	flen[0] = 7; flen[1] = 8;
	statfile.beginregel("Overige", &flen[0], "Temp.txt", &flen[1]);
	tempCnt = regelno = 0;
	map<uint8_t, strtemp*>::iterator itmptemp;
	for (uint8_t len = statfile.lsrgllength(&ls[0]); ls[0] != 'G' || ls[1] != 'G'; len = statfile.lsrgllength(&ls[0])) {
		while (true) {
			mptemp.insert(pair<uint8_t, strtemp*>(regelno, new strtemp));
			itmptemp = mptemp.find(regelno);
			if (itmptemp != mptemp.end()) {
				itmptemp->second->temp = 40;
				itmptemp->second->client = new uint8_t[len / 2 + 1];
				for (uint8_t tel = 0; tel * 2 < len; tel++) {
					*(itmptemp->second->client + tel) = (ls[tel * 2] - '0') * 10 + (ls[tel * 2 + 1] - '0');
				}
				*(itmptemp->second->client + (len / 2)) = 255;
				break;
			}
		}
	tempCnt = ++regelno;
	}
	statfile.close();
}

statvars::~statvars(void) {
}
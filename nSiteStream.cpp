#include "nSite.h"
#include "Radio.h"
#include "PiScreen.h"


bool clsNSite::func::stwzStream(bool type, char* nGet, int nLen) {
	if (!type || nLen < 3 || nGet[0] != 'z' || nGet[1] != 'z') {
		if (nLen != 2 || [&] { for (char t = 0, x = nGet[0]; t < 2; x = nGet[++t]) if (!(x >= '0' && x <= '9') && !(x >= 'A' && x <= 'Z') && !(x >= 'a' && x <= 'x')) return true; return false; }()) return false;
		uint8_t noV = strbasprc::cvintcharStr(nGet);
		if (type) 
			if (noV > piScreenC.chanCnt) return false;
			else if (!noV) piScreenC.playF(1, 99);
			else piScreenC.chanF(noV - 1, 99);
		else
			if (noV > radioS.chanCnt) return false;
			else radioS.pass(103 + noV * 256, 99);
		return true;
	}
	return false;
}

void clsNSite::func::voegStream() {
	voeg("web.vSTR(false, \'", 17);
	voeg(radioS.getF(buf), 2);
	voeg("\', [\'-\'", 7); 
	if (!fileObj.open("Radio/Set.txt")) return; 
	{ 
		unsigned int l;
		if (l = strbasprc::charPLen(strbasprc::charPLsR(buf, fileObj.file, fileObj.loc)))
			do voeg(", \'", 3), voeg(buf + 3, l - 3), voegC('\'');
		while (l = strbasprc::charPLen(strbasprc::charPLsDR(1, buf, fileObj.file, fileObj.loc)));
	} 
	voeg("]), [[", 6); 
	{ 
		bool v = piScreenC.StreamVidVar(buf); 
		if (v) voeg("true, \'", 7), voeg(buf, strbasprc::charPLen(buf)); 
		else voeg("false, \'", 8), voeg(buf, 2);
		voeg("\'], web.vSTR(true, \'", 20); 
		if (v) voeg("zz", 2); 
		else voeg(buf, 2); 
	} 
	voeg("\', [\'-\', \'Opdrachtregel\'", 24);
	{
		unsigned int l; unsigned long h = 0; char* f = piScreenC.chanPoint;
		while (l = strbasprc::charPLen(strbasprc::charPLsDR(1, buf, f, h)))
			voeg(", \'", 3), voeg(buf, l ), voegC('\'');
	}
	voeg("])]", 3);
}

void clsNSite::func::streamUp() {
	voeg(", Str: [\'", 9); 
	voeg(radioS.getF(buf), 2);
	voeg("\', [", 4);
	if (piScreenC.StreamVidVar(buf)) voeg("true, \'", 7), voeg(buf, strbasprc::charPLen(buf));
	else voeg("false, \'", 8), voeg(buf, 2);
	voeg("\']]", 3);
}
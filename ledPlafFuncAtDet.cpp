#include "ledPlaf.h"

void mainThreadCls::clsLedPl::clsLedPlObj::atDetFunc(char* xLs, int xLen) {
	char*& yLs = sndS.pack; int& yLen = sndS.len = 3; bool atDetBl; if (*xLs == 'A') atDetBl = true; else atDetBl = false;
	unsigned __int8 strNo = (xLs[xLen - 2] - '0') * 10 + (xLs[xLen - 1] - '0'), clNo; if (atDetBl) clNo = (xLs[1] - '0') * 10 + (xLs[2] - '0');
	{
		varMut.lock();
		varStr& p = var[strNo]; bool* pAr = p.parChldAr;
		auto detInFunc = [&] {
			for (unsigned __int8 tt, t = tt = 0, m = p.parChld; tt < m; t++)
				if ((t == strNo && ++tt) || !pAr[t] || !++tt) continue;
				else pAr[t] = false, var[t].parChld--, var[t].parChldAr[strNo] = false;
				p.parChld = 1;
		}; 
		if (!atDetBl) 
			detInFunc(), varMut.unlock(), yLs[0] = '&', yLs[1] = strbasprc::cvintcharchar(strNo), yLs[2] = 'D';
		else {
			detInFunc();
			varStr& p0 = var[clNo];  bool* pAr0 = p0.parChldAr; bool plus; if (!pAr0[strNo]) plus = true; else plus = false;
			for (unsigned __int8 t = 0; ((t == clNo || t == strNo) && (((++t == clNo || t == clNo) && ++t < stripCnt) || t < stripCnt)) || t < stripCnt; t++)
				if (pAr[t] = pAr0[t]) var[t].parChld += plus * 1, var[t].parChldAr[strNo] = true;
			if (plus) ++p0.parChld;
			p.parChld = p0.parChld, pAr[clNo] = pAr0[strNo] = true, p = p0, p.parChldAr = pAr;
			for (unsigned __int8 tel = 0; tel < stripCnt; tel++) if (pAr0[tel] && tel != strNo) { clNo = tel; break; }
			varMut.unlock(), yLs[0] = '$', yLs[1] = strbasprc::cvintcharchar(clNo), yLs[2] = 'A', yLs[yLen++] = strbasprc::cvintcharchar(strNo);
		}
	}
	yLs[yLen++] = '\n', yLs[yLen++] = '+';
	psMsPr();	
}

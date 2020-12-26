#include "nSite.h"
#include "ledPlaf.h"

extern unsigned __int8* LEDPL_ADR;

bool clsNSite::func::stwLdF(char* nGet, int nLen) {
	unsigned __int8 ldNo = (*(nGet - 5) - '0') * 10 + (*(nGet - 4) - '0'), type;
	if ([&] { 
		if (*(nGet - 3) == 'w' && *(nGet - 2) == 'z') {
			
			type = 0;
			bool uit = true; char n = *nGet;
			for (int t = 0; t < nLen; n = nGet[++t])
				if ((t < 4 && !(n >= '0' && n <= '9')) || (t == 4 && n != '=')) return true;
				else if (t > 4 && (!((n >= '0' && n <= '9') || (n >= 'A' && n <= 'Z') || (n >= 'a' && n <= 'x')) || (uit = false))) return true; 
			if (uit) return true; return false;
		} 



		if ((*(nGet - 3) == 'a' && *(nGet - 2) == 't' && (type = 1)) || (*(nGet - 3) == 'd' && *(nGet - 2) == 't' && (type = 2))) {
			bool uit = true; 
			char n = *nGet;
			for (unsigned __int8 t = 0, m = 2 + (type % 2) * 2; t < m; n = nGet[++t])
				if (!(n >= '0' && n <= '9')) return true;
			return false;
		}
		
		
		return true; }()) return false;
	if (ldNo >= LEDPL_CNT) return false;
	stwLdwzF(type, ldNo, nGet, nLen); 
	return true;
}

void clsNSite::func::stwLdwzF(unsigned __int8 type, unsigned __int8 ldNo, char* nGet, int nLen) {
	char* xLs; mainThreadCls::clsExMes& pE = *threadCls->webLisHome.exMes;
	__int8 xNow = pE.getStr(xLs); switch (type) {
	case 0: *xLs = 'V'; break;
	case 1: *xLs = 'A'; break;
	case 2: *xLs = 'D'; break;
	} strncpy_s(xLs + 1, nLen + 1, nGet, nLen);
	p_ledPl.toObjF(LEDPL_ADR[ldNo])->passPrep({ xLs, nLen + 1, &pE, xNow }, threadCls->mpChS[99][99 + ldNo], 99);
}
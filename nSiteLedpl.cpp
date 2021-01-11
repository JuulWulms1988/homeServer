#include "nSite.h"
#include "ledPlaf.h"

extern uint8_t* LEDPL_ADR;

void clsNSite::func::ledPlFVF(uint8_t n) {
	mainThreadCls::clsLedPl::clsLedPlObj& p = p_ledPl.mpObj.find(LEDPL_ADR[n])->second;
	shared_lock<shared_mutex> lk(p.varMut);
	voegC('[');
	for (uint8_t t = 0, m = p.stripCnt; t < m; t++) { 
		if (t) voeg(", [", 3);
		ledPlFVF2(p.var + t, m); 
		voegC(']');
	}
}


void clsNSite::func::ledPlFVF2(void* var, uint8_t m) {
	mainThreadCls::clsLedPl::clsLedPlObj::varStr& p = *((mainThreadCls::clsLedPl::clsLedPlObj::varStr*)var);
	voegC('[');
	for (uint8_t t = 0; t < m; t++) {
		if (t) voeg(", ", 2);
		if (p.parChldAr[t]) voeg("true", 4); else voeg("false", 5);
	}
	voegC(']');
	auto voegCnt = [&] (unsigned int X) {
		bool AL = false; char C[5], CL = 0;
		for (unsigned int T = 10000; T; T /= 10) if (AL || (X / T && (AL = true))) C[CL++] = X / T % 10 + '0';
		if (!AL) C[0] = '0', CL = 1;
		voeg(C, CL);
	};
	for (uint8_t t = 0; t < LEDPL_VARAANT; t++) {
		voeg(", ", 2); 
		if ([&] { for (uint8_t T = 0, TA[] = { 2, 4, 11 }; T < 3; T++) if (t == TA[T]) return true; return false; }())
			if (p.val(t)) voeg("true", 4);
			else voeg("false", 5);
		else voegCnt(p.val(t));
	}
	for (uint8_t t = 20, mm = 20 + LEDPL_VARAANT1; t < mm; t++) voeg(", ", 2), voegCnt(p.val(t));
	for (uint8_t t = 40, mm = 40 + LEDPL_VARAANT2; t < mm; t++) voeg(", ", 2), voegCnt(p.val(t));
}
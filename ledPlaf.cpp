#include "ledPlaf.h"

unsigned __int8* LEDPL_StripCnt;
unsigned __int8* LEDPL_ADR;
mainThreadCls::clsLedPl& p_ledPl{ *new mainThreadCls::clsLedPl };

void mainThreadCls::openLdPl() {
	p_ledPl.begin();
}

void mainThreadCls::clsLedPl::begin() {
	unsigned __int8 t = 1, x; do x = LEDPL_ADR[t - 1], mpObj.insert(pair<unsigned __int8, clsLedPlObj&>
		(x, (new clsLedPlObj{ threadCls->strCntS[t].open(50, t, 512), t, x, LEDPL_StripCnt[t - 1] })->begin()));
	while (t++ < LEDPL_CNT);
}

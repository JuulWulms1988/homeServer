#include "ledPlaf.h"

uint8_t* LEDPL_StripCnt;
uint8_t* LEDPL_ADR;
mainThreadCls::clsLedPl& p_ledPl{ *new mainThreadCls::clsLedPl };

void mainThreadCls::openLdPl() {
	p_ledPl.begin();
}

void mainThreadCls::clsLedPl::begin() {
	uint8_t t = 1, x; do x = LEDPL_ADR[t - 1], mpObj.insert(pair<uint8_t, clsLedPlObj&>
		(x, (new clsLedPlObj{ threadCls->strCntS[t].open(50, t, 512), t, x, LEDPL_StripCnt[t - 1] })->begin()));
	while (t++ < LEDPL_CNT);
}

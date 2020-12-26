#include "clstijd.h"
#include "strucwebuser.h"
#include "strucwebuser2.h"

extern clswbusr* p_clswbusr;
extern clswbusr2& p_wUsr;
extern unsigned int stuurleeslength;

bool clstijd::tijdupdate() {
	unsigned __int8 MM, DD;
	time(&rawtime); localtime_s(&timeinfo, &rawtime); if (seconde == timeinfo.tm_sec) return false;
	dag.store(DD = timeinfo.tm_mday - 1), maand.store(MM = timeinfo.tm_mon), jaar = timeinfo.tm_year - 100, weekdag = (timeinfo.tm_wday + 6) % 7,
	uur.store(timeinfo.tm_hour), seconde.store(timeinfo.tm_sec), aftrek = aftrekpr(MM + 1) + aftrekpr(DD + 1);
	if (minuut.load() != (MM = timeinfo.tm_min)) { minuut.store(MM), p_wUsr.mpupdate(MM), seconde = 88; return tijdupdate(); }
	minuut.store(MM); if (!timerloopt) timerloopt = 1; else switch (timer[0]) {
	case 2:
		if ((!aftrek && timer[1] == 4) || (aftrek && (timer[1] == 4 && kwart >= aftrek)) || timer[1] == 5) { 
			if (aftrek) if (kwart >= aftrek) kwart -= aftrek; else kwart = 4 - (aftrek - kwart); timer[0] = timer[1] = 0; }
		else timer[1]++;
		break;
	default:
		if (timer[1] == 4) timer[0]++, timer[1] = 0;
		else timer[1]++;
		break;
	}
	if (timer[0] != 2 && timer[1] > 1) return true; return false;
}

char clstijd::stuur(__int8 x) {
	switch (x) {
	case 3: return uur.load();
	case 4: return seconde.load();
	case 5: return timer[1]; }
}

char clstijd::stuurt(__int8 x) {
	unsigned __int8 optel;
	switch (x) {
	case 3: return timer[1];
	case 4: if (weekdag == 6) optel = 24; else optel = 0; return uur.load() + optel;
	case 5: return minuut.load();
	case 6: return seconde.load();
	case 7: if (weekdag == 6 || weekdag < 3) optel = 0; else optel = 1; return dag.load() + optel * 31;
	case 8: return maand.load() + weekdag % 3 * 12; }
}

void clstijd::printen(char* deprint, unsigned int print) {
	cout << deprint << ": " << print << "\r\n";
}
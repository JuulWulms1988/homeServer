#include "clstijd.h"
#include "strucfile.h"
#include "windows.h"

clstijd::clstijd(void) {
	strucfile tijdfile;
	char ls[32];
	__int8 tels = 0;
	unsigned __int8 lsfile[2] = { 7, 13 };
	time_t rawtime;
	struct tm timeinfo;
	timerloopt = 0;
	kwart = 0;
	aftrek = 0;
	timer[0] = 0; timer[1] = 0;
	minuutgestuurd = 2;
	time(&rawtime);
	localtime_s(&timeinfo, &rawtime);
	seconde = timeinfo.tm_sec;
	minuut = timeinfo.tm_min;
	seconde = timeinfo.tm_sec;
	dag = timeinfo.tm_mday - 1;
	maand = timeinfo.tm_mon;
	jaar = timeinfo.tm_year - 100;
	weekdag = (timeinfo.tm_wday + 6) % 7;
	tijdfile.beginregel("Overige", &lsfile[0], "tijdadres.txt", &lsfile[1]);
	if (tijdfile.lsrgllength(&ls[0]) != 0) 
		*(timeUpd = new unsigned __int8) = (ls[0] - '0') * 10 + (ls[1] - '0');
}
clstijd::~clstijd(void) {
}

#include "clstijd.h"
#include "strucfile.h"

clstijd::clstijd(void) {
	strucfile tijdfile;
	char ls[32];
	int8_t tels = 0;
	uint8_t lsfile[2] = { 7, 13 };
	time_t rawtime;
	timerloopt = 0;
	kwart = 0;
	aftrek = 0;
	timer[0] = 0; timer[1] = 0;
	minuutgestuurd = 2;
	time(&rawtime);
	#ifdef _WIN32
	struct tm timeinfo;
	localtime_s(&timeinfo, &rawtime);
	seconde = timeinfo.tm_sec;
	minuut = timeinfo.tm_min;
	seconde = timeinfo.tm_sec;
	dag = timeinfo.tm_mday - 1;
	maand = timeinfo.tm_mon;
	jaar = timeinfo.tm_year - 100;
	weekdag = (timeinfo.tm_wday + 6) % 7;
	#endif
	#ifndef _WIN32
	struct tm * timeinfo;
	timeinfo = localtime(&rawtime);
	seconde = timeinfo->tm_sec;
	minuut = timeinfo->tm_min;
	seconde = timeinfo->tm_sec;
	dag = timeinfo->tm_mday - 1;
	maand = timeinfo->tm_mon;
	jaar = timeinfo->tm_year - 100;
	weekdag = (timeinfo->tm_wday + 6) % 7;
	#endif
	tijdfile.beginregel("Overige", &lsfile[0], "Tijdadres.txt", &lsfile[1]);
	if (tijdfile.lsrgllength(&ls[0]) != 0) 
		*(timeUpd = new uint8_t) = (ls[0] - '0') * 10 + (ls[1] - '0');
}
clstijd::~clstijd(void) {
}

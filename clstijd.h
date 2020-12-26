#pragma once
#include <iostream>
#include <map>
#include <ctime>
#include <atomic>

using namespace std;

class clstijd {
public:
	clstijd(void);
	~clstijd(void);
	unsigned __int8* timeUpd;
	unsigned __int8 timeUpdC = 0;
	bool tijdupdate();
	unsigned __int8 kwart;
	atomic <unsigned __int8> uur;
	atomic <unsigned __int8> seconde;
	atomic <unsigned __int8> minuut;
	unsigned __int8 minuutgestuurd;
	bool timerloopt;
	unsigned __int8 timer[2];
	atomic <unsigned __int8> dag;
	atomic <unsigned __int8> maand;
	unsigned int jaar;
	unsigned __int8 weekdag;
	char stuur(__int8 x);
	char stuurt(__int8 x);
	void printen(char* deprint, unsigned int print);
	unsigned __int8 aftrek;
	bool aftrekpr(unsigned __int8 x) { if (x / 10 > 0) return true; return false; }
private:
	time_t rawtime;
	struct tm timeinfo;
};
#pragma once
#include <stdint.h>
#include <iostream>
#include <map>
#include <atomic>

#include <ctime>

using namespace std;

class clstijd {
public:
	clstijd(void);
	~clstijd(void);
	uint8_t* timeUpd;
	uint8_t timeUpdC = 0;
	bool tijdupdate();
	uint8_t kwart;
	atomic <uint8_t> uur;
	atomic <uint8_t> seconde;
	atomic <uint8_t> minuut;
	uint8_t minuutgestuurd;
	bool timerloopt;
	uint8_t timer[2];
	atomic <uint8_t> dag;
	atomic <uint8_t> maand;
	unsigned int jaar;
	uint8_t weekdag;
	char stuur(int8_t x);
	char stuurt(int8_t x);
	void printen(char* deprint, unsigned int print);
	uint8_t aftrek;
	bool aftrekpr(uint8_t x) { if (x / 10 > 0) return true; return false; }
};
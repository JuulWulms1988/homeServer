#pragma once
#include <stdint.h>
#include <iostream>
#include <map>
#include <atomic>
using namespace std;

extern uint8_t percatdimaant[10];
extern uint8_t cataant;

class statvars {
public:
	statvars(void);
	~statvars(void);
	struct strtemp {
		atomic<int8_t> temp;
		uint8_t* client;
	};
	map<unsigned int, char*> mpdimcat;
	uint8_t tempCnt;
	map<uint8_t, strtemp*> mptemp;
private:
};
//struct destatvars {
	
//	std::map<unsigned int, strdimvar> mapdimvars;
//};
//struct strdimvar {
//	int8_t aant;
	//bool type[1] = { 0 };
	//uint8_t dimwaarde;
//};
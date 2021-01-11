#include "strucwebuser.h"
#include "clstijd.h"
extern clstijd* p_clstijd;

clswbusr::clswbusr(void) {
	mpusr.insert(pair<unsigned int, clswbusrlogstr*>(0, new clswbusrlogstr));
	map<unsigned int, clswbusrlogstr*>::iterator itmpusr = mpusr.find(0);
	if (itmpusr != mpusr.end()) {
		itmpusr->second->usrlen = new uint8_t; *itmpusr->second->usrlen = 0;
		itmpusr->second->usr = new char[5]; strncpy_s(itmpusr->second->usr, 0, "", 0);
		itmpusr->second->pswlen = new uint8_t; *itmpusr->second->pswlen = 0;
		itmpusr->second->psw = new char[5]; strncpy_s(itmpusr->second->psw, 0, "", 0);
	}
}
clswbusr::~clswbusr(void) {
	map<unsigned int, clswbusrlogstr*>::iterator itmpusr = mpusr.find(0);
	if (itmpusr != mpusr.end()) {
		delete itmpusr->second->usrlen;
		delete[] itmpusr->second->usr;
		delete itmpusr->second->pswlen;
		delete[]itmpusr->second->psw;
	}
	delete itmpusr->second;
	mpusr.erase(itmpusr);
}

void clswbusr::mpupdate(uint8_t minuut) {
	for (map<unsigned int, strloghost*>::iterator itloghost = mphost.begin(); itloghost != mphost.end(); itloghost++) {
		if (vergminuut(*(itloghost->second->tijd + 2), minuut)) {
			delete[] itloghost->second->tijd;
			mphost.erase(itloghost);
		}
	}
}

bool clswbusr::vergminuut(uint8_t x, uint8_t y) {
	if (x > y) {
		if (60 - x + y > 10) {
			return 1;
		}
	}
	else {
		if (y - x > 10) {
			return 1;
		}
	}
	return 0;
}

unsigned int clswbusr::voegid(const unsigned int* usrno) {
	unsigned int voeg;
	for (uint8_t tel = 0; tel < 250; tel++) {
		if (mphost.find(voeg = rand()) == mphost.end()) {
			break;
		}
		if (tel == 249) {
			voeg = 32767;
			while (voeg++ != 32766) {
				if (mphost.find(voeg) == mphost.end()) {
					break;
				}
			}
		}
	}
	while (true) {
		mphost.insert(pair<unsigned int, strloghost*>(voeg, new strloghost));
		map<unsigned int, strloghost*>::iterator itloghost = mphost.find(voeg);
		if (itloghost != mphost.end()) {
			itloghost->second->usrno = usrno;
			itloghost->second->tijd = new uint8_t[4];
			*itloghost->second->tijd = p_clstijd->uur.load();
			unsigned int dexekaas = p_clstijd->uur.load();
			for (int8_t tel = 1; tel < 3; tel++) {
				*(itloghost->second->tijd + tel) = p_clstijd->minuut.load();
			}
			*(itloghost->second->tijd + 3) = p_clstijd->seconde.load();
			return voeg;
		}
	}
}
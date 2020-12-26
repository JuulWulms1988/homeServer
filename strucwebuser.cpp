#include "strucwebuser.h"
#include "clstijd.h"
extern clstijd* p_clstijd;

clswbusr::clswbusr(void) {
	mpusr.insert(pair<unsigned int, clswbusrlogstr*>(0, new clswbusrlogstr));
	map<unsigned int, clswbusrlogstr*>::iterator itmpusr = mpusr.find(0);
	if (itmpusr != mpusr.end()) {
		itmpusr->second->usrlen = new unsigned __int8; *itmpusr->second->usrlen = 4;
		itmpusr->second->usr = new char[2]; strncpy_s(itmpusr->second->usr, 2, "X", 1);
		itmpusr->second->pswlen = new unsigned __int8; *itmpusr->second->pswlen = 4;
		itmpusr->second->psw = new char[2]; strncpy_s(itmpusr->second->psw, 2, "X", 1);
	}
}
clswbusr::~clswbusr(void) {
	map<unsigned int, clswbusrlogstr*>::iterator itmpusr = mpusr.find(0);
	if (itmpusr != mpusr.end()) {
		delete itmpusr->second->usrlen;
		delete[2] itmpusr->second->usr;
		delete itmpusr->second->pswlen;
		delete[2]itmpusr->second->psw;
	}
	delete itmpusr->second;
	mpusr.erase(itmpusr);
}

void clswbusr::mpupdate(unsigned __int8 minuut) {
	for (map<unsigned int, strloghost*>::iterator itloghost = mphost.begin(); itloghost != mphost.end(); itloghost++) {
		if (vergminuut(*(itloghost->second->tijd + 2), minuut)) {
			delete[4] itloghost->second->tijd;
			mphost.erase(itloghost);
		}
	}
}

bool clswbusr::vergminuut(unsigned __int8 x, unsigned __int8 y) {
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
	for (unsigned __int8 tel = 0; tel < 250; tel++) {
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
			itloghost->second->tijd = new unsigned __int8[4];
			*itloghost->second->tijd = p_clstijd->uur.load();
			unsigned int dexekaas = p_clstijd->uur.load();
			for (__int8 tel = 1; tel < 3; tel++) {
				*(itloghost->second->tijd + tel) = p_clstijd->minuut.load();
			}
			*(itloghost->second->tijd + 3) = p_clstijd->seconde.load();
			return voeg;
		}
	}
}
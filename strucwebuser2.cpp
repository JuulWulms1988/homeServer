#include "strucwebuser2.h"
#include "clstijd.h"


extern clstijd* p_clstijd;

clswbusr2::clswbusr2(void) {
	for (int t = 0, t2 = 0; t2 < 2 || (!(t2 = 0) && ++t < WEBUSR_CNT); t2++) usrId.id[t][t2] = 0, usrId.tijd[t][t2] = 99;
	mpusr.insert(pair<unsigned int, clswbusrlogstr*>(0, new clswbusrlogstr));
	map<unsigned int, clswbusrlogstr*>::iterator itmpusr = mpusr.find(0);
	if (itmpusr != mpusr.end()) {
		itmpusr->second->usrlen = new uint8_t; *itmpusr->second->usrlen = 4;
		itmpusr->second->usr = new char[5]; strncpy_s(itmpusr->second->usr, 5, "Juul", 4);
		itmpusr->second->pswlen = new uint8_t; *itmpusr->second->pswlen = 4;
		itmpusr->second->psw = new char[5]; strncpy_s(itmpusr->second->psw, 5, "8140", 4);
	}
	mpusr.insert(pair<unsigned int, clswbusrlogstr*>(1, new clswbusrlogstr)); itmpusr = mpusr.find(1);
	if (itmpusr != mpusr.end()) {
		itmpusr->second->usrlen = new uint8_t; *itmpusr->second->usrlen = 4;
		itmpusr->second->usr = new char[5]; strncpy_s(itmpusr->second->usr, 5, "Kaas", 4);
		itmpusr->second->pswlen = new uint8_t; *itmpusr->second->pswlen = 4;
		itmpusr->second->psw = new char[5]; strncpy_s(itmpusr->second->psw, 5, "test", 4);
	}
}
clswbusr2::~clswbusr2(void) {
	map<unsigned int, clswbusrlogstr*>::iterator itmpusr = mpusr.find(0);
	if (itmpusr != mpusr.end()) {
		delete itmpusr->second->usrlen;
		delete[] itmpusr->second->usr;
		delete itmpusr->second->pswlen;
		delete[]itmpusr->second->psw;
	}
	delete itmpusr->second;
	itmpusr = mpusr.find(1);
	if (itmpusr != mpusr.end()) {
		delete itmpusr->second->usrlen;
		delete[] itmpusr->second->usr;
		delete itmpusr->second->pswlen;
		delete[]itmpusr->second->psw;
	}

	delete itmpusr->second;
	mpusr.erase(itmpusr);
}

void clswbusr2::mpupdate(uint8_t minuut) {
	mut.lock();
	for (unsigned int t = 0, v, m = WEBUSR_CNT * 2; t < m; t++)
		if (v = usrId.id[t / 2][t % 2])
			if ((t % 2 && vergminuut(true, usrId.tijd[t / 2][1], minuut) && (usrId.id[t / 2][1] = 0)) || (!(t % 2) && vergminuut(false, usrId.tijd[t / 2][0], minuut)))
				usrId.tijd[t /= 2][1] = usrId.tijd[t][0], usrId.id[t][1] = usrId.id[t][0], usrId.id[t][0] = 0, t = t * 2 + 1;
	mut.unlock();
}

bool clswbusr2::vergminuut(bool z, uint8_t x, uint8_t y) {
	if (x > y) {
		if (60 - x + y > 5 * (1 + (z * 1))) return true;
	}
	else if (y - x > 5 * (1 + (z * 1))) return true;	
	return false;
}

bool clswbusr2::getId(unsigned int id, unsigned int& logId, bool& wId) {
	wId = false, mut.lock(); 
	unsigned int loc = [&] { 
		for (unsigned int t, t2 = t = 0; t2 < 2 || (!(t2 = 0) && ++t < WEBUSR_CNT); t2++) 
			if (usrId.id[t][t2] == id) return 1 + t * 2 + t2; return (unsigned int) 0;
	}();
	return [&] {
		bool uit = [&] {
			if (!loc) return false;
			else if ((!(--loc % 2) && !(logId = id)) || (loc % 2 && (wId = true) && !(logId = usrId.id[loc %= 2][0]))) logId = usrId.id[loc][0] = usrId.newIdF(), usrId.tijd[loc][0] = p_clstijd->minuut.load();
			return true;
		}();
		mut.unlock(); return uit;
	 }();
}

unsigned int clswbusr2::voegid(unsigned int usrno) {
	mut.lock(); unsigned int& p = usrId.id[usrno][0];
	if (!p) usrId.tijd[usrno][0] = p_clstijd->minuut.load(), p = usrId.newIdF();
	mut.unlock();
	return p;
	}

unsigned int clswbusr2::userIdStr::newIdF() {
	unsigned int uit = 1; srand(time(NULL)); for (int8_t T = 0; T < 24; T++) uit += rand() % 32767; unsigned int ar[WEBUSR_CNT * 2], T = [&] {
		for (int t = 0, m = WEBUSR_CNT * 2; t < m; t++) ar[t] = 0;
		unsigned int niet, now = niet = 0, v, t;
		for (int t2 = t = 0, m = WEBUSR_CNT * 2; t2 < m || ((ar[t++] = niet = now) && !(now = t2 = 0) && (t < m || !++t)); t2++)
			if ((v = id[t2 / 2][t2 % 2]) && (!niet || v < niet) && v > now) now = v;
		return t - 1;
	}(); while (T--) if (uit >= ar[T]) uit++; return uit;
}
#include "threadBuf.h"

threadBufCls& p_TrBC = *new threadBufCls();
extern mutex ffMut;
void threadBufCls::recStruct::start(void* pnt, void* pnt2) { mutAanv.lock(), p_TrBC.start(tObjS::vStrS{ pF, pnt, pnt2 }), mutAanv.unlock(); }

void threadBufCls::start(tObjS::vStrS s) {
	allMut.lock(); 
	for (unsigned int t = 0; t < THRDBFCLS_CNT; t++)
		if (avCnt[avNow = (avNow + 1) % THRDBFCLS_CNT]) {
			avCnt[t = avNow]--, allMut.unlock(), tObj[t].voeg(s);
			return;
		} 
	allMut.unlock(), thread([](tObjS::vStrS s) { s.f(); }, s).detach();
}

void threadBufCls::tObjS::voeg(tObjS::vStrS& s) {
	{
		unique_lock<mutex> lk(mut); cvU.wait(lk, [&] { return !ready; });
		ready = true, vStr[20] = s;
	} cv.notify_one();
}

void threadBufCls::tObjS::func(uint8_t n) {
	while (true) {
		bMut.lock(), p_TrBC.raise(n), bMut.unlock();
		{
			unique_lock<mutex> lk(mut);
			cv.wait(lk, [&] { return ready; });
			ready = false, vStr[n] = vStr[20];
		} cvU.notify_one();
		vStr[n].f();
	}
}

void threadBufCls::threadBufCls::open() {
	for (unsigned int t = 0, m = THRDBFCLS_CNT; t < m && [&] { allMut.lock(), avCnt[t] = 0, allMut.unlock(); return true; }(); t++)
		for (int8_t tt = 0; tt < 20; tt++) thread([](tObjS* p, uint8_t n) { p->func(n); }, tObj + t, tt).detach();
}
#include "ThreadCls.h"

bool mainThreadCls::strMpCh::begin(mainThreadCls::strSndV s) {
	mut.lock();
	if (ready) { ready = false; mut.unlock(); p = s; return true; }
	if (lineCnt < ARSIZE_CLSMPCH) lineAr[(lineNo + lineCnt) % ARSIZE_CLSMPCH] = lAS{ val++, voeg(s, avAr[lineCnt]) }, lineCnt++;
	else mp.insert(pair<unsigned int, strSndV>(val++, { s }));
	mut.unlock();
	return false;
}

bool mainThreadCls::strMpCh::end() {
	mut.lock();
	if (val != set) {
		if (lineCnt && lineAr[lineNo].cnt == set) p = ar[lineAr[lineNo].no], avAr[--lineCnt] = lineAr[lineNo].no, lineNo = (lineNo + 1) % ARSIZE_CLSMPCH, set++;
		else p = mp.find(set)->second, mp.erase(set++);
		mut.unlock();
		return false;
	}
	val = set = 0; ready = true;
	mut.unlock();
	return true;
}

bool mainThreadCls::strMpCha::begin(uint16_t& s) {
	mut.lock();
	if (ready) { ready = false; mut.unlock(); p = s; return true; }
	if (lineCnt < ARSIZE_CLSMPCH) lineAr[(lineNo + lineCnt) % ARSIZE_CLSMPCH] = lAS{ val++, voeg(s, avAr[lineCnt]) }, lineCnt++;
	else mp.insert(pair<unsigned int, uint16_t>(val++, { s }));
	mut.unlock();
	return false;
}

bool mainThreadCls::strMpCha::end() {
	mut.lock();
	if (val != set) {
		if (lineCnt && lineAr[lineNo].cnt == set) p = ar[lineAr[lineNo].no], avAr[--lineCnt] = lineAr[lineNo].no, lineNo = (lineNo + 1) % ARSIZE_CLSMPCH, set++;
		else p = mp.find(set)->second, mp.erase(set++);
		mut.unlock();
		return false;
	}
	val = set = 0; ready = true;
	mut.unlock();
	return true;
}



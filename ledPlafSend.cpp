#include "ledPlaf.h"

void mainThreadCls::clsLedPl::clsLedPlObj::progPsMs() {
	bool x;
	do {
		if (!blAgg)
			if (agglineCnt < ARSIZE_CLSMPCH) agglineAr[(agglineNo + agglineCnt) % ARSIZE_CLSMPCH] = lAS{ aggVal++, aggvoeg(progS, aggavAr[agglineCnt]) }, agglineCnt++;
			else mpAgg.insert(pair<unsigned int, strSndV>(aggVal++, progS));
		else if (!progress()) blAgg = false; 
		{
			unique_lock<mutex> lk(cvPsMs.mut); cvPsMs.ready = !(x = cvPsMs.ready);
			if (x) cvPsMsBl = true, progS = sndS;
		} cvPsMs.cv.notify_one();
	} while (x);
}

void mainThreadCls::clsLedPl::clsLedPlObj::flagPsMs() {
	blAgg = true; 
	while (blAgg && aggSet != aggVal) {
		if (agglineCnt && agglineAr[agglineNo].cnt == aggSet) progS = aggar[agglineAr[agglineNo].no], aggavAr[--agglineCnt] = agglineAr[agglineNo].no, agglineNo = (agglineNo + 1) % ARSIZE_CLSMPCH, aggSet++;
		else progS = mpAgg.find(aggSet)->second, mpAgg.erase(aggSet++);
		if (!progress()) blAgg = false;
	}
	bool x; {
		unique_lock<mutex> lk(cvPsMs.mut); cvPsMs.ready = !(x = cvPsMs.ready);
		if (x) progS = sndS, cvPsMsBl = true;
		
	}  cvPsMs.cv.notify_one(); if (x) progPsMs();
}

void mainThreadCls::clsLedPl::clsLedPlObj::empPsMs() {
	blAgg = true; 
	while (aggSet != aggVal) 
		if (agglineCnt && agglineAr[agglineNo].cnt == aggSet) aggar[agglineAr[agglineNo].no].ret(), aggavAr[--agglineCnt] = agglineAr[agglineNo].no, agglineNo = (agglineNo + 1) % ARSIZE_CLSMPCH, aggSet++;
		else mpAgg.find(aggSet++)->second.ret();
	mpAgg.clear(); bool x; {
		unique_lock<mutex> lk(cvPsMs.mut); cvPsMs.ready = !(x = cvPsMs.ready);
		if (x) progS = sndS, cvPsMsBl = true;
	}  cvPsMs.cv.notify_one(); if (x) progPsMs();
}

bool mainThreadCls::clsLedPl::clsLedPlObj::progress() {
	bool agg = true; trLisHomeCls* ppp = threadCls->sesPoint(threadCls->sesPMut + adr, threadCls->adresNo(adr)); {
		int ll = progS.len; char* ss = progS.pack; while (ss[--ll] != '\\'); 
		if (progS.len - ll > 6 && (*ss == '$' || *ss == '#')) agg = false;
	} progS.len = (progS.len + 1) * (-1);
	if (ppp) ppp->sendPrep(progS, threadCls->mpChS[adr][adr]);
	else progS.ret(), agg = true;
	return agg;
}
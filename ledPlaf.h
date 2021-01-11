#pragma once
#include "ThreadCls.h"
#define LEDPL_VARAANT 14
#define LEDPL_VARAANT1 4
#define LEDPL_VARAANT2 1

extern uint8_t LEDPL_CNT;

class mainThreadCls::clsLedPl {
public:
	void begin();
private:
	struct clsLedPlObj; 
	mutex threadMut;
	friend struct clsExMes::strExec; friend struct stSndStt; friend class trLisHomeCls; friend class extCls; friend class clsNSite; 
	map<uint8_t, clsLedPlObj&> mpObj;
	clsLedPlObj* toObjF(uint8_t adr) { map<uint8_t, clsLedPlObj&>::iterator it = mpObj.find(adr); if (it != mpObj.end()) return &it->second; else return NULL; }
};

struct mainThreadCls::clsLedPl::clsLedPlObj {
	strStrCnt& mpCh;
	uint8_t no; 
	uint8_t adr; 
	uint8_t stripCnt;
	void reqFunc();
	atomic<unsigned int> upN = 1;
	atomic<uint8_t> upM = 0;
	atomic<uint8_t> upD = 0;
	atomic<uint8_t> upU = 0;
	atomic<uint8_t> upMi = 0;
	atomic<uint8_t> upS = 0;
	char bufPsMs[32];
	strSndV sndS; strSndV progS; strSndV voegS;
	bool ledPlFunc(strSndV s);
	void varFunc(char* xLs, int xLen);
	void atDetFunc(char* xLs, int xLen);
	bool varSFunc(uint8_t noStr, uint8_t noVal, unsigned long wVal);
	void setVal(uint8_t n, unsigned long v, uint8_t c);
	shared_mutex varMut;
	map<unsigned int, char*> mpPoint; 
	mutex mutPoint;

	unsigned int mpVal = 0;
	uint8_t mplineNo = 0;
	char* mpar[ARSIZE_CLSMPCH];
	uint8_t mpvoeg(char* s, uint8_t no) { mpar[no] = s; return no; }
	uint8_t mpavAr[ARSIZE_CLSMPCH];
	uint8_t mplineCnt = mainThreadCls::set_ClsMpCh(mpavAr);

	struct lAS {
		unsigned int cnt;
		uint8_t no;
	};

	lAS mplineAr[ARSIZE_CLSMPCH];

	unsigned int mpPointF(char* x) {
		mutPoint.lock();
		if (mplineCnt < ARSIZE_CLSMPCH) mplineAr[(mplineNo + mplineCnt) % ARSIZE_CLSMPCH] = lAS{ mpVal, mpvoeg(x, mpavAr[mplineCnt]) }, mplineCnt++;
		else mpPoint.insert(pair<unsigned int, char*>(mpVal, { x }));
		mutPoint.unlock();
		return mpVal++;
	}

	struct varStr {
		bool* parChldAr;
		uint8_t parChld = 1;
		uint8_t helder = 0;
		uint8_t rgbPauze = 0;
		bool negDlay = false;
		unsigned int gamDlay = 0;
		bool negGamDlay = false;
		unsigned int gamPer = 0;
		uint8_t gamClr = 0;
		uint8_t gamVal = 0;
		uint8_t gamIVal = 0;
		uint8_t gamIHel = 0;
		unsigned int helDlay = 0;
		bool negHelCur = 0;
		uint8_t gamPauze = 0;
		uint8_t helAmp = 0;
		unsigned int dlay = 0;
		uint8_t gamInterval = 0;
		unsigned int helPer = 0;
		unsigned int per = 0;
		uint8_t randVar = 0;
		unsigned int val(uint8_t x); unsigned int voegChld(uint8_t b, uint8_t m, char* ls, bool* gezet) {
			unsigned int u = 0; for (uint8_t t = b; t < m; t++) if (parChldAr[t]) gezet[t] = true, ls[u++] = '_', ls[u++] = strbasprc::cvintcharchar(t); return u;
		} 
	}; varStr* var;
	map<unsigned int, strSndV> mpAgg; unsigned int aggVal = 0; unsigned int aggSet = 0; bool blAgg = true;
	uint8_t agglineNo = 0;
	strSndV aggar[ARSIZE_CLSMPCH];
	uint8_t aggvoeg(strSndV s, uint8_t no) { aggar[no] = s; return no; }
	uint8_t aggavAr[ARSIZE_CLSMPCH];
	uint8_t agglineCnt = mainThreadCls::set_ClsMpCh(aggavAr);

	lAS agglineAr[ARSIZE_CLSMPCH];

	strCv cvPsMs{ true }; bool cvPsMsBl = true; void psMsPr(); void flagPsMsPr(); void empPsMsPr(); void psMsPr2(strSndV& s);
	void passPrep(strSndV s, strMpCh& pMCh, uint8_t ad); void pass(strSndV& s); strMpCh passMp; void progPsMs(); void flagPsMs(); void empPsMs(); bool progress();
	bool* gezet;
	clsLedPlObj& begin() { 
		sndS.len = 0, sndS.bron = NULL, voegS = sndS, sndS.lsNo = mpCh.get(sndS.pack), voegS.lsNo = mpCh.get(voegS.pack), *voegS.pack = '&', voegS.len = 1; 
		uint8_t tel = 0; varStr* t = var = new varStr[stripCnt]; while (tel < stripCnt) {
		t->parChldAr = new bool[stripCnt];
		for (uint8_t tt = 0; tt < stripCnt; tt++) if (tt == tel) t->parChldAr[tt] = true; else t->parChldAr[tt] = false; t++; gezet = new bool[stripCnt]; tel++;
		} return *this;
	} void voegFrCons(strSndV s, uint8_t ad); strMpCh voegMpCh; void voegF(strSndV &s); void remChld(uint8_t x) {
		for (uint8_t t, t2 = t = 0, m = var[x].parChld; t2 < m; t++) if (t == x) t2++; else if (var[x].parChldAr[t]) t2++, var[t].parChldAr[x] = false, var[t].parChld--;
	}
};

extern mainThreadCls::clsLedPl& p_ledPl;
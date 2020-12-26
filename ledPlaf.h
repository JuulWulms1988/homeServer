#pragma once
#include "ThreadCls.h"
#define LEDPL_VARAANT 14
#define LEDPL_VARAANT1 4
#define LEDPL_VARAANT2 1

extern unsigned __int8 LEDPL_CNT;

class mainThreadCls::clsLedPl {
public:
	void begin();
private:
	struct clsLedPlObj; 
	mutex threadMut;
	friend struct clsExMes::strExec; friend struct stSndStt; friend class trLisHomeCls; friend class extCls; friend class clsNSite; 
	map<unsigned __int8, clsLedPlObj&> mpObj;
	clsLedPlObj* toObjF(unsigned __int8 adr) { map<unsigned __int8, clsLedPlObj&>::iterator it = mpObj.find(adr); if (it != mpObj.end()) return &it->second; else return NULL; }
};

struct mainThreadCls::clsLedPl::clsLedPlObj {
	strStrCnt& mpCh;
	unsigned __int8 no; 
	unsigned __int8 adr; 
	unsigned __int8 stripCnt;
	void reqFunc();
	atomic<unsigned int> upN = 1;
	atomic<unsigned __int8> upM = 0;
	atomic<unsigned __int8> upD = 0;
	atomic<unsigned __int8> upU = 0;
	atomic<unsigned __int8> upMi = 0;
	atomic<unsigned __int8> upS = 0;
	char bufPsMs[32];
	strSndV sndS; strSndV progS; strSndV voegS;
	bool ledPlFunc(strSndV s);
	void varFunc(char* xLs, int xLen);
	void atDetFunc(char* xLs, int xLen);
	bool varSFunc(unsigned __int8 noStr, unsigned __int8 noVal, unsigned long wVal);
	void setVal(unsigned __int8 n, unsigned long v, unsigned __int8 c);
	shared_mutex varMut;
	map<unsigned int, char*> mpPoint; 
	mutex mutPoint;

	unsigned int mpVal = 0;
	unsigned __int8 mplineNo = 0;
	char* mpar[ARSIZE_CLSMPCH];
	unsigned __int8 mpvoeg(char* s, unsigned __int8 no) { mpar[no] = s; return no; }
	unsigned __int8 mpavAr[ARSIZE_CLSMPCH];
	unsigned __int8 mplineCnt = mainThreadCls::set_ClsMpCh(mpavAr);

	struct lAS {
		unsigned int cnt;
		unsigned __int8 no;
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
		unsigned __int8 parChld = 1;
		unsigned __int8 helder = 0;
		unsigned __int8 rgbPauze = 0;
		bool negDlay = false;
		unsigned int gamDlay = 0;
		bool negGamDlay = false;
		unsigned int gamPer = 0;
		unsigned __int8 gamClr = 0;
		unsigned __int8 gamVal = 0;
		unsigned __int8 gamIVal = 0;
		unsigned __int8 gamIHel = 0;
		unsigned int helDlay = 0;
		bool negHelCur = 0;
		unsigned __int8 gamPauze = 0;
		unsigned __int8 helAmp = 0;
		unsigned int dlay = 0;
		unsigned __int8 gamInterval = 0;
		unsigned int helPer = 0;
		unsigned int per = 0;
		unsigned __int8 randVar = 0;
		unsigned int val(unsigned __int8 x); unsigned int voegChld(unsigned __int8 b, unsigned __int8 m, char* ls, bool* gezet) {
			unsigned int u = 0; for (unsigned __int8 t = b; t < m; t++) if (parChldAr[t]) gezet[t] = true, ls[u++] = '_', ls[u++] = strbasprc::cvintcharchar(t); return u;
		} 
	}; varStr* var;
	map<unsigned int, strSndV> mpAgg; unsigned int aggVal = 0; unsigned int aggSet = 0; bool blAgg = true;
	unsigned __int8 agglineNo = 0;
	strSndV aggar[ARSIZE_CLSMPCH];
	unsigned __int8 aggvoeg(strSndV s, unsigned __int8 no) { aggar[no] = s; return no; }
	unsigned __int8 aggavAr[ARSIZE_CLSMPCH];
	unsigned __int8 agglineCnt = mainThreadCls::set_ClsMpCh(aggavAr);

	lAS agglineAr[ARSIZE_CLSMPCH];

	strCv cvPsMs{ true }; bool cvPsMsBl = true; void psMsPr(); void flagPsMsPr(); void empPsMsPr(); void psMsPr2(strSndV& s);
	void passPrep(strSndV s, strMpCh& pMCh, unsigned __int8 ad); void pass(strSndV& s); strMpCh passMp; void progPsMs(); void flagPsMs(); void empPsMs(); bool progress();
	bool* gezet;
	clsLedPlObj& begin() { 
		sndS.len = 0, sndS.bron = NULL, voegS = sndS, sndS.lsNo = mpCh.get(sndS.pack), voegS.lsNo = mpCh.get(voegS.pack), *voegS.pack = '&', voegS.len = 1; 
		unsigned __int8 tel = 0; varStr* t = var = new varStr[stripCnt]; while (tel < stripCnt) {
		t->parChldAr = new bool[stripCnt];
		for (unsigned __int8 tt = 0; tt < stripCnt; tt++) if (tt == tel) t->parChldAr[tt] = true; else t->parChldAr[tt] = false; t++; gezet = new bool[stripCnt]; tel++;
		} return *this;
	} void voegFrCons(strSndV& s, unsigned __int8 ad); strMpCh voegMpCh; void voegF(strSndV &s); void remChld(unsigned __int8 x) {
		for (unsigned __int8 t, t2 = t = 0, m = var[x].parChld; t2 < m; t++) if (t == x) t2++; else if (var[x].parChldAr[t]) t2++, var[t].parChldAr[x] = false, var[t].parChld--;
	}
};

extern mainThreadCls::clsLedPl& p_ledPl;
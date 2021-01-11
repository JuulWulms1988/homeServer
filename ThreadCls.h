#pragma once
#include <stdint.h>
#include "Basproc.h"
#include <map>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <condition_variable>
#include "ServerGame.h"
#include "threadBuf.h"
#define ARSIZE_CLSMPCH 100
//#define MAX_PACKET_SIZE 1000
#define DELAY_VAL_SET 2
extern uint8_t LEDPL_CNT;
extern void* bootPtrAlg;

//
#include "clstijd.h"

#ifndef _WIN32
#include <unistd.h>
#endif

extern clstijd* p_clstijd;
extern bool kaasdel;
extern mutex ffMut;
//

extern char* charPrint(unsigned int x, string& a);
extern void printTijdel(char** p, unsigned int l);
using namespace std;

class mainThreadCls;

struct strCv {
	bool ready;
	mutex mut;
	condition_variable cv;
};

class extCls {
public:
	static void begin();
	static void end();
	static bool piSPlay(int8_t x);
	static void piSWrite(uint8_t i, char* x);
	static void* piSRead(uint8_t i);
	static char* read(char* x, ifstream& i) { unsigned int tel = 0; char t; while ((t = i.get()) != '\n' && t != -1 && !i.eof()) x[tel++] = t; x[tel] = '\0'; return x; }
};

class mainThreadCls {
public:
	struct timedComNoStr {
		shared_mutex mut;
		unsigned int now = 0;
		unsigned int set() { mut.lock(); unsigned int V = ++now; mut.unlock(); return V; }
		class get {
		public:
			shared_mutex* p;
			bool appr;
			get(unsigned int x, timedComNoStr& y) { (p = &y.mut)->lock_shared(); if (y.now == x) appr = true; else appr = false; }
			~get() { p->unlock_shared(); }
		};
	} timedComNoS[100];
	class radioStr;
	static void sluisPiScreenF(uint16_t s, uint8_t ad);
	static void killProc(const char* x);
	struct deBootStr {
		mutex mut;
		uint8_t stat = 0;
		condition_variable cvMain;
		condition_variable cvSub;
		void subF() {
			bool uit = false;
			{
				unique_lock<mutex> lk(mut);
				if (++stat == 2) cvMain.notify_one();
				cvSub.wait(lk, [&] { return stat / 3; });
				if (stat++ == 4) uit = true;
			} if (uit) delete this;
		}
		void mainF() {
			{ unique_lock<mutex>lk(mut); cvMain.wait(lk, [&] { return stat / 2; }), stat++;	} cvSub.notify_all();
		}
	};
	static void piScreenOffSluis(uint16_t ad);
	mutex threadMut[101];
	static uint8_t set_ClsMpCh(uint8_t* p) { for (int8_t t = 0, i = ARSIZE_CLSMPCH - 1; t < ARSIZE_CLSMPCH; t++) p[t] = i--; return 0; }
	int jgjgjg = 2;
	void jajaja() { ffMut.lock(); cout << "EEEJ: " << jgjgjg << "\n"; ffMut.unlock(); }

	class clsExMes;
	class clsLedPl;
	struct strSndV {
		char* pack;
		int len;
		clsExMes* bron;
		int8_t lsNo;
		void ret();
		unsigned int voegChar(char x) { pack[len++] = x; return len; }
	};
	/*
	struct strMpCh {
		uint8_t ad;
		unsigned int set = 0;
		unsigned int val = 0;
		bool ready = true;
		mutex mut;
		map<unsigned int, strSndV> mp;
		bool begin(strSndV& s);
		bool end();
		strSndV p;
		void wait(condition_variable& cv) { cv.wait(unique_lock<mutex>(mut), [&] { return ready; }); }
	};

	*/



	struct strMpCh {


		//void func(Functor x);

		uint8_t ad;
		unsigned int set = 0;
		unsigned int val = 0;
		bool ready = true;
		mutex mut;
		map<unsigned int, strSndV> mp;
		bool begin(strSndV s);
		bool end();
		strSndV p;
		void wait(condition_variable& cv) { unique_lock<mutex>lk(mut); cv.wait(lk, [&] { return ready; }); }
		uint8_t lineNo = 0;
		strSndV ar[ARSIZE_CLSMPCH];
		uint8_t voeg(strSndV s, uint8_t no) { ar[no] = s; return no; }
		uint8_t avAr[ARSIZE_CLSMPCH];
		uint8_t lineCnt = mainThreadCls::set_ClsMpCh(avAr);

		struct lAS {
			unsigned int cnt;
			uint8_t no;
		};

		lAS lineAr[ARSIZE_CLSMPCH];



	};
	struct strMpCha {


		//void func(Functor x);

		uint8_t ad;
		unsigned int set = 0;
		unsigned int val = 0;
		bool ready = true;
		mutex mut;
		map<unsigned int, uint16_t> mp;
		bool begin(uint16_t& s);
		bool end();
		uint16_t p;
		void wait(condition_variable& cv) { unique_lock<mutex>lk(mut); cv.wait(lk, [&] { return ready; }); }
		uint8_t lineNo = 0;
		uint16_t ar[ARSIZE_CLSMPCH];
		uint8_t voeg(uint16_t s, uint8_t no) { ar[no] = s; return no; }
		uint8_t avAr[ARSIZE_CLSMPCH];
		uint8_t lineCnt = mainThreadCls::set_ClsMpCh(avAr);

		struct lAS {
			unsigned int cnt;
			uint8_t no;
		};

		lAS lineAr[ARSIZE_CLSMPCH];



	};
	class trLisHomeCls;
		
	struct strStrCnt {
		unsigned int len; uint8_t no;
		strStrCnt& open(int8_t c, unsigned int n, unsigned int l);
		int8_t get(char*& x);
		void ret(int8_t x) { (lock_guard<mutex>(mut)), lsA[lsT++] = -x - 1; cv.notify_one(); }
		void wait() { unique_lock<mutex>lk(mut); cv.wait(lk, [&] { return (lsT + 1) / (cnt + 1); }); };
		char* lPosF(char* x, unsigned int y) { for (uint8_t t = 0; t < 2; t++) x[y + t] = x[len - 2 + t]; return x; }
		static unsigned int lPosObNoF(char* x, unsigned int l, bool type);
		int8_t cnt;
		int8_t lsT;
		char* ls;
		int8_t* lsA;
		condition_variable cv;
		mutex mut;
	}; strStrCnt* strCntS;
	class clsExMes {
	public:
		clsExMes(trLisHomeCls* pp);
		~clsExMes();
		trLisHomeCls* pLisHome;
		static void naCheckF(strSndV s, uint8_t ad, uint8_t ad2);
		struct exStr;
		struct var {
			char* x;
			int8_t lsNow;
			uint8_t len;
			int8_t type;
		};
		struct exStr;
		struct strExec {
			void set(clsExMes* p, int8_t x);
			clsExMes* point = NULL;
			exStr* pExMp;
			void psPlayF(uint8_t x, uint8_t ad);
			memFileObj fileObj;
			trLisHomeCls* bufXX;
			char* file;
			var strVarS;
			void sluisPiScreenFC();
			//int8_t vgstrVarS(int8_t x) {  }
			unsigned int getPointLed(char* x);
			unsigned long fLoc;
			void fLock() { file = fileObj.file, fLoc = fileObj.loc; }
			void fUnlock() { fileObj.file = file, fileObj.loc = fLoc; }
			bool blDim;
			int8_t lsNow;
			char* ls;
			char* str;
			int8_t strNow;
			char buf[64];
			char buf2[64];
			int8_t now;
			uint8_t bufX;
			uint8_t sendLen;
			int len;
			uint8_t strAd;
			uint8_t zendId;
			void start();
			void main();
			void cancel();
			bool passMes();
			void readMes();
			void send(bool x);
			void passLpFromC();
			void voegLedPlaf(uint8_t ad);
			void sendLedPl(uint8_t ad);
			void piScreenF();
			void temp();
			void naCheck(strSndV& s, uint8_t ad);
			void stReq();
			void actionFunc(); void actionWFunc();
			bool stverzDim();
			strSndV* sStrBuf = NULL;
		};
		struct exStr {
			clsExMes* point;
			mutex mut;
			mutex mutLdPlPoint;
			int8_t iNo = 0;
			int8_t iT = 20;
			int8_t iA[20];
			strExec i[20];
			void set(int8_t t, int8_t z) { iA[t] = i[t].now = z; };
			unsigned int valF = 0;
			unsigned int setF = 0;
			unsigned int setS = 0;
			unsigned int valS = 0;
			bool com = 0;
			bool ready = true;
			bool diff(bool x) { if (x) return valF - setF; return valS - setS; }
			bool avail() { return diff(false) + diff(true); }
			bool comF() { return diff(true) * diff(false); }
			void wait() { { unique_lock<mutex>lk(mut); cv.wait(lk, [&] {return (iT / 20); }); } for (uint8_t t = 0; t < 20; t++) i[t].cancel(); }
			map<unsigned int, var> mpS;
			map<unsigned int, var> mpF;
			condition_variable cv;
			void voeg(var s);
			bool ret(var& s, int8_t n);
			uint8_t lineNo = 0;
			var ar[ARSIZE_CLSMPCH];
			uint8_t voegf(var s, uint8_t no) { ar[no] = s; return no; }
			uint8_t avAr[ARSIZE_CLSMPCH];
			uint8_t lineCnt = mainThreadCls::set_ClsMpCh(avAr);
			struct lAS {
				unsigned int cnt;
				uint8_t no;
			};

			lAS lineAr[ARSIZE_CLSMPCH];
			uint8_t lineNof = 0;
			var arf[ARSIZE_CLSMPCH];
			uint8_t voegff(var s, uint8_t no) { arf[no] = s; return no; }
			uint8_t avArf[ARSIZE_CLSMPCH];
			uint8_t lineCntf = mainThreadCls::set_ClsMpCh(avArf);


			lAS lineArf[ARSIZE_CLSMPCH];


		} exCls{ this };
		condition_variable cvSend;
		mutex sendMut;
		strCv cvEx;
		int8_t getStr(char*& x);
		void retStr(int8_t x) { (lock_guard<mutex>(sendMut)), lsA[lsT++] = x; cvSend.notify_one(); };
		char lsP[3200];
		int8_t lsT = 99;
		int8_t lsA[100];
	private:
		uint8_t strAd;
	};
	mainThreadCls();

	struct exMesOne {
		trLisHomeCls* bufX;
		int sendLen;
		char* ls;
		int8_t lsNow;
		uint8_t strAd;
		uint8_t zendId;
		void tijdPr();
		void tijdUpdate();
		void tijdUpdate2(char update, uint8_t adress);
		void send();
		void chckSiteAd();
		void chckTelAd();
	};


	//char* 
	void voegAdr(uint8_t sess);
	void checkAdr(uint8_t min);
	mutex mutChkAd;
	bool blArdChk[2];
	atomic<bool> blmutChkAd{ false };
	map<uint8_t, int8_t> mpChkAd;
	void tijdProc();
	bool sesFull = false;
	class trLisHomeCls {
	public:
		trLisHomeCls();
		mutex mutSend;
		//strCv cvSend{false};
		strCv cvLis{ true };
		void loop(SOCKET* sock);
		void sendPrep(strSndV s, strMpCh&);
		void send(strSndV& s, uint8_t ad);
		void sendPr();
		atomic<bool> available;
		atomic<bool> close;
		atomic<bool> del;
		SOCKET socket;
		unsigned int strLen = 0;
		atomic<uint8_t> adrs;
		clsExMes* exMes = new clsExMes(this);
		atomic<uint8_t> mpSesNo;
		void closeF() { del.store(true); NetworkMethods::sockCloseF(socket); }
		unsigned int timedComNo;
	private:
		friend struct clsExMes::strExec;
		void chSerAgg(strSndV& s); void chSerAggPl(uint8_t adrB);
		clsExMes::exStr* exCls{ &exMes->exCls };
		const char aanv[3] = { '-', '@', '#' };
		char thisChar;
		char* mesStr = exMes->lsP;
		bool sendReady;
		char* lpStr;
		bool timedMesF(strSndV s);
		void timedRadF(char* x);
		char dimCBuf[128];
		int dimCBufLen;
		char* dimLs;
		int dimSendLen;
		int8_t dimLsNow;
		memFileObj dimFileObj = memFileObj(fileData);
		void dimExF(strSndV s);
		void dimExAF(char* str, int len);
		uint8_t dimRicht; uint8_t dimW;
		int8_t exNow = 0;
		bool lsAr;
		char ls[2][1001];
		int iResult;
		uint8_t adAd;
		mutex muClose;
		condition_variable cvClose;
		bool closeMut;
		bool readySend;
		map <unsigned int, strSndV> sendMp;
		unsigned int sendVal;
		unsigned int sendSet;


		uint8_t sndlineNo = 0;
		strSndV sndar[ARSIZE_CLSMPCH];
		uint8_t sndvoeg(strSndV s, uint8_t no) { sndar[no] = s; return no; }
		uint8_t sndavAr[ARSIZE_CLSMPCH];
		uint8_t sndlineCnt = mainThreadCls::set_ClsMpCh(sndavAr);
		strSndV sndSStr;

		struct lAS {
			unsigned int cnt;
			uint8_t no;
		};

		lAS sndlineAr[ARSIZE_CLSMPCH];


		uint8_t strAanv;
		void messPr(char* mes, unsigned int len);
	}webLisHome;



	trLisHomeCls* accHome;
	void trAcc(SOCKET* s);
	bool newSes();
	trLisHomeCls* sesPoint(mutex* mut, uint8_t no);
	uint8_t adresNo(uint8_t no);
	strCv cvAcc = { true };
	struct stSndStt {
		uint8_t type;
		unsigned int no;
		uint8_t val;
		unsigned long loc;
		clsExMes* p;
		char* fl;
		strSndV s;
		void func();
		void funcSnd();
		void funcSnd2();
		void ledPlF(char* ls, int8_t lsNow, uint8_t strAd);
		void funcD();
		//void ledPlF(char* ls, int8_t lsNow, uint8_t strAd);
	};
	struct statStrucStr {
		stSndStt sluisS;
		map<unsigned int, stSndStt> mp;
		unsigned int val; unsigned int set = val = 0;
		bool ready = true; mutex mut;
		void start(stSndStt st, uint8_t ad);
		bool check();
		uint8_t lineNo = 0;

		stSndStt ar[ARSIZE_CLSMPCH];
		uint8_t voeg(stSndStt s, uint8_t no) { ar[no] = s; return no; }
		uint8_t avAr[ARSIZE_CLSMPCH];
		uint8_t lineCnt = mainThreadCls::set_ClsMpCh(avAr);
		struct lAS {
			unsigned int cnt;
			uint8_t no;
		};

		lAS lineAr[ARSIZE_CLSMPCH];
	}statStruc[1800];
	//clsExMes* pTMes = new clsExMes(NULL);
	atomic<bool> statVar[900];
	atomic<int> statDimVar[900];
	strMpCh* mpChS[100];
	strMpCh naChckMpCh[100];
	strMpCh timedMesMpCh[100];
	clsExMes::strExec uitEx[100];
	mutex sesPMut[100];
	strMpCh naCh2Mp[100][100];
	mutex sesPDMut;
private:
	friend class trLisHomeCls;
	friend class clsMes;
	friend class clsExMes;

	//friend class clsExMes::strExec;
	bool delay;
	void openLdPl();
	map<uint8_t, trLisHomeCls*> ses;
	shared_mutex sMutSes;
	shared_mutex sMutAdr;
	uint8_t adress[100];
	strCv cvAccFull{ false };
	mutex timeMut;
	char radBuf[332]{ 's', 't', 'a', 'r', 't', ' ', '\"', 'C', ':', '/', 'P', 'r', 'o', 'g', 'r', 'a', 'm', ' ', 'F', 'i', 'l', 'e', 's', ' ', '(', 'x', '8', '6', ')', '/', 'G', 'o', 'o', 'g', 'l', 'e', '/', 'C', 'h', 'r', 'o', 'm', 'e', '/', 'A', 'p', 'p', 'l', 'i', 'c', 'a', 't', 'i', 'o', 'n', '\"', ' ', '\"', 'c', 'h', 'r', 'o', 'm', 'e', '.', 'e', 'x', 'e', '\"', ' ', '\"' };
};

extern mainThreadCls* threadCls;



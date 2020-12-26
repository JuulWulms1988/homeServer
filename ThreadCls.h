#pragma once
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
extern unsigned __int8 LEDPL_CNT;
extern void* bootPtrAlg;

//
#include "clstijd.h"

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
	static bool piSPlay(__int8 x);
	static void piSWrite(unsigned __int8 i, char* x);
	static void* piSRead(unsigned __int8 i);
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
	static void sluisPiScreenF(unsigned __int16 s, unsigned __int8 ad);
	static void killProc(char* x);
	struct deBootStr {
		mutex mut;
		unsigned __int8 stat = 0;
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
			cvMain.wait(unique_lock<mutex>(mut), [&] { return stat / 2; }), stat++; cvSub.notify_all();
		}
	};
	static void piScreenOffSluis(unsigned __int16 ad);
	mutex threadMut[101];
	static unsigned __int8 set_ClsMpCh(unsigned __int8* p) { for (__int8 t = 0, i = ARSIZE_CLSMPCH - 1; t < ARSIZE_CLSMPCH; t++) p[t] = i--; return 0; }
	int jgjgjg = 2;
	void jajaja() { ffMut.lock(); cout << "EEEJ: " << jgjgjg << "\n"; ffMut.unlock(); }

	class clsExMes;
	class clsLedPl;
	struct strSndV {
		char* pack;
		int len;
		clsExMes* bron;
		__int8 lsNo;
		void ret();
		unsigned int voegChar(char x) { pack[len++] = x; return len; }
	};
	/*
	struct strMpCh {
		unsigned __int8 ad;
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

		unsigned __int8 ad;
		unsigned int set = 0;
		unsigned int val = 0;
		bool ready = true;
		mutex mut;
		map<unsigned int, strSndV> mp;
		bool begin(strSndV& s);
		bool end();
		strSndV p;
		void wait(condition_variable& cv) { cv.wait(unique_lock<mutex>(mut), [&] { return ready; }); }
		unsigned __int8 lineNo = 0;
		strSndV ar[ARSIZE_CLSMPCH];
		unsigned __int8 voeg(strSndV s, unsigned __int8 no) { ar[no] = s; return no; }
		unsigned __int8 avAr[ARSIZE_CLSMPCH];
		unsigned __int8 lineCnt = mainThreadCls::set_ClsMpCh(avAr);

		struct lAS {
			unsigned int cnt;
			unsigned __int8 no;
		};

		lAS lineAr[ARSIZE_CLSMPCH];



	};
	struct strMpCha {


		//void func(Functor x);

		unsigned __int8 ad;
		unsigned int set = 0;
		unsigned int val = 0;
		bool ready = true;
		mutex mut;
		map<unsigned int, unsigned __int16> mp;
		bool begin(unsigned __int16& s);
		bool end();
		unsigned __int16 p;
		void wait(condition_variable& cv) { cv.wait(unique_lock<mutex>(mut), [&] { return ready; }); }
		unsigned __int8 lineNo = 0;
		unsigned __int16 ar[ARSIZE_CLSMPCH];
		unsigned __int8 voeg(unsigned __int16 s, unsigned __int8 no) { ar[no] = s; return no; }
		unsigned __int8 avAr[ARSIZE_CLSMPCH];
		unsigned __int8 lineCnt = mainThreadCls::set_ClsMpCh(avAr);

		struct lAS {
			unsigned int cnt;
			unsigned __int8 no;
		};

		lAS lineAr[ARSIZE_CLSMPCH];



	};
	class trLisHomeCls;
		
	struct strStrCnt {
		unsigned int len; unsigned __int8 no;
		strStrCnt& open(__int8 c, unsigned int n, unsigned int l);
		__int8 get(char*& x);
		void ret(__int8 x) { (lock_guard<mutex>(mut)), lsA[lsT++] = -x - 1; cv.notify_one(); }
		void wait() { cv.wait(unique_lock<mutex>(mut), [&] { return (lsT + 1) / (cnt + 1); }); };
		char* lPosF(char* x, unsigned int y) { for (unsigned __int8 t = 0; t < 2; t++) x[y + t] = x[len - 2 + t]; return x; }
		static unsigned int lPosObNoF(char* x, unsigned int l, bool type);
		__int8 cnt;
		__int8 lsT;
		char* ls;
		__int8* lsA;
		condition_variable cv;
		mutex mut;
	}; strStrCnt* strCntS;
	class clsExMes {
	public:
		clsExMes(trLisHomeCls* pp);
		~clsExMes();
		trLisHomeCls* pLisHome;
		static void naCheckF(strSndV& s, unsigned __int8 ad, unsigned __int8 ad2);
		struct exStr;
		struct var {
			char* x;
			__int8 lsNow;
			unsigned __int8 len;
			__int8 type;
		};
		struct exStr;
		struct strExec {
			void set(clsExMes* p, __int8 x);
			clsExMes* point = NULL;
			exStr* pExMp;
			void psPlayF(unsigned __int8 x, unsigned __int8 ad);
			memFileObj fileObj;
			trLisHomeCls* bufXX;
			char* file;
			var strVarS;
			void sluisPiScreenFC();
			__int8 vgstrVarS(__int8 x) {  }
			unsigned int getPointLed(char* x);
			unsigned long fLoc;
			void fLock() { file = fileObj.file, fLoc = fileObj.loc; }
			void fUnlock() { fileObj.file = file, fileObj.loc = fLoc; }
			bool blDim;
			__int8 lsNow;
			char* ls;
			char* str;
			__int8 strNow;
			char buf[64];
			char buf2[64];
			__int8 now;
			unsigned __int8 bufX;
			unsigned __int8 sendLen;
			int len;
			unsigned __int8 strAd;
			unsigned __int8 zendId;
			void start();
			void main();
			void cancel();
			bool passMes();
			void readMes();
			void send(bool x);
			void passLpFromC();
			void voegLedPlaf(unsigned __int8 ad);
			void sendLedPl(unsigned __int8 ad);
			void piScreenF();
			void temp();
			void naCheck(strSndV& s, unsigned __int8 ad);
			void stReq();
			void actionFunc(); void actionWFunc();
			bool stverzDim();
			strSndV* sStrBuf = NULL;
		};
		struct exStr {
			clsExMes* point;
			mutex mut;
			mutex mutLdPlPoint;
			__int8 iNo = 0;
			__int8 iT = 20;
			__int8 iA[20];
			strExec i[20];
			void set(__int8 t, __int8 z) { iA[t] = i[t].now = z; };
			unsigned int valF = 0;
			unsigned int setF = 0;
			unsigned int setS = 0;
			unsigned int valS = 0;
			bool com = 0;
			bool ready = true;
			bool diff(bool x) { if (x) return valF - setF; return valS - setS; }
			bool avail() { return diff(false) + diff(true); }
			bool comF() { return diff(true) * diff(false); }
			void wait() { cv.wait(unique_lock<mutex>(mut), [&] {return (iT / 20); }); for (unsigned __int8 t = 0; t < 20; t++) i[t].cancel(); }
			map<unsigned int, var> mpS;
			map<unsigned int, var> mpF;
			condition_variable cv;
			void voeg(var& s);
			bool ret(var& s, __int8 n);
			unsigned __int8 lineNo = 0;
			var ar[ARSIZE_CLSMPCH];
			unsigned __int8 voegf(var s, unsigned __int8 no) { ar[no] = s; return no; }
			unsigned __int8 avAr[ARSIZE_CLSMPCH];
			unsigned __int8 lineCnt = mainThreadCls::set_ClsMpCh(avAr);
			struct lAS {
				unsigned int cnt;
				unsigned __int8 no;
			};

			lAS lineAr[ARSIZE_CLSMPCH];
			unsigned __int8 lineNof = 0;
			var arf[ARSIZE_CLSMPCH];
			unsigned __int8 voegff(var s, unsigned __int8 no) { arf[no] = s; return no; }
			unsigned __int8 avArf[ARSIZE_CLSMPCH];
			unsigned __int8 lineCntf = mainThreadCls::set_ClsMpCh(avArf);


			lAS lineArf[ARSIZE_CLSMPCH];


		} exCls{ this };
		condition_variable cvSend;
		mutex sendMut;
		strCv cvEx;
		__int8 getStr(char*& x);
		void retStr(__int8 x) { (lock_guard<mutex>(sendMut)), lsA[lsT++] = x; cvSend.notify_one(); };
		char lsP[3200];
		__int8 lsT = 99;
		__int8 lsA[100];
	private:
		unsigned __int8 strAd;
	};
	mainThreadCls();

	struct exMesOne {
		trLisHomeCls* bufX;
		int sendLen;
		char* ls;
		__int8 lsNow;
		unsigned __int8 strAd;
		unsigned __int8 zendId;
		void tijdPr() { thread([&] { while (true) tijdUpdate(), Sleep(10); }).detach(); }
		void tijdUpdate();
		void tijdUpdate2(char update, unsigned __int8 adress);
		void send();
		void chckSiteAd();
		void chckTelAd();
	};


	//char* 
	void voegAdr(unsigned __int8 sess);
	void checkAdr(unsigned __int8 min);
	mutex mutChkAd;
	bool blArdChk[2];
	atomic<bool> blmutChkAd{ false };
	map<unsigned __int8, __int8> mpChkAd;
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
		void send(strSndV& s, unsigned __int8 ad);
		void sendPr();
		atomic<bool> available;
		atomic<bool> close;
		atomic<bool> del;
		SOCKET socket;
		unsigned int strLen = 0;
		atomic<unsigned __int8> adrs;
		clsExMes* exMes = new clsExMes(this);
		atomic<unsigned __int8> mpSesNo;
		void closeF() { del.store(true); closesocket(socket); }
		unsigned int timedComNo;
	private:
		friend struct clsExMes::strExec;
		void chSerAgg(strSndV& s); void chSerAggPl(unsigned __int8 adrB);
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
		__int8 dimLsNow;
		memFileObj dimFileObj = memFileObj(fileData);
		void dimExF(strSndV s);
		void dimExAF(char* str, int len);
		unsigned __int8 dimRicht; unsigned __int8 dimW;
		__int8 exNow = 0;
		bool lsAr;
		char ls[2][1001];
		int iResult;
		unsigned __int8 adAd;
		mutex muClose;
		condition_variable cvClose;
		bool closeMut;
		bool readySend;
		map <unsigned int, strSndV> sendMp;
		unsigned int sendVal;
		unsigned int sendSet;


		unsigned __int8 sndlineNo = 0;
		strSndV sndar[ARSIZE_CLSMPCH];
		unsigned __int8 sndvoeg(strSndV s, unsigned __int8 no) { sndar[no] = s; return no; }
		unsigned __int8 sndavAr[ARSIZE_CLSMPCH];
		unsigned __int8 sndlineCnt = mainThreadCls::set_ClsMpCh(sndavAr);
		strSndV sndSStr;

		struct lAS {
			unsigned int cnt;
			unsigned __int8 no;
		};

		lAS sndlineAr[ARSIZE_CLSMPCH];


		unsigned __int8 strAanv;
		void messPr(char* mes, unsigned int len);
	}webLisHome;



	trLisHomeCls* accHome;
	void trAcc(SOCKET* s);
	bool newSes();
	trLisHomeCls* sesPoint(mutex* mut, unsigned __int8 no);
	unsigned __int8 adresNo(unsigned __int8 no);
	strCv cvAcc = { true };
	struct stSndStt {
		unsigned __int8 type;
		unsigned int no;
		unsigned __int8 val;
		unsigned long loc;
		clsExMes* p;
		char* fl;
		strSndV s;
		void func();
		void funcSnd();
		void funcSnd2();
		void ledPlF(char* ls, __int8 lsNow, unsigned __int8 strAd);
		void funcD();
		//void ledPlF(char* ls, __int8 lsNow, unsigned __int8 strAd);
	};
	struct statStrucStr {
		stSndStt sluisS;
		map<unsigned int, stSndStt> mp;
		unsigned int val; unsigned int set = val = 0;
		bool ready = true; mutex mut;
		void start(stSndStt& st, unsigned __int8 ad);
		bool check();
		unsigned __int8 lineNo = 0;

		stSndStt ar[ARSIZE_CLSMPCH];
		unsigned __int8 voeg(stSndStt s, unsigned __int8 no) { ar[no] = s; return no; }
		unsigned __int8 avAr[ARSIZE_CLSMPCH];
		unsigned __int8 lineCnt = mainThreadCls::set_ClsMpCh(avAr);
		struct lAS {
			unsigned int cnt;
			unsigned __int8 no;
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
	map<unsigned __int8, trLisHomeCls*> ses;
	shared_mutex sMutSes;
	shared_mutex sMutAdr;
	unsigned __int8 adress[100];
	strCv cvAccFull{ false };
	mutex timeMut;
	char radBuf[332]{ 's', 't', 'a', 'r', 't', ' ', '\"', 'C', ':', '\\', 'P', 'r', 'o', 'g', 'r', 'a', 'm', ' ', 'F', 'i', 'l', 'e', 's', ' ', '(', 'x', '8', '6', ')', '\\', 'G', 'o', 'o', 'g', 'l', 'e', '\\', 'C', 'h', 'r', 'o', 'm', 'e', '\\', 'A', 'p', 'p', 'l', 'i', 'c', 'a', 't', 'i', 'o', 'n', '\"', ' ', '\"', 'c', 'h', 'r', 'o', 'm', 'e', '.', 'e', 'x', 'e', '\"', ' ', '\"' };
};

extern mainThreadCls* threadCls;



#pragma once
#include "Serverintnetwork.h"
#include "threadCls.h"
#include "strucwebuser2.h"
#define SENDLEN_INT 100000
#define GETLEN_INT 1024

class clsNSite;
extern clswbusr2& p_wUsr;
extern clsNSite* p_nSite;
extern mutex ffMut;

class clsNSite {
public:
	clsNSite();
	void main(SOCKET& s);
	atomic<bool>chckAd = false;
	void checkAdr(unsigned __int8 min);
	class func {
	public:
		void proc();
		SOCKET sluisSock;
	private:
		friend class clsNSite;
		char buf[532]; unsigned __int16 bufLen;
		memFileObj fileObj;
		unsigned __int8 getLsActieF(char* nGet, int nLen);
		void voegC(char x);
		void voegS(char* x, unsigned long l);
		void voegSH(char* x, unsigned long l);
		void voegCode(unsigned int x);
		void voegFlag(unsigned __int8 x, unsigned int b);
		bool breakwebchar1(char c);
		bool breakwebchar2(char c);
		bool logWId;
		void stwzF(char* nGet, int nLen);
		void stwzdF(char* nGet, int nLen);
		bool stwLdF(char* nGet, int nLen);
		void stwLdwzF(unsigned __int8 type, unsigned __int8 ldNo, char* nGet, int nLen);
		void ledPlFVF(unsigned __int8 n);
		void ledPlFVF2(void* var, unsigned __int8 m);
		char* url; int urlLen; unsigned __int8 imgBl;
		atomic<bool> del; unsigned __int8 getPost;
		mainThreadCls::strMpCh mpCh; bool outFF;
		condition_variable cvMpCh; SOCKET* sock; char get[GETLEN_INT]; char* ls; __int8 getNo; __int8 lsNo; int len; int lsLen;
		void sendP() {
			mainThreadCls::strSndV& s = mpCh.p; do { if (!del.load() && NetworkServices::sendMessage(*sock, s.pack, s.len) == SOCKET_ERROR) closeF(); __int8 U = s.lsNo; if (U == -101) delete[SENDLEN_INT] s.pack; else p_nSite->getStr.ret(s.lsNo); } while (!mpCh.end()); cvMpCh.notify_one();
		} void voegNm(); void voegNoD(); void voegTmp(); void voegLdPl(); bool stwzStream(bool type, char* nGet, int nLen); void voegStream(); void streamUp(); void voegNo(); void voegUp(); void voegNo0(); bool voegNo02(bool kom); void voegAN(bool x); void voegAD(unsigned __int8 x); void voegNo1(unsigned int N); void voegNoD1(unsigned int N);
		char* urlDecode(char* str);
		char* urlEncode(char* str);
		unsigned int logId;
		void send() { /* ffMut.lock(); for (int t = 0; t < lsLen; t++) cout << ls[t]; cout << '\n'; ffMut.unlock();*/ if (!mpCh.begin(mainThreadCls::strSndV{ ls, lsLen, NULL, lsNo })) return;
		threadBufCls::recStruct{ p_nSite->threadMut, [](void* p, void* AA) { ((func*)p)->sendP(); } }.start(this, NULL);
		}
		bool closeF(); void closeF2(); void getLsPrc(); void voeg(char* x, unsigned int y);
	} fncCls[100];
private:
	
	void start(__int8 n);
	mutex mutChkAd; bool blArdChk[2];


	unsigned __int8 cnt = 100; 
	__int8 cntAr[100]; 
	mutex threadMut;
	mutex cntMut; 
	
	unsigned int cntVal; 
	
	unsigned int cntSet = cntVal = 0;
	map<unsigned int, SOCKET> cntMp;
	unsigned __int8 lineNo = 0;
	unsigned __int8 lineCnt = 0;
	SOCKET ar[ARSIZE_CLSMPCH];
	unsigned __int8 voeg(SOCKET s, unsigned __int8 no) { ar[no] = s; return no; }
	unsigned __int8* avAr{ [] {unsigned __int8* PP{ new unsigned __int8[ARSIZE_CLSMPCH] }; for (__int8 t = 0, i = ARSIZE_CLSMPCH - 1; t < ARSIZE_CLSMPCH; t++) PP[t] = i--; return PP; }() };
	struct lAS {
		unsigned int cnt;
		unsigned __int8 no;
	};

	lAS lineAr[ARSIZE_CLSMPCH];

	

	ServerintNetwork* network = new ServerintNetwork;
	
	mainThreadCls::strStrCnt getStr;
	 friend class func; void voegAdr(func* f); unsigned __int8* mpChkAdAr{ [] { unsigned __int8* x = new unsigned __int8[100]; for (int t = 0; t < 100; t++) x[t] = 0; return x; }() };
};


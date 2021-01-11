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
	void checkAdr(uint8_t min);
	class func {
	public:
		void proc();
		SOCKET sluisSock;
	private:
		friend class clsNSite;
		char buf[532]; uint16_t bufLen;
		memFileObj fileObj;
		uint8_t getLsActieF(char* nGet, int nLen);
		void voegC(char x);
		void voegS(char* x, unsigned long l);
		void voegSH(char* x, unsigned long l);
		void voegCode(unsigned int x);
		void voegFlag(uint8_t x, unsigned int b);
		bool breakwebchar1(char c);
		bool breakwebchar2(char c);
		bool logWId;
		void stwzF(char* nGet, int nLen);
		void stwzdF(char* nGet, int nLen);
		bool stwLdF(char* nGet, int nLen);
		void stwLdwzF(uint8_t type, uint8_t ldNo, char* nGet, int nLen);
		void ledPlFVF(uint8_t n);
		void ledPlFVF2(void* var, uint8_t m);
		char* url; int urlLen; uint8_t imgBl;
		atomic<bool> del; uint8_t getPost;
		mainThreadCls::strMpCh mpCh; bool outFF;
		condition_variable cvMpCh; SOCKET* sock; char get[GETLEN_INT]; char* ls; int8_t getNo; int8_t lsNo; int len; int lsLen;
		void sendP() {
			mainThreadCls::strSndV& s = mpCh.p; do { if (!del.load() && _SOCK_ENUM_COMP(NetworkServices::sendMessage(*sock, s.pack, s.len), SOCKET_ERROR)) closeF(); int8_t U = s.lsNo; if (U == -101) delete[] s.pack; else p_nSite->getStr.ret(s.lsNo); } while (!mpCh.end()); cvMpCh.notify_one();
		} void voegNm(); void voegNoD(); void voegTmp(); void voegLdPl(); bool stwzStream(bool type, char* nGet, int nLen); void voegStream(); void streamUp(); void voegNo(); void voegUp(); void voegNo0(); bool voegNo02(bool kom); void voegAN(bool x); void voegAD(uint8_t x); void voegNo1(unsigned int N); void voegNoD1(unsigned int N);
		char* urlDecode(char* str);
		char* urlEncode(char* str);
		unsigned int logId;
		void send() { /* ffMut.lock(); for (int t = 0; t < lsLen; t++) cout << ls[t]; cout << '\n'; ffMut.unlock();*/ if (!mpCh.begin(mainThreadCls::strSndV{ ls, lsLen, NULL, lsNo })) return;
		threadBufCls::recStruct{ p_nSite->threadMut, [](void* p, void* AA) { ((func*)p)->sendP(); } }.start(this, NULL);
		}
		bool closeF(); void closeF2(); void getLsPrc(); void voeg(const char* x, unsigned int y);
	} fncCls[100];
private:
	
	void start(int8_t n);
	mutex mutChkAd; bool blArdChk[2];


	uint8_t cnt = 100; 
	int8_t cntAr[100]; 
	mutex threadMut;
	mutex cntMut; 
	
	unsigned int cntVal; 
	
	unsigned int cntSet = cntVal = 0;
	map<unsigned int, SOCKET> cntMp;
	uint8_t lineNo = 0;
	uint8_t lineCnt = 0;
	SOCKET ar[ARSIZE_CLSMPCH];
	uint8_t voeg(SOCKET s, uint8_t no) { ar[no] = s; return no; }
	uint8_t* avAr{ [] {uint8_t* PP{ new uint8_t[ARSIZE_CLSMPCH] }; for (int8_t t = 0, i = ARSIZE_CLSMPCH - 1; t < ARSIZE_CLSMPCH; t++) PP[t] = i--; return PP; }() };
	struct lAS {
		unsigned int cnt;
		uint8_t no;
	};

	lAS lineAr[ARSIZE_CLSMPCH];

	

	ServerintNetwork* network = new ServerintNetwork;
	
	mainThreadCls::strStrCnt getStr;
	 friend class func; void voegAdr(func* f); uint8_t* mpChkAdAr{ [] { uint8_t* x = new uint8_t[100]; for (int t = 0; t < 100; t++) x[t] = 0; return x; }() };
};


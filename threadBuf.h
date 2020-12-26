#pragma once
#include <IOstream>
#include <condition_variable>
#include <mutex>
#include <thread>
#define THRDBFCLS_CNT 25


using namespace std;
class threadBufCls;
extern threadBufCls& p_TrBC;

class threadBufCls {
public:
	void open();
	struct recStruct {
		mutex& mutAanv;
		void(*pF)(void*, void*);
		void start(void* pnt, void* pnt2);
	};
private:
	friend struct recStruct;
	mutex allMut;
	unsigned __int8 avCnt[THRDBFCLS_CNT];
	void raise(unsigned __int8 n) { allMut.lock(), avCnt[n]++, allMut.unlock(); }
	unsigned int avNow = 0;
	struct tObjS {
		struct vStrS {
			void(*pF)(void*, void*);
			void* pA;
			void* pA2;
			void f() { pF(pA, pA2); }
		};
		unsigned __int8 no;
		vStrS vStr[21];
		condition_variable cv;
		condition_variable cvU;
		mutex mut;
		mutex bMut;
		bool ready = false;
		void voeg(tObjS::vStrS& s);
		void func(unsigned __int8 n);
	}tObj[THRDBFCLS_CNT];
	friend struct tObjs;

	void start(tObjS::vStrS s);
};

#pragma once
#include <stdint.h>
#include <iostream>
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
	uint8_t avCnt[THRDBFCLS_CNT];
	void raise(uint8_t n) { allMut.lock(), avCnt[n]++, allMut.unlock(); }
	unsigned int avNow = 0;
	struct tObjS {
		struct vStrS {
			void(*pF)(void*, void*);
			void* pA;
			void* pA2;
			void f() { pF(pA, pA2); }
		};
		uint8_t no;
		vStrS vStr[21];
		condition_variable cv;
		condition_variable cvU;
		mutex mut;
		mutex bMut;
		bool ready = false;
		void voeg(tObjS::vStrS& s);
		void func(uint8_t n);
	}tObj[THRDBFCLS_CNT];
	friend struct tObjs;

	void start(tObjS::vStrS s);
};

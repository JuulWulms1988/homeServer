
#include <stdint.h>

void* bootPtrAlg;

#include <iostream>

#include "nSite.h"
#include "ThreadCls.h"
#include "PiScreen.h"
#include "Radio.h"

#include "clstijd.h"
#include "udpImplementation/Implementation.hpp"

#ifdef _WIN32
#include "../stdafx.h"

static inline void startKillF() {
#ifdef _WIN32
	for (char t = 0, *y[4/*5*/]{ /*"explorer.exe", */"start.exe", "chrome.exe", "cmd.exe", "vlc.exe" }; t < 4; t++)
		mainThreadCls::killProc(y[t]);
#endif
}

static inline BOOL ctrl_handler(DWORD event)
{
	if (event == CTRL_CLOSE_EVENT || event == CTRL_LOGOFF_EVENT || event == CTRL_SHUTDOWN_EVENT) {
		extCls::end();
		return TRUE;
	}
	return FALSE;
}

static inline void setCloseHandle() {
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)(ctrl_handler), TRUE);
}

#endif

#ifndef _WIN32
#include "stdio.h"
static inline void startKillF() {}
static inline void setCloseHandle() {

}

#endif


memFileCls* fileData;
mainThreadCls* threadCls;

char lsUsrCin[512]; 
uint8_t LEDPL_CNT = 0;


int main()
{
	{ char p[]{ 'D', 'a', 't', 'a', '\0' }; fileData = new memFileCls(p); }
	startKillF();
	stuurbericht();
	p_clstijd->tijdupdate();
	bootPtrAlg = new mainThreadCls::deBootStr;
	new mainThreadCls;
	radioS.open();
	piScreenC.start();
	
	setCloseHandle();

	
	thread([] { new clsNSite; }).detach();
	{
		strCv cv{ false };
		thread([](strCv* cv) {
			{ unique_lock<mutex>lk(cv->mut); cv->cv.wait(lk, [&] { return cv->ready; }), cv->ready = false, cv->cv.notify_all(); }
			telnetS.serv.update();
		}, &cv).detach();
		
		((mainThreadCls::deBootStr*)bootPtrAlg)->mainF();

		cv.mut.lock(); cv.ready = true; cv.mut.unlock();
		cv.cv.notify_all();
		unique_lock<mutex>lk(cv.mut);
		cv.cv.wait(lk, [&] { return !cv.ready; });
		
	}

	thread([] { udpImplementation::lisBroadcast(); }).detach();

	while (true) cin >> lsUsrCin;
}


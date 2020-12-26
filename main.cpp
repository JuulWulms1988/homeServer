// main.cpp : Defines the entry point for the console application.
//
// may need #include "stdafx.h" in visual studio
void* bootPtrAlg;
// #include "ClientGame.h"
#include <iostream>
// used for multi-threading
#include "nSite.h"
#include "ThreadCls.h"
#include "PiScreen.h"
#include "Radio.h"
#include "stdafx.h"
#include "clstijd.h"
#include "udpImplementation\\Implementation.hpp"
memFileCls* fileData;
mainThreadCls* threadCls;

char lsUsrCin[512]; 
unsigned __int8 LEDPL_CNT = 0;


BOOL ctrl_handler(DWORD event)
{
	if (event == CTRL_CLOSE_EVENT || event == CTRL_LOGOFF_EVENT || event == CTRL_SHUTDOWN_EVENT) {
		extCls::end();
		return TRUE;
	}
	return FALSE;
}


int main()
{
	fileData = new memFileCls("Data");
	for (char t = 0, *y[4/*5*/]{ /*"explorer.exe", */"start.exe", "chrome.exe", "cmd.exe", "vlc.exe" }; t < 4; t++)
		mainThreadCls::killProc(y[t]);
	stuurbericht();
	p_clstijd->tijdupdate();
	bootPtrAlg = new mainThreadCls::deBootStr;
	new mainThreadCls;
	radioS.open();
	piScreenC.start();
	
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)(ctrl_handler), TRUE);

	
	thread([] { new clsNSite; }).detach();
	{
		strCv cv{ false };
		thread([](strCv* cv) {
			cv->cv.wait(unique_lock<mutex>(cv->mut), [&] { return cv->ready; }), cv->ready = false, cv->cv.notify_all();
			telnetS.serv.update();
		}, &cv).detach();
		
		((mainThreadCls::deBootStr*)bootPtrAlg)->mainF();

		unique_lock<mutex>(cv.mut), cv.ready = true;
		cv.cv.notify_all();
		cv.cv.wait(unique_lock<mutex>(cv.mut), [&] { return !cv.ready; });
	}

	thread([] { udpImplementation::lisBroadcast(); }).detach();

	while (true) cin >> lsUsrCin;
}


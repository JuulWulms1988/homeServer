#include <stdint.h>
#include "ledPlaf.h"
#include "Radio.h"

static inline void delHibF() {
#ifdef _WIN32
	char p[]{ 'd', 'e', 'l', ' ', 'h', 'i', 'b', 'e', 'r', '\\', 'h', 'i', 'b', 'e', 'r', '.', 't', 'x', 't', ' ', '/', 'Q', ' ', '/', 'F', '\0' };
#endif

#ifndef _WIN32
	char p[]{ 'r', 'm', ' ', '/', 'h', 'o', 'm', 'e', '/', 'p', 'i', '/', 's', 'h', 'a', 'r', 'e', '/', 'h', 'i', 'b', 'e', 'r', '/', 'h', 'i', 'b', 'e', 'r', '.', 't', 'x', 't', '\0' };
#endif
	system(p);
}

static inline void openHibF(ifstream* hF, ofstream* hF2) {
#ifdef _WIN32
	char p[]{ 'h', 'i', 'b', 'e', 'r', '/', 'h', 'i', 'b', 'e', 'r', '.', 't', 'x', 't', '\0' };
#endif

#ifndef _WIN32

	char p[]{ '/', 'h', 'o', 'm', 'e', '/', 'p', 'i', '/', 's', 'h', 'a', 'r', 'e', '/', 'h', 'i', 'b', 'e', 'r', '/', 'h', 'i', 'b', 'e', 'r', '.', 't', 'x', 't', '\0' };
#endif
	
	if (hF) hF->open(p);
	else hF2->open(p);
}

#ifndef _WIN32

static inline void mountHib() {
	char p[]{ '/', 'h', 'o', 'm', 'e', '/', 'p', 'i', '/', 'S', 'e', 'r', 'v', 'e', 'r', '/', 'm', 'H', 'i', 'b', '.', 's', 'h', '\0' };
	system(p);
}

static inline void umountHib() {
	char p[]{ '/', 'h', 'o', 'm', 'e', '/', 'p', 'i', '/', 'S', 'e', 'r', 'v', 'e', 'r', '/', 'u', 'H', 'i', 'b', '.', 's', 'h', '\0' };
	system(p);
}

#endif 


void extCls::begin() {
	do {
#ifndef WIN32_
		mountHib();
#endif

		ifstream hF; openHibF(&hF, NULL); if (!hF.is_open()) {
#ifndef WIN32_
			umountHib();
#endif
			
			return;
		}
		hF.seekg(-2, ios::end);
		{
			bool flag = false;
			for (uint8_t t = 0; t < 2; t++) if (hF.get() != 'z') { flag = true; break; }
			if (flag) { hF.close(); break; }
		}
		hF.seekg(0, ios::beg);
		char ls[512]; unsigned int l = 0;
		bool flag = false;
		{
			atomic<bool>* p = threadCls->statVar;
			for (unsigned int t = 0; t < 900; t++, l = 0)
				if (hF.eof()) { flag = true; break; }
				else p[t] = (*read(ls, hF) - '0') * true;
				if (flag) { hF.close(); break; }
		}
		{
			atomic<int>* p = threadCls->statDimVar;
			for (unsigned int t = 0; t < 900; t++, l = 0)
				if (hF.eof()) { flag = true; break; }
				else p[t] = strbasprc::cvintcharStr(read(ls, hF));
				if (flag || hF.eof()) { hF.close(); break; }
		} do {
			mainThreadCls::clsLedPl::clsLedPlObj* p;
			if ((*read(ls, hF) == 'z' && ls[1] == 'z') || !(p = p_ledPl.toObjF(strbasprc::cvintcharStr(ls))) || hF.eof() || strbasprc::cvintcharStr(read(ls, hF)) != p->stripCnt || hF.eof()) break;
			{
				unsigned long in = strbasprc::cvintcharStr(read(ls, hF));
				for (uint8_t t = 0; (hF.eof() && !(flag = true)) || t < 5; t++, in = strbasprc::cvintcharStr(read(ls, hF))) switch (t) {
				case 0: p->upN = in; break;
				case 1: p->upM = in; break;
				case 2: p->upD = in; break;
				case 3: p->upU = in; break;
				case 4: p->upMi = in; break;
				} if (flag) break;
				p->upS = in;
			} if (!p->stripCnt) continue; bool* gezet = p->gezet; for (uint8_t t = 0, m = p->stripCnt; t < m; t++) gezet[t] = false;
			for (uint8_t tt = 0, mm = p->stripCnt; (flag && !flag) || (tt < mm && (gezet[tt] = true)); gezet[tt++] = false)
			{
				p->var[tt].parChld = strbasprc::cvintcharStr(read(ls, hF));
				for (uint8_t t = 0, m = p->stripCnt; t < m; t++) p->var[tt].parChldAr[t] = strbasprc::cvintcharStr(read(ls, hF)) * true;
				for (uint8_t t = 0, m = LEDPL_VARAANT2 + 40; ((tt || t) && hF.eof() && !(flag = true)) || (t == LEDPL_VARAANT && (t = 20)) || (t == LEDPL_VARAANT1 + 20 && (t = 40)) || t < m; t++, l = 0)
					p->setVal(t, strbasprc::cvintcharStr(read(ls, hF)), 1);
			}
			if (flag) break;
		} while (true);
		for (uint8_t t = 0; t < 4; t++) piSWrite(t, read(ls, hF));
		piSPlay(1 + (*read(ls, hF) - '0'));
		unique_lock<shared_mutex>(radioS.varMut), radioS.chan = (*read(ls, hF) - '0') * 100 + (ls[1] - '0') * 10 + (ls[2] - '0');
		hF.close();
	} while (false); 
	delHibF();
#ifndef WIN32_
	umountHib();
#endif
}



void extCls::end() {
#ifndef WIN32_
	mountHib();
#endif
	do {
		ifstream hF; openHibF(&hF, NULL); if (!hF.is_open()) break;
		hF.close();
		delHibF();
	} while (false);
	ofstream hF;
	openHibF(NULL, &hF);
	if (!hF.is_open()) {
#ifndef WIN32_
		umountHib();
#endif

		return;
	}
	{
		char w[3] = { 'g', '\n', '\0' };
		atomic<bool>* p = threadCls->statVar;
		for (unsigned int t = 0; t < 900; t++) *w = (p[t].load() * 1) + '0', hF << w;
	}
	{
		char w[4]; uint8_t l = 0;
		atomic<int>* p = threadCls->statDimVar;
		for (unsigned int t = 0; t < 900; t++, l = 0) w[(l += strbasprc::cvcharlngth(60, p[t].load(), w))++] = '\n', w[l] = '\0', hF << w;
	}
	for (map<uint8_t, mainThreadCls::clsLedPl::clsLedPlObj&>::iterator t = p_ledPl.mpObj.begin(), m = p_ledPl.mpObj.end(); t != m; t++) {
		mainThreadCls::clsLedPl::clsLedPlObj& p = t->second;
		char w[512]; int l = 0; w[(l += strbasprc::cvcharlngth(60, p.adr, w))++] = '\n', w[l] = '\0', l = 0, hF << w;
		w[(l += strbasprc::cvcharlngth(60, p.stripCnt, w))++] = '\n', w[l] = '\0', l = 0, hF << w;
		w[(l += strbasprc::cvcharlngth(60, p.upN.load(), w))++] = '\n', w[l] = '\0', l = 0, hF << w;
		w[(l += strbasprc::cvcharlngth(60, p.upM.load(), w))++] = '\n', w[l] = '\0', l = 0, hF << w;
		w[(l += strbasprc::cvcharlngth(60, p.upD.load(), w))++] = '\n', w[l] = '\0', l = 0, hF << w;
		w[(l += strbasprc::cvcharlngth(60, p.upU.load(), w))++] = '\n', w[l] = '\0', l = 0, hF << w;
		w[(l += strbasprc::cvcharlngth(60, p.upMi.load(), w))++] = '\n', w[l] = '\0', l = 0, hF << w;
		w[(l += strbasprc::cvcharlngth(60, p.upS.load(), w))++] = '\n', w[l] = '\0', l = 0, hF << w;
		p.varMut.lock_shared();
		for (uint8_t tt = 0, mm = p.stripCnt; tt < mm; tt++)
		{
			w[(l += strbasprc::cvcharlngth(60, p.var[tt].parChld, w))++] = '\n', w[l] = '\0', l = 0, hF << w;
			for (uint8_t t = 0, m = p.stripCnt; t < m; t++) w[0] = [&] { if (p.var[tt].parChldAr[t]) return '1'; return '0'; }(), w[1] = '\n', w[2] = '\0', hF << w;
			for (uint8_t t = 0, m = LEDPL_VARAANT2 + 40; (t == LEDPL_VARAANT && (t = 20)) || (t == LEDPL_VARAANT1 + 20 && (t = 40)) || t < m; t++, l = 0)
				w[(l += strbasprc::cvcharlngth(60, p.var[tt].val(t), w))++] = '\n', w[l] = '\0', hF << w;
		}
		p.varMut.unlock_shared();
	}
	hF << 'z' << 'z' << '\n';
	{
		void * p = NULL; char w[512]; int l = 0;
		for (uint8_t t = 0; t < 5 && ((p = piSRead(t)) || !p); t++, l = 0)
			switch (t) {
			case 0: *w = strbasprc::cvintcharchar((l = (uint64_t)(p)) / 60), w[1] = strbasprc::cvintcharchar(l % 60); w[2] = '\n'; w[3] = '\0'; hF << w; break;
			case 1: if (p) *w = '1'; else *w = '0'; w[1] = '\n'; w[2] = '\0'; hF << w; break;
			case 2: *w = strbasprc::cvintcharchar((l = (uint64_t)(p)) / 60), w[1] = strbasprc::cvintcharchar(l % 60); w[2] = '\n'; w[3] = '\0'; hF << w; break;
			case 3: { char* P = w; char* T = (char*)p; while (*T) *(P++) = *(T++); *(P++) = '\n'; *(P++) = '\0'; hF << w; break; }
			}
	}
	hF << (char)((piSPlay(0) * 1) + '0') << '\n';
	{   
		uint8_t C; shared_lock<shared_mutex>(radioS.varMut), C = radioS.chan;
		hF << (char)(C / 100 + '0') << (char)((C / 10) % 10 + '0') << (char)(C % 10 + '0') << '\n';	
	}
	hF << 'z' << 'z';
	hF.close();
#ifndef WIN32_
	umountHib();
#endif
}
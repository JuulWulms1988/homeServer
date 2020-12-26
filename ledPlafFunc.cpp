#include "ledPlaf.h"

bool mainThreadCls::clsLedPl::clsLedPlObj::ledPlFunc(strSndV s) {
	char* str = s.pack;
	if (!str) flagPsMsPr();
	else if (s.len == 1 && (*str == 'E' || *str == 'R')) { 
		s.ret(), empPsMsPr(); if (*str == 'R') reqFunc();
	}
	else if (*str == 'R') {
		empPsMsPr(); 
		str++; int L = s.len - 1, Loc; char bufL = '@';
		for (unsigned __int8 t = 0; t < 6; t++) {
			bufL = str[L], str[L] = '\0';
			if ((Loc = strbasprc::indChar('\\', str)) != -1) str[Loc] = '\0', str[L] = bufL, bufL = '@';
			unsigned long uit = strbasprc::cvintcharStr(str); bool flag = false; switch (t) {
			case 0: if (uit != upM) flag = true; break;
			case 1: if (uit != upD) flag = true; break;
			case 2: if (uit != upU) flag = true; break;
			case 3: if (uit != upMi) flag = true; break;
			case 4: if (uit != upS) flag = true; break;
			case 5: if (uit != upN) flag = true; else { s.ret(); char*& ls = sndS.pack; *ls = '#', ls[1] = '+', sndS.len = 2, psMsPr(); return false; } break;
			} if (flag) break; str += ++Loc; L -= Loc;
		} s.ret(), reqFunc();
	}
	else if (*str == 'L' && str[1] == 'P') {
		for (unsigned __int8 t = 1, m = (s.len -= 1) - 2; t < m || (str[m++] = '\n' && !(str[m] = '+')); t++) str[t] = str[t + 3]; *str = '&', psMsPr2(s);
	}
	else if (*str == 'P') {
		char* ls = sndS.pack;
		*ls = '&'; char* rd; {
			mutPoint.lock();
			unsigned int sk = strbasprc::cvintcharStr(str + 1);
			if (mplineCnt && mplineAr[mplineNo].cnt == sk) rd = mpar[mplineAr[mplineNo].no], mpavAr[--mplineCnt] = mplineAr[mplineNo].no, mplineNo = (mplineNo + 1) % ARSIZE_CLSMPCH;
			else rd = mpPoint.find(sk)->second, mpPoint.erase(sk);
			mutPoint.unlock();
			}
		//= (char*)strbasprc::cvintcharStr(str + 1); rd += strbasprc::cvintcharStr(str + strbasprc::charPLen(str) + 1);
		unsigned int tel = 1, Next = 0; char Now; unsigned __int8 Bron, pC; __int8 zetAant; for (unsigned __int8 t = 0; t < stripCnt; t++) gezet[t] = false;
		for (char thisC = *rd;
			thisC != '\r' && thisC != '\n'; thisC = rd[tel++]) { ls[tel] = thisC; 
		if (!Next && tel < 4)
			switch (tel) {
			case 1: gezet[Bron = strbasprc::cvintcharint(thisC)] = true, zetAant = 1; break;
			case 2: if ((Now = thisC) != 'S') { for (unsigned __int8 t = 0; t < Bron; t++) if (var[Bron].parChldAr[t]) { Bron = t; break; } }
					else varMut.lock(); remChld(Bron); // OPLETTEN MET MUTEX!
					break;
			case 3: if (Now == 'S') *ls = '$', pC = strbasprc::cvintcharint(thisC), Next = 5; else if ((Next = 3) && Bron < stripCnt - 1) for (unsigned __int8 t = Bron + 1; t < stripCnt; t++) if (var[Bron].parChldAr[t]) gezet[t] = true, pC = zetAant++; zetAant *= -1; break;
			}
		else if (Next)
			if (tel != Next) continue;
			else if (pC != zetAant - 1) {
				bool flag = true;
				if (zetAant < 0) zetAant *= -1, flag = false;
				if (flag || (pC != zetAant - 1 && (flag = true))) {
					char X = strbasprc::cvintcharint(thisC); gezet[X] = true, Next += 2; if (Now == 'S') { remChld(X); if (pC != zetAant++) continue; }
					else { zetAant++; continue; }
				}
				for (unsigned __int8 t = 0, m = LEDPL_VARAANT2 + 40; (t == LEDPL_VARAANT && (t = 20)) || (t == LEDPL_VARAANT1 + 20 && (t = 40)) || t < m; t++)
					setVal(t, 0, zetAant);
				for (unsigned __int8 tt, tt2 = tt = 0; tt2 < zetAant; tt++)
					if (!gezet[tt]) continue; else tt2++, var[tt].parChld = zetAant;
				for (unsigned __int8 t = 0; t < stripCnt; t++)
					for (unsigned __int8 tt, tt2 = tt = 0; tt2 < zetAant; tt++)
						if (!gezet[tt]) continue; else tt2++, var[tt].parChldAr[t] = gezet[t];
				if (!flag) tel--;
			}
			else {
				unsigned __int8 loc = 0; char Buf;
				while ((Buf = rd[tel + loc++]) != '_' && Buf != '\r' && Buf != '\n'); rd[tel + loc - 1] = '\0';
				switch (Now) {
				case 'S':
					unsigned __int8 vr = strbasprc::cvintcharint(thisC); setVal(vr, strbasprc::cvintcharStr(rd + tel), zetAant); break;
				} if (Buf == '_') Next = tel + loc + 1; else Next = 0; rd[tel + loc - 1] = Buf;
			}
		} if (Now == 'S') varMut.unlock(); ls[tel++] = '\n';
		ls[(sndS.len = tel)++] = '+';
		s.ret();
		psMsPr(); 
		return true;
	}
	else if (*str == 'V') varFunc(str, s.len), s.ret();
	else if (*str == 'D' || *str == 'A') atDetFunc(str, s.len), s.ret();
	return false;	
}

void mainThreadCls::clsLedPl::clsLedPlObj::reqFunc() {
	char*& ls = sndS.pack; int& lsLen = sndS.len = 0;
	bool eerst = false;
	for (unsigned __int8 t = 0; t < stripCnt; t++) gezet[t] = false;
	for (unsigned __int8 tt = 0; tt < stripCnt; tt++) if (gezet[tt]) continue; 
	else {
		bool zet = false; varStr& p = var[tt]; unsigned __int8 zet0 = p.parChld - 1;
		unsigned int w; 
		for (unsigned __int8 t = 0, m = LEDPL_VARAANT2 + 40; (t == LEDPL_VARAANT && (t = 20)) || (t == LEDPL_VARAANT1 + 20 && (t = 40)) || t < m; t++) 
			if (!(w = p.val(t))) continue;
			else {
				if (!zet) {
					zet = true; if (!eerst) *ls = '#', eerst = true; else *ls = '$'; ls[1] = strbasprc::cvintcharchar(tt), ls[2] = 'S', ls[3] = strbasprc::cvintcharchar(zet0), lsLen = 4;
					if (tt < stripCnt - 1) lsLen += p.voegChld(tt + 1, stripCnt, ls + lsLen, gezet);
				}
				ls[lsLen++] = '_', ls[lsLen++] = strbasprc::cvintcharchar(t), lsLen += strbasprc::cvcharlngth(60, w, ls + lsLen);
			}
			if (zet) ls[lsLen++] = '\n', ls[(sndS.len = lsLen)++] = '+', psMsPr();
			else {
				zet = true; if (!eerst) *ls = '#', eerst = true; else *ls = '$'; ls[1] = strbasprc::cvintcharchar(tt), ls[2] = 'S', ls[3] = '0', ls[4] = '\n', ls[5] = '+'; lsLen = 6; psMsPr();
			}
	}
	if (!eerst) *ls = '#', ls[1] = '+', lsLen = 2, psMsPr();
}

unsigned int mainThreadCls::clsLedPl::clsLedPlObj::varStr::val(unsigned __int8 x) {
	//cout << "lees: " << (int)x << "\n";
	switch (x) {
	case 0: return helder; case 1: return rgbPauze; case 2: return negDlay * 1; case 3: return gamDlay;
	case 4: return negGamDlay * 1; case 5: return gamPer; case 6: return gamClr;
	case 7: return gamVal; case 8: return gamIVal; case 9: return gamIHel;
	case 10: return helDlay; case 11: return negHelCur * 1; case 12: return gamPauze;
	case 13: return helAmp; case 20: return dlay; case 21: return gamInterval;
	case 22: return helPer; case 23: return per; case 40: return randVar;
	}
}

void mainThreadCls::clsLedPl::clsLedPlObj::setVal(unsigned __int8 n, unsigned long v, unsigned __int8 c) {
	for (unsigned __int8 t, t2 = t = 0; t2 < c; t++) {
		if (!gezet[t]) continue; t2++;
		switch (n) {
		case 0: var[t].helder = v; break; case 1: var[t].rgbPauze = v; break; case 2: var[t].negDlay = v * true; break;
		case 3: var[t].gamDlay = v; break; case 4: var[t].negGamDlay = v * true; break; case 5: var[t].gamPer = v; break;
		case 6: var[t].gamClr = v; break; case 7: var[t].gamVal = v; break; case 8: var[t].gamIVal = v; break;
		case 9: var[t].gamIHel = v; break;	case 10: var[t].helDlay = v; break; case 11: var[t].negHelCur = v * true; break;
		case 12: var[t].gamPauze = v; break; case 13: var[t].helAmp = v; break; case 20: var[t].dlay = v; break;
		case 21: var[t].gamInterval = v; break; case 22: var[t].helPer = v; break; case 23: var[t].per = v; break;
		case 40: var[t].randVar = v; break;
		}
	}
}

void mainThreadCls::clsLedPl::clsLedPlObj::varFunc(char* xLs, int xLen) {
	char*& yLs = sndS.pack; int& yLen = sndS.len;
	{
		unsigned __int8 x = (xLs[1] - '0') * 10 + (xLs[2] - '0'), y = (xLs[3] - '0') * 10 + (xLs[4] - '0');
		yLs[1] = strbasprc::cvintcharchar(x), yLs[2] = 'V';
		yLen = 3 + strbasprc::cvcharlngth(60, y, yLs + 3);
		if (varSFunc(x, y, strbasprc::cvintcharStr(xLs + 6))) *yLs = '$'; else *yLs = '&';
	}
	
	yLs[1] = strbasprc::cvintcharchar((xLs[1] - '0') * 10 + (xLs[2] - '0')), yLs[2] = 'V';
	yLen = 3 + strbasprc::cvcharlngth(60, (xLs[3] - '0') * 10 + (xLs[4] - '0'), yLs + 3);
	yLs[yLen++] = '_'; for (int t = 6; t < xLen; t++) yLs[yLen++] = xLs[t]; yLs[yLen++] = '\n', yLs[yLen++] = '+';
	psMsPr();
}


bool mainThreadCls::clsLedPl::clsLedPlObj::varSFunc(unsigned __int8 noStr, unsigned __int8 noVal, unsigned long wVal) {
	bool uit; if (noVal > 19) uit = true; else uit = false;
	varMut.lock();
	varStr& p = var[noStr];
	{
		bool* ar = p.parChldAr;
		for (unsigned __int8 t = 0; t < stripCnt; t++) gezet[t] = ar[t];
	} unsigned __int8 max = p.parChld;
	setVal(noVal, wVal, max);
	switch (noVal) {
	case 5: //gamPer -> per
		 if (p.per >= wVal) break; 
		 unsigned long jaja;
		 if (wVal && wVal < 100) jaja = 100; else jaja = wVal;
		 setVal(23, jaja, max), uit = true;
		 break;
	case 23: //per -> gamper
		if (p.gamPer) {
			if (p.gamPer <= wVal) break;
			setVal(5, wVal, max);
		} break;
}
	varMut.unlock();
	return uit;
}
/*
unsigned long mainThreadCls::clsLedPl::clsLedPlObj::varSFuncR(unsigned long waarde, unsigned __int8 meer) {
	auto prF = [](unsigned __int8 x, unsigned long& w) { if (x < 8) w = (x / 2) * 25 + x % 2 * 13; else if (x < 37) w = (x - 7) * 100; else if (x < 41) w = (x - 33) * 750; else w = (x - 40) * 6000; };
	unsigned long uit, uit2 = 0;
	for (unsigned __int8 t = 1; t < 52; t++) {
		uit = uit2, prF(t, uit2);
		if (uit2 > waarde)
		{
			if (meer && (meer == 2 || uit != waarde)) uit = uit2;
			break;
		}
	} return uit;
}
*/
unsigned int mainThreadCls::clsExMes::strExec::getPointLed(char* x) {
	lock_guard<mutex>(pExMp->mutLdPlPoint);
	return p_ledPl.toObjF(strAd)->mpPointF(x);
}
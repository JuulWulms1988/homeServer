#include "nSite.h"

void clsNSite::func::getLsPrc() {
	//char urlBuf[10]; 
	static char urlInd[]{ 'i', 'n', 'd', '.', 'h', 't', 'm', '\0' }, urlInd2[]{ 'i', 'n', 'd', '2', '.', 'h', 't', 'm', '\0' }, urlLgF3[]{ 'l', 'g', 'F', '3', '.', 'h', 't', 'm', '\0' };
	{
		{
			int loc = strbasprc::indChar('\r', get), rek = strbasprc::indChar('\n', get);
			if (loc < 0 || (rek >= 0 && rek < loc)) loc = rek;
			rek = 0; int rek2; while ((rek2 = strbasprc::indChar(' ', get + rek)) != -1 && rek + rek2 < loc) rek += rek2 + 1;
			if (!rek) return;
			get[(len = rek) - 1] = '\r';
		}
		int nLen = imgBl = 0; char* nGet = get + 5; url = NULL; bool flag = false; 	int8_t log = 1;
		/*enum urlEnum { __ind, __ind2, __lgF3 };
		auto urlSet = [&](int X) {
			char* Y = url = urlBuf;
			switch (X) {
			case __lgF3: *Y++ = 'l'; *Y++ = 'g'; *Y++ = 'F'; *Y++ = '3'; break;
			case __ind:  *Y++ = 'i'; *Y++ = 'n'; *Y++ = 'd'; break;
			case __ind2:  *Y++ = 'i'; *Y++ = 'n'; *Y++ = 'd'; *Y++ = '2'; break;
			} *Y++ = '.'; *Y++ = 'h'; *Y++ = 't'; *Y++ = 'm'; *Y = '\0';
		};*/ 
		for (unsigned int t = 5; t < len; t++, nLen++) {
			char b = nGet[nLen];
			if (nLen > 30) url = NULL, nLen = -1, log = 1;
			else if (!(breakwebchar2(b) || (breakwebchar1(b) && (flag = true)))) continue;
			else nGet[nLen] = '\0', urlDecode(nGet);
			//ffMut.lock(), cout << nGet << '\n', ffMut.unlock();
			if (log >= 4) {
				switch (log) {
				case 4: 
					stwzF(nGet, nLen);
					break;
				case 5:
					stwzdF(nGet, nLen);
					break;
				case 6:
					if (!stwLdF(nGet, nLen)) url = NULL;
					break;
				case 7:
					if (!stwzStream(false, nGet, nLen)) url = NULL;
					break;
				case 8:
					if (!stwzStream(true, nGet, nLen)) url = NULL;
					break;
				} if (!url) log = 1; else log = 0;
			} else if (log == 2) {
				if (nLen > 4 && nGet[0] == 'u' && nGet[1] == 's' && nGet[2] == 'r' && nGet[3] == '=')
				{
					bool Flag = false;
					for (map<unsigned int, clswbusr2::clswbusrlogstr*>::iterator it = p_wUsr.mpusr.begin(), m = p_wUsr.mpusr.end(); it != m || !(Flag = true); it++) {
						if (!strbasprc::vergCharPH(it->second->usr, buf + 4)) continue;
						logId = it->first, log = 3; break;
					}
					if (Flag) log = 1, url[3] = '0';
				}
				else log = 1;
			}
			else if (log == 3) {
				if (nLen > 4 && nGet[0] == 'p' && nGet[1] == 's' && nGet[2] == 'w' && nGet[3] == '=') {
					char* J = p_wUsr.mpusr.find(logId)->second->psw; if (!strbasprc::vergCharP(J, buf + 4)) log = 1, url[3] = '1';
					else logId = p_wUsr.voegid(logId), log = 0, url[3] = '2';
				}
				else log = 1;
			}
			else if (log == 1 && nLen > 3 && nGet[0] == 'i' && nGet[1] == 'd' && nGet[2] == '=') {
				if (p_wUsr.getId(strbasprc::cvintcharStr(nGet + 3), logId, logWId)) log = 0;
			}
			else if (!log && (log = getLsActieF(nGet, nLen))) url = urlLgF3, imgBl = 2;
			else if (!url && (!nLen || ((nLen < 6 && strbasprc::indChar('.', nGet) != -1) || strbasprc::indChar('.', nGet + (nLen - 6)) != -1))) {
				if (nLen > 0 && nGet[nLen - 1] == '/') nGet[--nLen] = '\0';
				if ((log && (((nLen == -1 && (url = urlInd)) && (imgBl = 2) && (flag = true)) || (nLen >= 8 && strbasprc::vergCharP(nGet + (nLen - 8), "back.jpg") || (nLen >= 4 && strbasprc::vergCharPH(nGet + (nLen - 3), ".js")) || (nLen >= 5 && strbasprc::vergCharPH(nGet + (nLen - 4), ".css")) || (strbasprc::vergCharP(nGet, "lgFr.htm") && (log = 2))))) || !log) {
					char* B = NULL;
					if (!url && nLen < 30) {
						if ((nLen >= 5 && strbasprc::vergCharPH(nGet + (nLen - 5), ".html")) || (nLen >= 4 && strbasprc::vergCharPH(B = nGet + (nLen - 4), ".htm"))) imgBl = 2;
						else if (B && strbasprc::vergCharPH(B, ".jpg"))imgBl = 1;
						else if (B && strbasprc::vergCharPH(B, ".css"))imgBl = 3;
						else if (nLen >= 3 && strbasprc::vergCharPH(nGet + (nLen - 3), ".js"))imgBl = 4;
						url = nGet;
					}
				}
				else break;
		}
				if (flag) break;
				else nGet += nLen + 1, nLen = -1;
		} if (len == 6) url = urlInd2, imgBl = 0;
		else if (imgBl == 2 && log) imgBl = 0;
	}
	

	strncpy_s(buf, 6, "Site/", bufLen = 5);
	if (url) {
		for (unsigned int t = 0; url[t] != '\0'; t++)
			if (url[t] == '/') buf[bufLen++] = '/';
			else buf[bufLen++] = url[t]; buf[bufLen] = '\0';
			if (!fileObj.open(buf)) url = NULL;
	}
	if (!url) {
		strncpy_s(buf + 5, 8, urlInd, bufLen = 5 + 7);
		imgBl = 0;
		if (!fileObj.open(buf)) return;
	}
		
	voeg("HTTP/1.1 200 OK\r\nContent-Type: ", 31);
	switch (imgBl) {
	case 1: voeg("image/jpeg", 10); break;
	case 3: voeg("text/css", 8); break;
	case 4: voeg("text/javascript", 15); imgBl = 2; break;
	default: voeg("text/html", 9); break;
	}
	voeg("\r\nConnection: close\r\n\r\n", 23);
	if (imgBl == 2) voegSH(fileObj.file, fileObj.fLen);
	else voegS(fileObj.file, fileObj.fLen);
}

uint8_t clsNSite::func::getLsActieF(char* nGet, int nLen) {
	switch (nLen) {
	case 4: 
		if (strbasprc::vergCharP(nGet, "stwz")) return 4;
		if (strbasprc::vergCharP(nGet, "sdwz")) return 5;
		if (strbasprc::vergCharP(nGet + 1, "str") && (*nGet == 'R' || *nGet == 'S')) return 7 + *nGet / 'S';
		return 0;
	case 6:
		if (*nGet == 'l' && nGet[1] == 'd' && (nGet[2] >= '0' && nGet[2] <= '9') && (nGet[3] >= '0' && nGet[3] <= '9')) return 6;
		return 0;
	} return 0;
}

void clsNSite::func::voegS(char* x, unsigned long l) {
	for (unsigned long t = 0; t < l; t++) voegC(*(x)++);
}
void clsNSite::func::voegSH(char* x, unsigned long l) {
	char c; uint8_t T; unsigned int B = T = 0;
	for (unsigned long t = 0; t < l && ((c = *(x++)) || !c); t++)
		if (((T == 6 || T == 7) && ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'x')) && 
			((B += strbasprc::cvintcharint(c) * [&] { if (T == 6) return 60; else return 1; }()) || !B)) ||
			(c == '/' && !T) || 
			(c == '*' && (T == 1 || T == 8)) || 
			(c == '?' && (T == 3 || T == 5)) || 
			(c == '@' && (T == 2 || T == 4))) T++;
		else if (T == 9 && c == '/') voegCode(B), T = B = 0;
		else { if (T) voegFlag(T, B), T = B = 0; voegC(c); 
		}
}

void clsNSite::func::voegFlag(uint8_t x, unsigned int b) { 
	for (uint8_t t = 0; t < x; t++)
		if (!t) voegC('/');
		else if (t == 1 || t == 8) voegC('*');
		else if (t == 2 || t == 4) voegC('@'); 
		else if (t == 3 || t == 5) voegC('?');
		else voegC(strbasprc::cvintcharchar((uint8_t)([&] { if (t == 6) return b / 60; else return b % 60; })()));
}

void clsNSite::func::voegC(char x) {
		ls[lsLen++] = x; if (lsLen == SENDLEN_INT) send(), lsNo = p_nSite->getStr.get(ls), lsLen = 0;
}

void clsNSite::func::voegCode(unsigned int x) {
	switch (x) {
	case 0: voeg(buf, strbasprc::cvcharlngth(60, logId, buf)); break;
	case 1: voegNm(); break;
	case 2: voegNo(); break;
	case 3: voegUp(); break;
	case 4: voegNoD(); break;
	case 5: if (logWId) voeg("parent.parent.lgUsrId = \'", 25), voeg(buf, strbasprc::cvcharlngth(60, logId, buf)), voeg("\';", 2); break;
	case 6: voegTmp(); break;
	case 7: voegLdPl(); break;
	case 8: voegStream(); break;
	}
}



bool clsNSite::func::breakwebchar1(char c) {
	if (c != '\n' && c != '\r') {
		return false;
	}
	return true;
}

bool clsNSite::func::breakwebchar2(char c) {
	if (c != '?' && c != '\0' && c != '&' && c != '@' && c != ' ') {
		return false;
	}
	return true;
}

char* clsNSite::func::urlEncode(char* str) {
	char c, bufHex[10];	int ic, loen = strbasprc::charPLen(str); bufLen = 0;

	for (int i = 0; i < loen; i++) {
		c = str[i];
		ic = c;
		// uncomment this if you want to encode spaces with +
		/*if (c==' ') new_str += '+';
		else */if (bufLen < 126) if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') buf[bufLen++] = c;
		else {
			//sprintf(bufHex, "%X", c);
			buf[bufLen++] = '%';
			if (ic < 16)
				buf[bufLen++] = '0';
			
			for (char* a = bufHex; *a != '\0'; a++) if (bufLen > 126) { bufLen = 0; break; } else buf[bufLen++] = *a;
		}
		else bufLen = 0;
	}
	buf[bufLen] = '\0'; return buf;
}

char* clsNSite::func::urlDecode(char* str) {
	char ch; int i, ii, loen = strbasprc::charPLen(str); bufLen = 0;
	for (i = 0; i < loen; i++) {
		if (str[i] != '%') {
			if (bufLen < 127)
			if (str[i] == '+')
				buf[bufLen++] = ' ';
			else
				buf[bufLen++] = str[i];
			else { bufLen = 0; break; }
		}
		else if (bufLen < 127) {
			{
				char p[]{ '%', 'x', '\0' };
				#ifdef _WIN32
				sscanf_s(string(str).substr(i + 1, 2).c_str(), p, & ii);
				#endif
				#ifndef _WIN32
				sscanf(string(str).substr(i + 1, 2).c_str(), p, &ii);
				#endif	
			}
			ch = static_cast<char>(ii);
			buf[bufLen++] = ch;
			i = i + 2;
		}
		else { bufLen = 0; break; }
	}
	buf[bufLen] = '\0';
	return buf;
}
#include "ThreadCls.h"

void mainThreadCls::trLisHomeCls::dimExF(mainThreadCls::strSndV s) {
	char* str = s.pack; int len = s.len;
	if (s.len < 10) return;
	if (str[4] == 'A' && str[5] == 'N') dimRicht = 0;
	else if ((str[4] == 'U' && str[5] == 'T' && (dimRicht = 3)) || (((str[4] >= '0' && str[4] <= '9') || (str[4] >= 'a' && str[4] <= 'f')) && ((((str[5] >= '0' && str[5] <= '9') || (str[5] >= 'a' && str[5] <= 'f')) && (dimRicht = 2)) || (str[5] >= 'A' && str[5] <= 'Q' && (dimRicht = 1) && (str[5] = [&](unsigned __int8 XX) { if (XX < 10) return XX + '0'; else return (XX - 10) + 'a'; }(str[5] - 'A')))) && ((dimW = strbasprc::cv16waarde(str + 4)) || !dimW))) str[4] = 'A', str[5] = 'N';
	else return;
	strncpy_s(dimCBuf, 11, "Apparaten\\", 10); dimCBuf[10] = str[2]; dimCBuf[11] = str[3]; strncpy_s(dimCBuf + 12, 11, "\\Signalen\\", 10); strncpy_s(dimCBuf + 22, len - 1, str + 2, len - 2); strncpy_s(dimCBuf + len + 20, 5, ".txt", 4);
	if (!dimFileObj.open(dimCBuf) || strbasprc::vergCharP(dimFileObj.file, "GG")) return; len = strbasprc::charPLen(dimFileObj.file); strncpy_s(str, len + 1, dimFileObj.file, len);
	dimExAF(str, len);
}

void mainThreadCls::trLisHomeCls::dimExAF(char* str, int len) {
	strncpy_s(dimCBuf, 9, "Actie\'s\\", 8); strncpy_s(dimCBuf + 8, len + 1, str, len); strncpy_s(dimCBuf + 8 + len, 5, ".txt", 4);
	if (!dimFileObj.open(dimCBuf)) return; unsigned long loc = 0; char* file = dimFileObj.file;
	while (!strbasprc::vergCharP(strbasprc::remCommCharP(strbasprc::charPLsR(str, file, loc)), "GG"))
		if (str[0] == 'N' && str[1] == 'A') {
			len = strbasprc::charPLen(str) - 2;
			for (unsigned __int8 t = 0; t < len; t++) str[t] = str[t + 2];
				dimExAF(str, len);
		}
		else {
			strncpy_s(dimCBuf, 22, "Apparaten\\11\\Nummers\\", 21), dimCBuf[10] = str[2], dimCBuf[11] = str[3], strncpy_s(dimCBuf + 21, (dimCBufLen = strbasprc::charPLen(str + 2)) + 1, str + 2, dimCBufLen); dimCBuf[23] = 'N', dimCBuf[24] = 'O', dimCBufLen = 21 + dimCBufLen; strncpy_s(dimCBuf + dimCBufLen, 5, ".txt", 4);
			if (!dimFileObj.open(dimCBuf)) return;
			dimLsNow = exMes->getStr(dimLs); *dimLs = '@', strncpy_s(dimLs + 1, dimSendLen = strbasprc::charPLen(str) + 1, str, dimSendLen - 1), dimLs[2] = 'V', dimLs[dimSendLen++] = '+'; unsigned __int8 aaa = adrs.load(); dimLs[dimSendLen] = aaa / 60 + '0', dimLs[dimSendLen + 1] = aaa % 60 + '0';
			dimCBufLen = (*strbasprc::charPLsR(dimCBuf, dimFileObj.file, dimFileObj.loc) - '1') * 100 + (dimCBuf[1] - '0') * 10 + (dimCBuf[2] - '0');
			threadCls->statStruc[900 + dimCBufLen].start(stSndStt{ (unsigned __int8)[&] { if ((!dimRicht && (dimLs[5] = 'a') && (dimLs[6] = 'n')) || (dimRicht == 3 && (dimLs[5] = 'u') && (dimLs[6] = 't'))) { len = (dimRicht / 3 + 1) % 2; return 7; } else { len = dimW; return dimRicht * 2 + 7; } }(), (unsigned int)dimCBufLen, (unsigned __int8)len, dimFileObj.loc, exMes, dimFileObj.file, strSndV{ dimLs, dimSendLen, exMes, dimLsNow } }, aaa);
		}
}

void mainThreadCls::stSndStt::funcD() {
	unsigned __int8 w = threadCls->statDimVar[no].load();
	if (type == 9) if (w >= 255 - val) val = 255; else val += w;
	else if (w <= val) val = 0; else val = w - val; threadCls->statDimVar[no].store(val), type = 1; char* x = s.pack + 5; unsigned int A = val; *x++ = strbasprc::cv16char0(A), *x = strbasprc::cv16char1(A);
}
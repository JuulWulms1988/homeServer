#include "MemFile.h"

memFileCls::memFileCls(char* path) {
	strbasprc bas;
	char p[378]; unsigned int t = bas.charPLen(path); strncpy_s(p, t + 1, path, t);
	mainDir = new Dir(p, &bas, 0);
}

bool memFileCls::open(char* path, char*& str, unsigned long& lLen, strbasprc& bas) {
	Dir* point = mainDir; bool flag = false; char buf[378]; int p;
	while (!flag) {
		if ((p = bas.indChar('\\', path)) != -1) path[p] = '\0'; else flag = true; unsigned long t = 0; 
		for (unsigned int rl = 1; *(bas.charPLsR(buf, point->ls, t)) || !(flag = true); rl++) {
			if (flag && bas.vergCharPH(buf, path)) { lLen = point->mLn.find(rl - 1)->second; str = point->fl.find(rl - 1)->second; return true; }
			else if (!flag && bas.vergCharPH(buf, path)) {
				point = point->mp.find(rl - 1)->second; break;
			}
		}
		path += p + 1;
	} 
	return false;
}

memFileCls::Dir::Dir(char* path, strbasprc* bas, unsigned int tF) {
	char buf[378] = "dir \""; char fN[32] = "file_"; bas->charPVC(fN, ".txt", 5 + bas->cvcharlngth(60, tF, fN + 5));
	unsigned int pTB = bas->charPLen(path); path[pTB++] = '\\'; path[pTB] = '\0'; 
	system(bas->charPVC(buf, fN, bas->charPVCI(buf, "\" /n /b > ", bas->charPVI(buf, path) - 1)));
	{ unsigned long ii; ls = set(fN, bas, ii); }
	bas->charPVC(buf, "\"", (bas->charPVCI(buf, fN, bas->charPVCI(buf, "del \"", 0))))[pTB + 20] = '\0';
	system(buf); unsigned long cnt = 0; for (unsigned int rl = 0; *bas->charPLsR(buf, ls, cnt); path[pTB] = '\0') {
		if (bas->indChar('.', buf) != -1) { unsigned long lenG; fl.insert(pair<unsigned int, char*>(rl, set(bas->charPVC(path, buf, pTB), bas, lenG))); 
		mLn.insert(pair<unsigned int, unsigned long>(rl++, lenG));
		}
		else mp.insert(pair<unsigned int, Dir*>(rl++, new Dir(bas->charPVC(path, buf, pTB), bas, tF + 1)));
	}
}

char* memFileCls::Dir::set(char* src, strbasprc* bas, unsigned long& lenG) {
	char* buf = new char[40000000]; unsigned long tel = 0;
	ifstream s(src, ios::binary);
	while (!s.eof()) buf[tel++] = (char)s.get(); 
	char* b = new char[tel--]; lenG = tel;
	for (unsigned long t = 0; t < tel; t++) b[t] = buf[t];
	b[tel] = '\0'; delete[4000000] buf; return b;
}

memFileObj::memFileObj(char* path, memFileCls* str) {
	openStr(path, str);
}

memFileObj::memFileObj(memFileCls* str) {
	struc = str;
}

memFileObj::memFileObj() {
}


bool memFileObj::openStr(char* path, memFileCls* str) {
	struc = str; return open(path);
}

bool memFileObj::open(char* path) {
	strbasprc bas; loc = 0; if (bas.indChar('.', path) == -1) return false; 
	char pP[378]; unsigned int len = bas.charPLen(path); strncpy_s(pP, len + 1, path, len);
	return struc->open(pP, file, fLen, bas);
}

char memFileObj::get() {
	char x = file[loc]; if (x) loc++;
	return x;
}

bool memFileObj::eof() {
	if (file[loc] == '\0') return true; return false;
}
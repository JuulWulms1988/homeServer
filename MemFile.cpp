#include "MemFile.h"

memFileCls::memFileCls(const char* path) {
	strbasprc bas;
	char p[378]; unsigned int t = bas.charPLen(path); strncpy_s(p, t + 1, path, t);
	mainDir = new Dir(p, &bas, 0);
}

bool memFileCls::open(const char* path, char*& str, unsigned long& lLen, strbasprc& bas) {
	Dir* point = mainDir; bool flag = false; char buf[378]; int p;
	while (!flag) {
		if ((p = bas.indChar('/', path)) != -1); else flag = true; unsigned long t = 0; 
		for (unsigned int rl = 1; *(bas.charPLsR(buf, point->ls, t)) || !(flag = true); rl++) {
			if (flag && bas.vergCharPH(buf, path)) { lLen = point->mLn.find(rl - 1)->second; str = point->fl.find(rl - 1)->second; return true; }
			else if (!flag && bas.vergCharPH_path(buf, path)) {
				point = point->mp.find(rl - 1)->second; break;
			}
		}
		path += p + 1;
	} 
	return false;
}

memFileCls::Dir::Dir(char* path, strbasprc* bas, unsigned int tF) {
#ifdef _WIN32
	char buf[378]{ 'd', 'i', 'r', ' ', '\"', '\0' };
	unsigned int pTB = bas->charPLen(path); path[pTB++] = '/'; path[pTB] = '\0';
	{
		char p[]{ '\"', ' ', '/', 'n', ' ', '/', 'b', '\0' };
		bas->charPVC(buf, p + 7, bas->charPVCI(buf, p, bas->charPVI(buf, path) - 1));
	}
#endif
#ifndef _WIN32
	char buf[378]{ 'd', 'i', 'r', ' ', '-', '1', ' ', '\0' };
	unsigned int pTB = bas->charPLen(path); path[pTB++] = '/'; path[pTB] = '\0';
	{
		char p = '\0';
		bas->charPVC(buf, &p, bas->charPVCI(buf, &p, bas->charPVI(buf, path) - 1));
	}
#endif
	{ unsigned long ii; ls = setP(buf, bas, ii); }
	unsigned long cnt = 0; for (unsigned int rl = 0; *bas->charPLsR(buf, ls, cnt); path[pTB] = '\0') {
		if (bas->indChar('.', buf) != -1) { unsigned long lenG; fl.insert(pair<unsigned int, char*>(rl, set(bas->charPVC(path, buf, pTB), bas, lenG))); 
		mLn.insert(pair<unsigned int, unsigned long>(rl++, lenG));
		}
		else mp.insert(pair<unsigned int, Dir*>(rl++, new Dir(bas->charPVC(path, buf, pTB), bas, tF + 1)));
	}
}

char* memFileCls::Dir::setP(const char* src, strbasprc* bas, unsigned long& lenG) {
	char* buf = new char[40000000]; unsigned long tel = 0;
	FILE* s;
#ifdef _WIN32
	{
		char p[]{ 'r', 't', '\0' };
		s = _popen(src, p);
	}
	while (fgets(buf + tel, 2, s)) tel++;
	_pclose(s);
#endif
#ifndef _WIN32
	{
		char p[]{ 'r', '\0' };
		s = popen(src, p);
	}
	while (fgets(buf + tel, 2, s)) tel++;
	pclose(s);
#endif
	char* b = new char[tel + 1]; lenG = tel++;
	for (unsigned long t = 0; t < tel; t++) b[t] = buf[t];
	delete[] buf; return b;
}

char* memFileCls::Dir::set(const char* src, strbasprc* bas, unsigned long& lenG) {
	char* buf = new char[40000000]; unsigned long tel = 0;
	ifstream s(src, ios::binary);
	while (!s.eof()) buf[tel++] = (char)s.get(); 
	char* b = new char[tel--]; lenG = tel;
	for (unsigned long t = 0; t < tel; t++) b[t] = buf[t];
	b[tel] = '\0'; delete[] buf; return b;
}

memFileObj::memFileObj(const char* path, memFileCls* str) {
	openStr(path, str);
}

memFileObj::memFileObj(memFileCls* str) {
	struc = str;
}

memFileObj::memFileObj() {
}


bool memFileObj::openStr(const char* path, memFileCls* str) {
	struc = str; return open(path);
}

bool memFileObj::open(const char* path) {
	strbasprc bas; loc = 0; if (bas.indChar('.', path) == -1) return false; 
	//char pP[378]; unsigned int len = bas.charPLen(path); strncpy_s(pP, len + 1, path, len);
	return struc->open(path, file, fLen, bas);
}

char memFileObj::get() {
	char x = file[loc]; if (x) loc++;
	return x;
}

bool memFileObj::eof() {
	if (file[loc] == '\0') return true; return false;
}
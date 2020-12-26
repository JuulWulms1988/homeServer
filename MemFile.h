#pragma once
#include <iostream>
#include <fstream>
#include "Basproc.h"
#include <map>

using namespace std;

class memFileObj;

class memFileCls {
public:
	memFileCls(char* path);
private:
	friend class memFileObj;
	class Dir {
	public:
		Dir(char* path, strbasprc* bas, unsigned int tF);
		char* ls;
		map<unsigned int, Dir*> mp;
		map<unsigned int, char*> fl;
		map<unsigned int, unsigned long> mLn;
	private:
		char* set(char* src, strbasprc* bas, unsigned long& lenG);
	};
	bool open(char* path, char*& str, unsigned long& lLen, strbasprc& bas);
	Dir* mainDir;
};

class  memFileObj {
public:
	memFileObj(char* path, memFileCls* str);
	memFileObj(memFileCls* str);
	memFileObj();
	//memFileObj(char* path, memFileCls* str);
	bool openStr(char* path, memFileCls* str);
	bool open(char* path);
	char get();
	bool eof();
	char* file;
	unsigned long fLen;
	unsigned long loc;
private:
	memFileCls* struc;
};
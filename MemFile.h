#pragma once
#include <stdint.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "Basproc.h"
#include <map>

using namespace std;

class memFileObj;

class memFileCls {
public:
	memFileCls(const char* path);
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
		char* set(const char* src, strbasprc* bas, unsigned long& lenG);
		char* setP(const char* src, strbasprc* bas, unsigned long& lenG);
	};
	bool open(const char* path, char*& str, unsigned long& lLen, strbasprc& bas);
	Dir* mainDir;
};

class  memFileObj {
public:
	memFileObj(const char* path, memFileCls* str);
	memFileObj(memFileCls* str);
	memFileObj();
	bool openStr(const char* path, memFileCls* str);
	bool open(const char* path);
	char get();
	bool eof();
	char* file;
	unsigned long fLen;
	unsigned long loc;
private:
	memFileCls* struc;
};
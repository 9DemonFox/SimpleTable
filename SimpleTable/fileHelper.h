#pragma once
#ifndef  _FILE_HELPER__H_
#define  _FILE_HELPER__H_
#include<mutex>
#include<thread>
#include<cstdio>
#include"Util.h"
using namespace std;
class FileHelper {
public:
	static void writeFile(mutex* mtx, int* i,const char* filePath ,int thread_id);
};

// µ¥ÀýÄ£Ê½ Singleton
class FileHandler {
private:
	FileHandler() {}
	static mutex mtxForConstructSelf_;
	static mutex mtx;
	static FileHandler* fileHandler_;

public:
	static FileHandler getInstance()
	{
		if (fileHandler_ == NULL) {
			mtxForConstructSelf_.lock();
			if (fileHandler_ == NULL)fileHandler_ = new FileHandler();
			mtxForConstructSelf_.unlock();
		}
		return *fileHandler_;
	}

	 void printNum(int* i) {
		cout << *i << endl;
	}
};
#endif 
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
	//mutex* mtx = new mutex();
	static void writeFile(mutex* mtx, int* i, int thread_id);
};

// ����ģʽ Singleton
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

FileHandler* FileHandler::fileHandler_ = NULL;
mutex FileHandler::mtx;
mutex FileHandler::mtxForConstructSelf_;
#endif 
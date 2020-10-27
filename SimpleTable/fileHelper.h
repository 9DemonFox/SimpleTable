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
	static void writeFile(mutex* mtx, int* i, const char* filePath, int thread_id);
};

// 单例模式 Singleton
class FileHandler {
private:
	FileHandler() {}
	FileHandler(const FileHandler& fileHandler) {}
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
	/// <summary>
	/// 从文件获取数据到buffer，需要线程安全
	/// </summary>
	/// <param name="file"></param>
	/// <param name="buffer"></param>
	/// <returns></returns>
	int getOneRow(FILE* file, char* buffer) {
		if (fgetc(file) == EOF)return 0;
		else {
			fseek(file, -1, SEEK_CUR);
			fgets(file, sizeof(buffer), buffer);
			return 1;
		}
	}
};
#endif 
#pragma once
#ifndef  _FILE_HELPER__H_
#define  _FILE_HELPER__H_
#include<mutex>
#include<thread>
#include<cstdio>
#include"Util.h"
#include "config.h"
using namespace std;
class FileHelper {
public:
	static void writeFile(mutex* mtx, int* i, const char* filePath, int thread_id);
};

// ����ģʽ Singleton
class FileHandler {
private:
	FileHandler() {}
	FileHandler(const FileHandler&) {}
	FileHandler& operator= (const FileHandler&) {};
	static mutex mtxForConstructSelf_;
	static mutex mtx;
	static FileHandler* fileHandler_;

public:
	static FileHandler* getInstance()
	{
		if (fileHandler_ == NULL) {
			mtxForConstructSelf_.lock();
			if (fileHandler_ == NULL)fileHandler_ = new FileHandler();
			mtxForConstructSelf_.unlock();
		}
		return fileHandler_; // ֻ�ܷ���FileHandler* �Ż᲻���ø��ƹ��캯��
	}
	/// <summary>
	/// ���ļ���ȡ���ݵ�buffer����Ҫ�̰߳�ȫ
	/// </summary>
	/// <param name="file"></param>
	/// <param name="buffer"></param>
	/// <returns></returns>
	int getOneRow(FILE* file, char* buffer, const int file_pos, const int lengthOfOneRow) {
#ifdef DEBUG
		cout << "\nfile_pos " << file_pos << " file pointer position: " << ftell(file);
#endif // DEBUG
		fseek(file, file_pos, SEEK_SET);
		if (fgetc(file) == EOF)return 0;
		else {
			fseek(file, -1, SEEK_CUR);
			fgets(buffer, lengthOfOneRow + 1, file);//read lengthOfOneRow
			return 1;
		}
	}
};
#endif 
#include "fileHelper.h"
using namespace std;

void FileHelper::writeFile(mutex* mtx, int* i, const char* filePath, int thread_id)
{
	while (true) {
		mtx->lock();
		FILE* file = fopen(filePath, "a+");
		fseek(file, *i, SEEK_END);
		if (*i > 64) {
			mtx->unlock();
			return;
		}
		char in = (char)(*i + '0');
		(*i)++;
		fputc(in, file);
		cout << "thread_id:" << thread_id;
		fclose(file);
		mtx->unlock();
		for (int j = 0; j < 1000000; )j++;
	}
}


// 静态类的静态成员必须在类外进行初始化
FileHandler* FileHandler::fileHandler_ = NULL;
mutex FileHandler::mtx;
mutex FileHandler::mtxForConstructSelf_;
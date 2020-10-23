#include "fileHelper.h"
using namespace std;

void FileHelper::writeFile(mutex* mtx, int* i, int thread_id)
{
	while (true) {
		mtx->lock();
		FILE* file = fopen("testThreads.txt", "a+");
		fseek(file, *i, SEEK_END);
		if (*i > 90) {
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


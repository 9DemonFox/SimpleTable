#include "Util.h"
#include <math.h>
#include <fstream>
#include <sys/stat.h>

/// <summary>
/// 将数字返回字符串 ， 如果位数>n,返回空
/// </summary>
/// <param name="n"></param>
/// <param name="id"></param>
/// <returns></returns>
string Utils::num2NSizeString(const int n, int id)
{
	string row = "";
	if (id > (pow(10, n) - 1)) {// n=3,999<1000
		throw "over the max length";
	}
	int tDigit;
	for (int i = 0; i < n; i++) {
		tDigit = pow(10, n - 1 - i);
		if (id < tDigit) {
			row += "0";
		}
		else {
			row += (char)(id / tDigit + 48);
			id = id % tDigit;
		}
	}
	return row;
}

int Utils::nSizeString2Num(string s)
{
	int len = s.length();
	int ret = 0;
	int i = 0;
	while (true) {
		if (s[i] != '0')break;
		i++;
	}
	for (; i < len; i++) {
		ret += (s[i] - 48) * pow(10, len - i - 1);
	}
	return ret;
}

string Utils::getRandomNByteString(int n)
{
	if (n <= 0)return "";
	unsigned int seed = time(NULL);
	srand(seed + rand());
	string ret;
	for (int i = 0; i < n; i++) {
		ret += rand() % 27 + 97;
	}
	return ret;
}

string Utils::paddingToNByteString(string s, int maxByte, POSITION pos)
{
	if (s.size() > maxByte) {
		throw "over size";
	}
	else {
		int paddingSize = maxByte - s.size();
		switch (pos)
		{
		case POSITION::front:
			return string(paddingSize, ' ') + s;
		case POSITION::back:
			return s + string(paddingSize, ' ');
		default:
			break;
		}

	}
}

bool Utils::existsFile(const string file)
{
	struct stat buffer;
	return (stat(file.c_str(), &buffer) == 0);
}


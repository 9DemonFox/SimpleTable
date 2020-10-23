#pragma once
#include<iostream>;
#include<string>
#include<cmath>
#include<random>
#include<time.h>
using namespace std;




class Utils {
public:
	enum  POSITION {
		front,
		back
	};

	static string num2NSizeString(const int n, int id);

	static int nSizeString2Num(string s);

	static string getRandomNByteString(int n);
	static string paddingToNByteString(string s, int maxByte, POSITION pos);

};


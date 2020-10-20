#pragma once
#include<iostream>;
#include<string>
#include<cmath>
#include<random>
#include<time.h>
using namespace std;

static class Utils {
public:
	static string num2NSizeString(const int n, int id);

	static int nSizeString2Num(string s);

	static string getRandomNByteString(int n);

	static enum class POSITION {
	front,
	back
};

	static string paddingToNByteString(string s, int maxByte,POSITION pos);

};
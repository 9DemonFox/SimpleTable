#pragma once
#include<iostream>
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

	/// <summary>
	/// 
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	static int nSizeString2Num(string s);

	/// <summary>
	/// �����ȡnbyte����
	/// </summary>
	/// <param name="n"></param>
	/// <returns></returns>
	static string getRandomNByteString(int n);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="s"></param>
	/// <param name="maxByte">�����೤</param>
	/// <param name="pos">front or back </param>
	/// <returns></returns>
	static string paddingToNByteString(string s, int maxByte, POSITION pos);


	static bool existsFile(string file);

};


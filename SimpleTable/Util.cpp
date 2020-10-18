#include "Util.h"

/// <summary>
/// �����ַ���N���ȵ��ַ��� �� ���λ��>n,���ؿ�
/// </summary>
/// <param name="n"></param>
/// <param name="id"></param>
/// <returns></returns>
string num2NSizeString(const int n, int id)
{

	string row = "";
	if (id > (pow(10, n) - 1)) {// n=3,999<1000
		return "";
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

#include "ISimpleTable.h"
#include<vector>
#include<map>
#include "config.h"
using namespace std;
using namespace SimpleTable;
/// <summary>
/// �����ʵ������
/// </summary>
class IndexRBTress : IIndex<map<string, vector<int> > > {

	/// <summary>
	/// �ж��Ƿ��иñ���е�����
	/// </summary>
	/// <returns></returns>
	bool IHasIndex(string tableName, string tableIndex);

	///// <summary>
	///// �ж������Ƿ�������
	///// </summary>
	///// <returns></returns>
	//bool IIsUpToDate();

	/// <summary>
	/// ��������
	/// </summary>
	/// <param name="tableName"></param>
	/// <param name="colName"></param>
	/// <returns></returns>
	bool ICreatIndex(string tableName, string colName);


	/// <summary>
	/// �����
	/// </summary>
	/// <returns></returns>

	map<string, vector<int> > ICreatIndex(vector<int> values, vector<string> keys);// ����һ��key��Ӧ�ܶ�values

	///// <summary>
	///// ��������
	///// </summary>
	///// <param name="tableName"></param>
	///// <param name="colName"></param>
	///// <returns></returns>
	//bool IUpDateIndex(string tableName, string colName);

	///// <summary>
	///// ��ȡ����
	///// </summary>
	///// <returns></returns>
	//T IGetIndex();
};
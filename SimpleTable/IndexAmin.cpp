#include "IndexAmin.h"
#include <fstream>
#include "Util.h"
#include <vector>

bool IndexRBTress::IHasIndex(string tableName, string tableIndex)
{
	return Utils::existsFile(tableName) ? Utils::existsFile(tableName + tableIndex) : false;
}


/// <summary>
/// �漰�����������л�
/// </summary>
/// <param name="tableName"></param>
/// <param name="colName"></param>
/// <returns></returns>
bool IndexRBTress::ICreatIndex(string tableName, string colName)
{
	if (!Utils::existsFile(tableName)) {
		throw "table not exsit";
	}
	if (IHasIndex(tableName, colName)) {
		// ɾ������
	}
	// ��������
	map<string, vector<int>> = index;
	// ��ȡ�ļ�
	ISimpleTable* isimpleTable = new ISimpleTable();
	vector<IRow> = isimpleTable->IGetAllRows(tableName.c_str());
	
	return false;
}

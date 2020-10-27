#include "IndexAmin.h"
#include <fstream>
#include "Util.h"
#include <vector>

bool IndexRBTress::IHasIndex(string tableName, string tableIndex)
{
	return Utils::existsFile(tableName) ? Utils::existsFile(tableName + tableIndex) : false;
}


/// <summary>
/// 涉及到索引的序列化
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
		// 删除索引
	}
	// 声明索引
	map<string, vector<int>> = index;
	// 读取文件
	ISimpleTable* isimpleTable = new ISimpleTable();
	vector<IRow> = isimpleTable->IGetAllRows(tableName.c_str());
	
	return false;
}

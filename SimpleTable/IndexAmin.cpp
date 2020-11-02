#include "IndexAmin.h"
#include <fstream>
#include "Util.h"
#include <vector>
#include <assert.h>
using namespace SimpleTable;

bool IndexRBTree::IHasIndex(string tableName, string tableIndex)
{
	return Utils::existsFile(tableName) ? Utils::existsFile(tableName + "_" + tableIndex + ".bin") : false;
}

int IndexRBTree::init_map_serilization(RowsWithInfo rowsWithInfo)
{
	auto rows = rowsWithInfo.getRows();
	auto info = rowsWithInfo.getColInfo();
	auto s = info.columnType_.getAttrOfIndex(0);
	// ��һ����int
	assert(info.columnType_.getAttrOfIndex(0) == "     int");
	for (int i = 0; i < rows.size(); i++) {
		map_seri[rows[i].getAttrOfIndex(1)].push_back(Utils::nSizeString2Num(rows[i].getAttrOfIndex(0)));
	}
}

int IndexRBTree::ICreateIndex(string tableName, string columnName, ISimpleTable* isimpleTable, FileHandler* fileHandler)
{
	// ��ȡ��
	auto r = isimpleTable->IGetProjectedColumns(tableName.c_str(), *new vector<string>{ "  row_id",columnName }, *fileHandler);
	// �������л�����
	init_map_serilization(r);
	// ���л����ļ���
	map_seri.serialization((tableName + "_" + columnName + ".bin").c_str());
	return 1;
}

int IndexRBTree::ISearchRows(string tableName, string columnName, string op, string parameter, vector<int>* result)
{
	if (!IHasIndex(tableName, columnName)) {
		return -1;
	}
	map_seri.unserialization((tableName + "_" + columnName + ".bin").c_str());
	if (op == "=") {
		map<string, vector<int>>::iterator map_iter = map_seri.find(parameter);
		if (map_iter == map_seri.end()) {
			return 0;
		}
		else
		{
			*result = map_iter->second;
			return (*result).size();
		}
	}

}





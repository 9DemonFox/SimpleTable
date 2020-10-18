#include "ISimpleTable.h"

using namespace SimpleTable;

int SimpleTable::IRow::setAttrOfIndex(int index, columnType type, string content)
{
	classMap[index]=pair<columnType, string>(type, content);
	return 0;
}

pair<IRow::columnType, string> SimpleTable::IRow::getAttrOfIndex(int index)
{
	if (classMap.find(index) != classMap.end()) {
		pair<columnType, string>ret = classMap.at(index);
		return ret;
	}
	else
	{
		return pair<columnType,string>(columnType::T_NULL,"");
	}
}

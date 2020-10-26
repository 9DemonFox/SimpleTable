#include "ISimpleTable.h"
#include"Util.h"
using namespace SimpleTable;

SimpleTable::IRow::IRow(int rowId, int maxIndex)
{
	this->rowId_ = rowId;
	this->maxIndex_ = maxIndex;
	this->setAttrOfIndex(0, to_string(rowId_));
}

int SimpleTable::IRow::setAttrOfIndex(int index, string content)
{
	int isFirstSet = data_.find(index) == data_.end();
	data_[index] = content;
	return isFirstSet;
}

string SimpleTable::IRow::getAttrOfIndex(int index)
{
	if (index < 0 || index>maxIndex_) {
		throw "index out of array";
	}
	return data_[index];
}

string SimpleTable::IRow::dataToString()
{
	map<int, string>::iterator iter = data_.begin();
	string ret;
	if (iter == data_.end()) {
		throw "There is no data in this row!";
	}
	while (iter != data_.end())
	{
		ret += iter->second + "|";
		iter++;
	}
	ret += "\n";
	return ret;
}

int SimpleTable::IRow::setDataFromString(char seprator, string s)
{
	int i = 0;
	int index = 0;
	int len = s.length();
	int begin = 0;
	string content;
	while (s[i] != '\n') {
		while (s[i] != seprator) {
			i++;
		}
		content = s.substr(begin, i - begin);
		setAttrOfIndex(index++, content);
		i++;// 跳过分隔符
		begin = i;
	}
	return 1;
}

void SimpleTable::IRow::printData()
{
	cout << dataToString();
}

/// <summary>
/// 设置序列化的列名和随机的类型
/// </summary>
/// <param name="maxColumn"></param>
void SimpleTable::IColumnInfo::setSerialColumnNameAndRanomType(int maxColumn, int maxByte)
{
	for (int i = 0; i < maxColumn; i++) {
		if (i == 0) {
			this->columnName_->setAttrOfIndex(0, Utils::paddingToNByteString("row_id", maxByte, Utils::POSITION::front)); // 第一列是列名
			this->columnType_->setAttrOfIndex(0, Utils::paddingToNByteString(typeMap[T_INT], maxByte, Utils::POSITION::front));
		}
		else {
			this->columnName_->setAttrOfIndex(i, "col_" + Utils::num2NSizeString(maxByte - 4, i));
			this->columnType_->setAttrOfIndex(i, Utils::paddingToNByteString("string", maxByte, Utils::POSITION::front));
		}
	}
}
#include "TableAmin.h"
#include "RowAmin.h"

namespace SimpleTable { // 为了顺序访问的需要


	int TableAmin::ICreateTable(const char* tablename)
	{
		ISetColumnInfo();
		FILE* file;
		try {
			file = fopen(tablename, "r");// 判断文件是否存在 只读方式打开
			if (file != NULL) {
				cout << "table: " << tablename << " already exist\n";
				return 0;
			}
			else
			{
				file = fopen(tablename, "w+");
				if (file == NULL) {
					return -1;// 创建失败
				}
				else {
					fseek(file, 0, SEEK_END);
					string ctype = columnInfo_->columnType_->dataToString();
					string cname = columnInfo_->columnName_->dataToString();
					fputs(ctype.c_str(), file);
					fputs(cname.c_str(), file);
					fclose(file);
					cout << "table: " << tablename << " is created\n";
					return 1;
				}
			}
		}
		catch (exception& e) {
			cout << e.what();
			return -1;
		}
	}


	int TableAmin::IDeleteTable(const char* tablename) {
		try
		{
			if (std::remove(tablename) == 0) {
				cout << "table: " << tablename << " is deleted\n";
			}
			else {
				cout << "failed to delete the tabel " << tablename << "\n";
				return 0;
			}
		}
		catch (const std::exception& e)
		{
			cout << e.what();
			return -1;
		}

	}

	/// <summary>
	/// 设置列信息
	/// </summary>
	/// <returns></returns>
	int TableAmin::ISetColumnInfo()
	{
		this->columnInfo_->setSerialColumnNanmeAndRanomType(maxColumn_, maxByte_);
		return 1;
	}

	int TableAmin::IAppendOneRow(const char* tableName, IRow row) {
		FILE* file = fopen(tableName, "a+");//原来的EOF保留
		// TODO 线程安全
		fseek(file, 0, SEEK_END);
		return fputs(row.dataToString().c_str(), file);
	}

	string TableAmin::IGetOneRowByIndex(const char* tableName, int index)
	{
		return string();
	}

	IRow TableAmin::getOneRowByColumn(const char* tableName,int columnIndex, string value)
	{
		FILE* file;
		file = fopen(tableName, "r");// 判断文件是否存在 只读方式打开
		int lineCount = 0;
		int maxByte = 0;
		if (file != NULL) {
			while (fgetc(file) != '\n') {
				lineCount++;
			}
			fseek(file, 0, SEEK_SET);
			while (fgetc(file) != seprator_) { // 第一个分隔符为最大长度
				maxByte++;
			}
			lineCount++;// 换行符
			cout << "lineCount: " << lineCount << endl;
			cout << "maxByte; " << maxByte << endl;
		}
		else {
			throw "table not exist";
		}
		return IRow(1, 100);
	}

}
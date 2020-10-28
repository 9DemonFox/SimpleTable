#include "TableAmin.h"
#include "RowAmin.h"
#include <errno.h>
#include <algorithm>
#include <string.h>
//#define DEBUG
#define pr(x) cout<<#x<<" = "<<x<<endl
using namespace std;
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
		this->columnInfo_->setSerialColumnNameAndRanomType(maxColumn_, maxByte_);
		return 1;
	}

	int TableAmin::IAppendOneRow(const char* tableName, IRow row) {
		FILE* file = fopen(tableName, "a+");
		int file_position = fseek(file, 0, SEEK_END);
		// TODO 线程安全
#ifdef  DEBUG
		pr(file_position);
#endif //  DEBUG
		string s = Utils::paddingToNByteString(row.dataToString(), byteOfOneRow_, Utils::POSITION::back); // '\0'
#ifdef DEBUG
		const char* buf = s.c_str();
#endif // DEBUG
		fputs(s.c_str(), file);
		fclose(file);
		return 1;
	}

	string TableAmin::IGetOneRowStringByRowID(const char* tableName, int rowID)
	{
		if (rowID <= 0)
		{
			throw "rowID must over than 0";
		}

		FILE* file;
		file = fopen(tableName, "r");// 判断文件是否存在 只读方式打开
		int lineCount = 0;
		int maxByte = 0;
		fseek(file, info_size_, SEEK_SET);
		if (file != NULL) {
			if (fgetc(file) == EOF) { // 没有文件信息
				return "";
			}
			else {
				fseek(file, -1, SEEK_CUR); // fgetc() 移动了一步，回退

				fseek(file, byteOfOneRow_ * (rowID - 1), SEEK_CUR);
#ifdef DEBUG
				cout << "position:" << ftell(file);
#endif // DEBUG

				if (char* buffer = (char*)malloc(sizeof(char) * byteOfOneRow_)) {
					fgets(buffer, byteOfOneRow_, file);
					fclose(file);
					return buffer;
				}
			}
		}
		else {
			throw "table not exist";
		}

	}

	IRow TableAmin::getOneRowByRowID(const char* tableName, int rowID, string value)
	{
		return IRow(1, 100);
	}

	/// <summary>
	/// 获取所有行
	/// </summary>
	/// <param name="tableName"></param>
	/// <returns></returns>
	vector<IRow> TableAmin::IGetAllRows(const char* tableName)
	{
		// 计算所有行数
		vector<IRow> rows;
		FILE* file = fopen(tableName, "r");
		fseek(file, 0, SEEK_END);
		int rowNum = ftell(file) / byteOfOneRow_ - info_row_num_; // 总行数 = 文件大小/每行大小 - 列信息行树;
		for (int i = 1; i <= rowNum; i++) {
			IRow* r = new IRow();
			r->setRowId(i);
			r->setDataFromString(seprator_, IGetOneRowStringByRowID(tableName, i));
			rows.push_back(*r);
		}
		return rows;
	}

	/// <summary>
	/// 必须包含第0列，行号，设计缺陷
	/// </summary>
	/// <param name="tableName"></param>
	/// <param name="columnName"></param>
	/// <param name="fileHandler"></param>
	/// <returns></returns>
	RowsWithInfo TableAmin::IGetProjectedRows(const char* tableName, vector<string> columnName, FileHandler& fileHandler)
	{
		// 选出column所在列的列号
		IColumnInfo* columnInfo = new IColumnInfo(maxColumn_);
		FILE* file;
		file = fopen(tableName, "r");// 判断文件是否存在 只读方式打开
		int lineCount = 0;
		int maxByte = 0;
		RowsWithInfo rowsWithInfo;
		if (file != NULL) {
			if (char* buffer = (char*)malloc(sizeof(char) * byteOfOneRow_ + 1)) {
				IColumnInfo* colInfo = new IColumnInfo(this->maxColumn_);
				// fgets()读取n-1个字符
				if (fileHandler.getOneRow(file, buffer, 0 * byteOfOneRow_, byteOfOneRow_) == 1) {
					colInfo->columnType_->setDataFromString(seprator_, buffer);
				}
				if (fileHandler.getOneRow(file, buffer, 1 * byteOfOneRow_, byteOfOneRow_) == 1) {
					colInfo->columnName_->setDataFromString(seprator_, buffer);
				}
				int rowId = 0;
				vector<int> indexs;
				// 获取需要加载的列
				vector<string>::iterator iter;
				for (iter = columnName.begin(); iter != columnName.end(); iter++) {
					for (map<int, string>::iterator iter_col_info = colInfo->columnName_->data_.begin(); iter_col_info != colInfo->columnName_->data_.end(); iter_col_info++) {
						if (iter_col_info->second == *iter) {
							indexs.push_back(distance(colInfo->columnName_->data_.begin(), iter_col_info));
						}
					}
				}
				// 返回信息构建
				vector<int>::iterator int_iter;
				string retColType_s = "";
				string retColName_s = "";
				IRow retColType;
				IRow retColName;
				for (int_iter = indexs.begin(); int_iter != indexs.end(); int_iter++) {
					retColName_s += colInfo->columnName_->getAttrOfIndex(*int_iter) + seprator_;
					retColType_s += colInfo->columnType_->getAttrOfIndex(*int_iter) + seprator_;
				}
				retColName_s += "\n";
				retColType_s += "\n";
				retColType.setDataFromString(seprator_, retColType_s);
				retColName.setDataFromString(seprator_, retColName_s);
				// 创建被过滤的行列
				colInfo = new IColumnInfo(&retColName, &retColType);
				rowsWithInfo.setInfo(*colInfo);
				int p;
				vector<IRow>* rows = new vector<IRow>();// 返回的列
				int rowNum = 0 + info_row_num_;// 当前行号
				while (fileHandler.getOneRow(file, buffer, rowNum * byteOfOneRow_, byteOfOneRow_) == 1) { // 读取新行
					IRow t_row(rowNum - info_row_num_ + 1, maxColumn_);
					t_row.setDataFromString(seprator_, buffer);
					IRow r_row(rowNum - info_row_num_ + 1,indexs.size());// 存project后的数据
					string t_string = "";
					for (int_iter = indexs.begin(), p = 0; int_iter != indexs.end(); int_iter++, p++) {
						r_row.setAttrOfIndex(p, t_row.getAttrOfIndex(*int_iter));
					}
					r_row.setRowId(Utils::nSizeString2Num(r_row.getAttrOfIndex(0)));
					rows->push_back(r_row);
					rowNum++;
				}
				rowsWithInfo.setRows(*rows);
			}

		}
		else {
			throw "table not exist";
		}

		return rowsWithInfo;
	}


}
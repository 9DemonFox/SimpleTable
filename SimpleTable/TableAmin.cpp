#include "TableAmin.h"
#include "RowAmin.h"
#include <errno.h>
#include <algorithm>
//#define DEBUG
#define pr(x) cout<<#x<<" = "<<x<<endl
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
		FILE* file = fopen(tableName);
		fseek(file, 0, SEEK_END);
		int rowNum = ftell(file) / byteOfOneRow_ - info_row_num_; // 总行数 = 文件大小/每行大小 - 列信息行树;
		for (int i = 1;i <= rowNum;i++) {
			rows.push_back(IGetOneRowStringByRowID(i));
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
		auto columnInfo = new IColumnInfo();
		FILE* file;
		file = fopen(tableName, "r");// 判断文件是否存在 只读方式打开
		int lineCount = 0;
		int maxByte = 0;
		fseek(file, info_size_, SEEK_SET);
		if (file != NULL) {
			if (char* buffer = (char*)malloc(sizeof(char) * byteOfOneRow_)) {
				IColumnInfo* colInfo = new IColumnInfo(this->maxColumn_);
				if (fileHandler.getOneRow(file, buffer) == 1) {
					colInfo->columnType_->setDataFromString(buffer);
				}
				if (fileHandler.getOneRow(file, buffer) == 1) {
					colInfo->columnName_->setDataFromString(buffer);
				}
				int rowId = 0;
				RowsWithInfo* rowWithInfo = new RowsWithInfo(columnName.size());
				vector<int> indexs;
				for each (var name in *colInfo->columnName_)
				{
					var it = find(columnName.begin(), columnName.end(), name);
					it == columnName.end() ? continue : ;
				}
				while (fileHandler.getOneRow(file, buffer) == 1) {

				}
			}

		}
		else {
			throw "table not exist";
		}

		return RowsWithInfo();
		return RowsWithInfo();
	}


}
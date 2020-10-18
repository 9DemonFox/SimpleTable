#pragma once
#include <string>
#include <fcntl.h>
#pragma once
#include <assert.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
using namespace std;

namespace SimpleTable {

	struct IRow {
	public:
		IRow(int rowId) :rowId_(rowId) {};
	public:
		enum class columnType// 列支持T_INT 和 T_STRING
		{
			T_NULL,
			T_INT,
			T_STRING,
		};
		int setAttrOfIndex(int index, columnType type, string content);
		pair<columnType, string> getAttrOfIndex(int index);

	public:
		int rowId_;
	private:
		map<int, pair<columnType, string>> classMap;
		// 列号 <类型 值>
	};

	class Table {
	public:
		Table() {};
		vector <IRow> Rows;
		string tableName_;
	};

	class ISimpleTable
	{
	public:
		ISimpleTable() :rowNum_(0) { // 0行

		}
		virtual int ICreateTable(const char* tablename) = 0;
		virtual int IDeleteTable(const char* tablename) = 0;

		//virtual int IAppendOneRow(const char* tableName, IRow row) = 0;// return whitch line insered to, -1 失败
		//virtual int ISearchRow(const bool useIndex) = 0; // 1成功 -1失败

		//virtual int IAddIndex() = 0; // 1 成功 -1 失败
		//virtual int IDeleteIndex(const string indexName) = 0;// 1成功
		//virtual int IGetAllIndex() = 0;
	private:
		vector <IRow> Rows;
		int rowNum_;
		string tableName_;
	};

	class IIndex {
	public:
		IIndex() {

		}
		virtual int ICreatIndex(const char* tablename, const char* indexname, const int columnIndex) = 0;
	};
}



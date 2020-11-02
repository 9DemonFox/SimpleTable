#pragma once
#include "ISimpleTable.h"
#include "RowAmin.h"
#include<iostream>
#include<stdio.h>
#include<vector>
#include"fileHelper.h"
#include "config.h"
namespace SimpleTable {
	class TableAmin :public ISimpleTable
	{
	public:
		TableAmin() {
			std::cout << "This is realized by Amin \n";
		}

		int ICreateIndex(string columnName);

		int ICreateTable(const char* tablename);

		int IDeleteTable(const char* tablename);

		int ISetColumnInfo();

		/// <summary>
		/// 返回值为非负数插入成功
		/// 返回值为正数插入失败
		/// </summary>
		/// <param name="tablename"></param>
		/// <param name="row"></param>
		/// <returns></returns>
		int IAppendOneRow(const char* tablename, IRow row);

		string IGetOneRowStringByRowID(const char* tableName, int rowID);

		RowsWithInfo ISearchRows(const char* tablename, string col_name, string operater, string parameter, bool useIndex = false);

		IRow getOneRowByRowID(const char* tableName, int rowID, string value);

		vector<IRow> IGetAllRows(const char* tableName);

		RowsWithInfo IGetProjectedColumns(const char* tableName, vector<string> columnName, FileHandler& fileHandler);

		bool compare(const string op, const string l, const string r);
	};
}
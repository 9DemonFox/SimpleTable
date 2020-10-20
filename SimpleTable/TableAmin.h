#pragma once
#include "ISimpleTable.h"
#include "RowAmin.h"
#include<iostream>
#include<stdio.h>
#include<vector>
namespace SimpleTable {
	class TableAmin :public ISimpleTable
	{
	public:
		TableAmin() {
			std::cout << "This is realized by Amin \n";
		}
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
		int IAppendOneRow(const char* tablename,IRow row);
		string IGetOneRowByIndex(const char* tableName,int index);
		IRow getOneRowByColumn(const char* tableName, int columnIndex, string value);
	};
}
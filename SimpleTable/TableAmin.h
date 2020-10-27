#pragma once
#include "ISimpleTable.h"
#include "RowAmin.h"
#include<iostream>
#include<stdio.h>
#include<vector>
#include"fileHelper.h"
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
		/// ����ֵΪ�Ǹ�������ɹ�
		/// ����ֵΪ��������ʧ��
		/// </summary>
		/// <param name="tablename"></param>
		/// <param name="row"></param>
		/// <returns></returns>
		int IAppendOneRow(const char* tablename, IRow row);
		string IGetOneRowStringByRowID(const char* tableName, int rowID);
		IRow getOneRowByRowID(const char* tableName, int rowID, string value);
		vector<IRow> IGetAllRows(const char* tableName);
		RowsWithInfo IGetProjectedRows(const char* tableName, vector<string> columnName,FileHandler& fileHandler);

	};
}
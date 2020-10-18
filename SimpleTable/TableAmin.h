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
		//int IAppendOneRow(const char* tablename,RowAmin row);
	};
}
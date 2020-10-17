#pragma once
#include <string>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <sstream>
#include <vector>
using namespace std;
namespace SimpleTable{
	struct Row {
		int rowId = -1;
		vector <char[8]>data;// 7+1=8
	};

	class Table {
		vector <Row> data;
		int size;
	};

	class ISimpleTable
	{
	public:
		ISimpleTable() {

		}
		virtual int ICreateTable(const char* tablename) = 0;
		virtual int IDeleteTable(const char* tablename) = 0;

		virtual int IAppendOneRow(const char* tableName,Row row) = 0;// return whitch line insered to, -1 ʧ��
		//virtual int ISearchRow(const bool useIndex) = 0; // 1�ɹ� -1ʧ��

		//virtual int IAddIndex() = 0; // 1 �ɹ� -1 ʧ��
		//virtual int IDeleteIndex(const string indexName) = 0;// 1�ɹ�
		//virtual int IGetAllIndex() = 0;

	};
	
	class IIndex {
	public:
		IIndex() {

		}
		virtual int ICreatIndex(const char* tablename,const char* indexname,const int columnIndex)=0;
	};
}



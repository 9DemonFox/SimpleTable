#pragma once
#include <string>
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include "ISimpleTable.h"
#include "Util.h"
#include "fileHelper.h"
#include "config.h"
//#include "IndexAmin.h"
// �����һ��ͻύ�����ò�������
//#include "IndexAmin.h"

using namespace std;

namespace SimpleTable {

	class IRow {
	public:
		/// <summary>
		/// 
		/// </summary>
		/// <param name="rowId">�к�</param>
		/// <param name="maxIndex_">�е���Ŀ</param>
		IRow(int rowId, int maxIndex_);
		IRow() { maxIndex_ = 1000; };
	public:

		/// <summary>
		/// �������һ��ֵ ����1
		/// ����Ǹ���һ��ֵ ����0
		/// redis ������
		/// </summary>
		/// <param name="index"></param>
		/// <param name="content"></param>
		/// <returns></returns>
		int setAttrOfIndex(int index, string content);

		/// <summary>
		/// ������Ӧ������
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		string getAttrOfIndex(int index);

		/// <summary>
		/// ��ȡrowId
		/// </summary>
		/// <returns></returns>
		int rowId() { return rowId_; }

		void setRowId(int rowId) { rowId_ = rowId; }

		/// <summary>
		/// ��ȡ����ж�����
		/// </summary>
		/// <returns></returns>
		int maxIndex() { return maxIndex_; }

		void setMaxIndex(int maxIndex) { maxIndex_ = maxIndex; }

		string dataToString();

		/// <summary>
		/// ��s��Ϣ����data,���շָ���
		/// </summary>
		/// <param name="seprator"></param>
		/// <param name="s"></param>
		/// <returns></returns>
		int setDataFromString(char seprator, string s);

		void printData();

		map<int, string> data_;
	protected:
		int rowId_;
		int maxIndex_;
		// �к� <���� ֵ>
	};

	/// <summary>
	/// ����Ϣ���������� һ�д洢������һ�д洢��������
	/// ����
	/// �е����int or string TODO ֧���������
	/// </summary>
	class IColumnInfo {
	public:
		IColumnInfo() {};
		IColumnInfo(int maxColumn) { init(maxColumn); };
		IColumnInfo(IRow columnName, IRow columnType) {
			columnName_ = columnName;
			columnType_ = columnType;
		};
		void init(int maxColumn) {
			columnType_.setRowId(-1);
			columnName_.setRowId(0);
			columnType_.setMaxIndex(maxColumn);
			columnName_.setMaxIndex(maxColumn);

			for (int cET = columnTypeEnum::begin_ + 1; cET < columnTypeEnum::end_; cET++) {
				switch (cET)
				{
				case T_INT:
					typeMap[T_INT] = "int";
					break;
				case T_STRING:
					typeMap[T_STRING] = "string";
					break;
				default:
					break;
				}
			}
		};
		void init(IRow columnName, IRow columnType) {
			columnName_ = columnName;
			columnType_ = columnType;
		}
		enum columnTypeEnum// ��֧��T_INT �� T_STRING
		{
			begin_ = 0,
			T_INT,
			T_STRING,
			end_
		};
		/// <summary>
		/// �γ�Ҫ��
		/// </summary>
		void setSerialColumnNameAndRanomType(int maxColumn, int maxByte);
	public:
		/// <summary>
		/// �洢����
		/// </summary>
		IRow columnName_;

		/// <summary>
		/// �洢�е�����
		/// </summary>
		IRow columnType_;

		/// <summary>
		/// �����������Ĵ洢��
		/// </summary>
		map<columnTypeEnum, string> typeMap;

	};

	/// <summary>
	/// �ڹ��ˡ�ɸѡ�Ȳ���ʱ�������������ݲ���
	/// </summary>
	class RowsWithInfo {
	public:
		RowsWithInfo() {
		}
		void setRows(vector<IRow>rows) {
			rows_ = rows;
		}
		void setInfo(IColumnInfo col_info) {
			col_info_ = col_info;
		}
		vector<IRow> getRows() { return rows_; }
		IColumnInfo getColInfo() { return col_info_; }
	private:
		IColumnInfo col_info_;
		vector<IRow> rows_;
	};

	class ISimpleTable
	{
	public:
		ISimpleTable() :rowNum_(0) {
			columnInfo_ = new IColumnInfo(maxColumn_); // ��������Ϣ
		}

		/// <summary>
		/// �������
		/// </summary>
		/// <param name="tablename">����</param>
		/// <param name="columnInfo">����Ϣ</param>
		/// <returns></returns>
		virtual int ICreateTable(const char* tablename) = 0;
		virtual int IDeleteTable(const char* tablename) = 0;
		virtual int IAppendOneRow(const char* tableName, IRow row) = 0;// return whitch line insered to, -1 ʧ��
		virtual string IGetOneRowStringByRowID(const char* tableName, int rowID) = 0;

		/// <summary>
		/// ����ĳ������ɸѡ
		/// </summary>
		/// <param name="useIndex"></param>
		/// <returns></returns>

		// col = "aaaaaaaa";
		// ��ȡ���ر��ļ����ķ�����ȡ
		virtual RowsWithInfo ISearchRows(const char* tablename, string col_name, string operater, string parameter, FileHandler& fileHandler) = 0; // 1�ɹ� -1ʧ�� 

		//  "aaaaaaaa" <= col <= "bbbbbbbb"
		//virtual vector<IRow> ISearchRows(const char* tablename, string parameter1, string operater1, string col_name, string operater2, string parameter2) = 0;

		//virtual int ISetColumnInfo() = 0;

		virtual IRow getOneRowByRowID(const char* tableName, int rowID, string value) = 0;

		virtual vector<IRow> IGetAllRows(const char* tableName) = 0;

		///// <summary>
		///// ���ļ���ɸѡ�С���
		///// </summary>
		///// <param name="tableName"></param>
		///// <returns></returns>
		//virtual RowsWithInfo IGetProjectedColumns(const char* tableName, vector<int> row_id, vector<string> columnName) = 0;

		virtual RowsWithInfo IGetProjectedColumns(const char* tableName, vector<string> columnName, FileHandler& fileHandler) = 0;

		char seprator() {
			return seprator_;
		}

		virtual int ICreateIndex(string columnName) = 0;
		//virtual int IAddIndex() = 0; // 1 �ɹ� -1 ʧ��
		//virtual int IDeleteIndex(const string indexName) = 0;// 1�ɹ�
		//virtual int IGetAllIndex() = 0;
	protected:
		IColumnInfo* columnInfo_;
		vector <IRow> rows_;
		int rowNum_;
		string tableName_;
		static const char seprator_ = '|';
		static const int maxByte_ = 8;
		static const int maxColumn_ = 100;
		static const int info_row_num_ = 2;// �����Ϣ����
		static const int byteOfOneRow_ = (maxByte_ + 1) * maxColumn_ + 1;// �ָ��+���з�+��ֹ��
		static const int info_size_ = info_row_num_ * byteOfOneRow_; // �洢�ļ���Ϣ����
	};

	class IIndex {
		/// <summary>
		/// Index�ӿ�
		/// </summary>
	public:

		/// <summary>
		/// �ж��Ƿ��иñ���е�����
		/// </summary>
		/// <returns></returns>
		virtual bool IHasIndex(string tableName, string tableIndex) = 0;

		/// <summary>
		/// ��������
		/// </summary>
		/// <param name="tableName"></param>
		/// <param name="colName"></param>
		/// <returns></returns>
		virtual int ICreateIndex(string tableName, string columnName, ISimpleTable* isimpleTable, FileHandler* fileHandler) = 0;

		virtual int ISearchRows(string tableName, string columnName, string op, string parameter, vector<int>* result) = 0;

	};
}



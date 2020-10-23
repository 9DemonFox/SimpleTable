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
#define DEBUG
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

		/// <summary>
		/// ��ȡ����ж�����
		/// </summary>
		/// <returns></returns>
		int maxIndex() { return maxIndex_; }

		string dataToString();

		/// <summary>
		/// ��s��Ϣ����data,���շָ���
		/// </summary>
		/// <param name="seprator"></param>
		/// <param name="s"></param>
		/// <returns></returns>
		int setDataFromString(char seprator, string s);

		void printData();
	protected:
		map<int, string> data_;
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
		IColumnInfo(int maxColumn) {
			columnType_ = new IRow(0, maxColumn);
			columnName_ = new IRow(1, maxColumn);
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
		IRow* columnName_;

		/// <summary>
		/// �洢�е�����
		/// </summary>
		IRow* columnType_;

		/// <summary>
		/// �����������Ĵ洢��
		/// </summary>
		map<columnTypeEnum, string> typeMap;

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
		//virtual int ISearchRow(const bool useIndex) = 0; // 1�ɹ� -1ʧ�� 
		//virtual int ISetColumnInfo() = 0;
		virtual IRow getOneRowByRowID(const char* tableName, int rowID, string value) = 0;
		/// <summary>
		/// ��������Ϣ
		/// </summary>
		//virtual void ILoadColumnInfo() = 0;
		char seprator() {
			return seprator_;
		}
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
}



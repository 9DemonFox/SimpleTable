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
		/// <param name="rowId">行号</param>
		/// <param name="maxIndex_">列的数目</param>
		IRow(int rowId, int maxIndex_);
	public:

		/// <summary>
		/// 如果插入一个值 返回1
		/// 如果是更新一个值 返回0
		/// redis 是这样
		/// </summary>
		/// <param name="index"></param>
		/// <param name="content"></param>
		/// <returns></returns>
		int setAttrOfIndex(int index, string content);

		/// <summary>
		/// 返回相应的属性
		/// </summary>
		/// <typeparam name="T"></typeparam>
		/// <returns></returns>
		string getAttrOfIndex(int index);

		/// <summary>
		/// 获取rowId
		/// </summary>
		/// <returns></returns>
		int rowId() { return rowId_; }

		/// <summary>
		/// 获取最多有多少列
		/// </summary>
		/// <returns></returns>
		int maxIndex() { return maxIndex_; }

		string dataToString();

		/// <summary>
		/// 将s信息存入data,按照分隔符
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
		// 列号 <类型 值>
	};

	/// <summary>
	/// 列信息，包含两行 一行存储列名，一行存储数据类型
	/// 列名
	/// 列的类别：int or string TODO 支持其它类别
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
		enum columnTypeEnum// 列支持T_INT 和 T_STRING
		{
			begin_ = 0,
			T_INT,
			T_STRING,
			end_
		};
		/// <summary>
		/// 课程要求
		/// </summary>
		void setSerialColumnNameAndRanomType(int maxColumn, int maxByte);
	public:
		/// <summary>
		/// 存储列名
		/// </summary>
		IRow* columnName_;

		/// <summary>
		/// 存储列的类型
		/// </summary>
		IRow* columnType_;

		/// <summary>
		/// 类型名到它的存储名
		/// </summary>
		map<columnTypeEnum, string> typeMap;

	};


	class ISimpleTable
	{
	public:
		ISimpleTable() :rowNum_(0) {
			columnInfo_ = new IColumnInfo(maxColumn_); // 设置列信息
		}
		/// <summary>
		/// 创建表格
		/// </summary>
		/// <param name="tablename">表名</param>
		/// <param name="columnInfo">列信息</param>
		/// <returns></returns>
		virtual int ICreateTable(const char* tablename) = 0;
		virtual int IDeleteTable(const char* tablename) = 0;
		virtual int IAppendOneRow(const char* tableName, IRow row) = 0;// return whitch line insered to, -1 失败
		virtual string IGetOneRowStringByRowID(const char* tableName, int rowID) = 0;
		//virtual int ISearchRow(const bool useIndex) = 0; // 1成功 -1失败 
		//virtual int ISetColumnInfo() = 0;
		virtual IRow getOneRowByRowID(const char* tableName, int rowID, string value) = 0;
		/// <summary>
		/// 加载列信息
		/// </summary>
		//virtual void ILoadColumnInfo() = 0;
		char seprator() {
			return seprator_;
		}
		//virtual int IAddIndex() = 0; // 1 成功 -1 失败
		//virtual int IDeleteIndex(const string indexName) = 0;// 1成功
		//virtual int IGetAllIndex() = 0;
	protected:
		IColumnInfo* columnInfo_;
		vector <IRow> rows_;
		int rowNum_;
		string tableName_;
		static const char seprator_ = '|';
		static const int maxByte_ = 8;
		static const int maxColumn_ = 100;
		static const int info_row_num_ = 2;// 存放信息的列
		static const int byteOfOneRow_ = (maxByte_ + 1) * maxColumn_ + 1;// 分割符+换行符+终止符
		static const int info_size_ = info_row_num_ * byteOfOneRow_; // 存储文件信息的行
	};
}



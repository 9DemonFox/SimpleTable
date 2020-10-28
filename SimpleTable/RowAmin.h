#pragma once
#include "config.h"
#include "ISimpleTable.h"
namespace SimpleTable {
	class RowAmin :IRow { // Ëæ»úÐÐ
	public:
		RowAmin(int rowId,int max_Byte):IRow(rowId,max_Byte) {
		};
	};
}

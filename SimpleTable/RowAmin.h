#pragma once

#include "ISimpleTable.h"
namespace SimpleTable {
	class RowAmin :IRow { // �����
	public:
		RowAmin(int rowId,int max_Byte):IRow(rowId,max_Byte) {
		};
	};
}

#pragma once

#include "ISimpleTable.h"
namespace SimpleTable {
	class RowAmin:IRow{
	public:
		RowAmin(int rowId):IRow(rowId) {};
	};
}


#include "catch.hpp"
#include "TableAmin.h"
#include "Util.h"
#include "ISimpleTable.h"
using namespace SimpleTable;

const char* DATA_PATH_DIR = "data/";
const char* DATA_NAME = "test.db";
const char* DATA_FULL_PATH = "test.db";

TEST_CASE("Test unit Test work", "[single-file]") {
	REQUIRE(1 == 1);
}

TEST_CASE("TableAmin", "[single-file]") {
	ISimpleTable* isimpletable = new TableAmin();
	isimpletable->IDeleteTable(DATA_FULL_PATH);
	REQUIRE(isimpletable->ICreateTable(DATA_FULL_PATH) == 1);// 创建成功
	REQUIRE(isimpletable->ICreateTable(DATA_FULL_PATH) == 0);// 已存在，返回0
	isimpletable->getOneRowByColumn(DATA_FULL_PATH,8,"a");
}

TEST_CASE("IRow RowAmin", "[single-file]") {
	IRow* irow = new IRow(1, 8);
	REQUIRE(irow->setAttrOfIndex(1, "a") == 1);  // 插入 string a
	REQUIRE(irow->getAttrOfIndex(1) == "a"); // 查询为空的返回空

	REQUIRE(irow->setAttrOfIndex(1, "b") == 0);  // update return 0
	REQUIRE(irow->getAttrOfIndex(1) == "b"); // 查询为空的返回空

	IRow* r2 = new IRow(1, 100);
	for (int i = 1; i < 100; i++) {
		r2->setAttrOfIndex(i, Utils::getRandomNByteString(8));
	}
	r2->printData();

}

TEST_CASE("IColumnInfo", "[single-file]") {
	IColumnInfo *iColumnInfo = new IColumnInfo(100);
	iColumnInfo->setSerialColumnNanmeAndRanomType(100, 8);
	iColumnInfo->columnName_->printData();
	iColumnInfo->columnType_->printData();
	REQUIRE(iColumnInfo->columnName_->dataToString().length() == 100 * (8 + 1) + 1);
}

TEST_CASE("Util", "[single-file]") {
	REQUIRE(Utils::num2NSizeString(8, 9) == "00000009");
	//REQUIRE(num2NSizeString(3, 1000) == "");
	REQUIRE(Utils::nSizeString2Num("00000009") == 9);
	REQUIRE(Utils::nSizeString2Num("10000009") == 10000009);

	REQUIRE(Utils::getRandomNByteString(8) != Utils::getRandomNByteString(8)); // 获取的是随机数
	REQUIRE(Utils::getRandomNByteString(8).length() == 8);

	REQUIRE(Utils::paddingToNByteString("int", 8, Utils::POSITION::front) == "     int");
	REQUIRE(Utils::paddingToNByteString("string", 8, Utils::POSITION::front) == "  string");
	REQUIRE(Utils::paddingToNByteString("col_1", 8, Utils::POSITION::front) == "   col_1");

	REQUIRE(Utils::paddingToNByteString("abc", 8, Utils::POSITION::back) == "abc     ");
}
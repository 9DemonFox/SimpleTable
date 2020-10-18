#define CATCH_CONFIG_MAIN

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
}

TEST_CASE("RowAmin", "[single-file]") {
	IRow *irow = new IRow(1);
	irow->setAttrOfIndex(1,IRow::columnType::T_STRING, "a"); // 插入 string a
	pair<IRow::columnType, string> result = irow->getAttrOfIndex(1);
	REQUIRE(result==pair<IRow::columnType,string>(IRow::columnType::T_STRING,"a")); // 获取string a
	REQUIRE(irow->getAttrOfIndex(2) == pair<IRow::columnType, string>(IRow::columnType::T_NULL, "")); // 查询为空的返回空
}

TEST_CASE("Util", "[single-file]") {
	REQUIRE(num2NSizeString(8, 9) == "00000009");
	REQUIRE(num2NSizeString(3, 1000)=="");// 如果位数超过了，返回空
}
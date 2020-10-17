#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "TableAmin.h"
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
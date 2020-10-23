
#include "catch.hpp"
#include "TableAmin.h"
#include "Util.h"
#include "ISimpleTable.h"
#include <thread>
#include "fileHelper.h"
//#define DEBUG
#define p(x) cout<<#x<<":"<<x<<endl
#include <mutex>

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
	REQUIRE(isimpletable->IGetOneRowStringByRowID(DATA_FULL_PATH, 1) == ""); //没有信息

	IRow* r1 = new IRow(0, 100);
	for (int i = 1; i < 100; i++) {
		r1->setAttrOfIndex(i, Utils::getRandomNByteString(8));
	}
	string s0 = r1->dataToString();
	isimpletable->IAppendOneRow(DATA_FULL_PATH, *r1);
	string s1 = isimpletable->IGetOneRowStringByRowID(DATA_FULL_PATH, 1);
	REQUIRE(s0 == s1);
#ifdef DEBUG
	p(s1);
#endif //DEBUG
	IRow* r2 = new IRow(1, 100);
	for (int i = 1; i < 100; i++) {
		r2->setAttrOfIndex(i, Utils::getRandomNByteString(8));
	}
	s0 = r2->dataToString();
	isimpletable->IAppendOneRow(DATA_FULL_PATH, *r2);
	s1 = isimpletable->IGetOneRowStringByRowID(DATA_FULL_PATH, 2);
	REQUIRE(s0 == s1);
#ifdef DEBUG
	p(s1);
#endif
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
#ifdef DEBUG
	r2->printData();
#endif // DEBUG
	IRow* r3 = new IRow(0, 3);
	r3->setDataFromString('|', "a|b|c|\n");
	REQUIRE(r3->dataToString() == "a|b|c|\n");

#ifdef DEBUG
	r3->printData();
#endif // DEBUG
}

TEST_CASE("IColumnInfo", "[single-file]") {
	IColumnInfo* iColumnInfo = new IColumnInfo(100);
	iColumnInfo->setSerialColumnNameAndRanomType(100, 8);
#ifdef DEBUG
	iColumnInfo->columnName_->printData();
	iColumnInfo->columnType_->printData();
#endif // DEBUG
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

TEST_CASE("FileHelper", "[single - file]") {
	//vector<thread> threads;
	//remove("testThreads.txt");

	//FILE* file = fopen("testThreads.txt", "w");
	//fclose(file);
	//mutex mtx;
	//int i = 0;
	//thread p1 = thread(FileHelper::writeFile, &mtx, &i,1);
	//thread p2 = thread(FileHelper::writeFile, &mtx, &i,2);
	//p1.join();
	//p2.join();
	//file = fopen("testThreads.txt", "r");
	//char* buff = (char*)malloc(sizeof(char) * 100);
	//fgets(buff, 100, file);
	//cout << "file:" << buff << endl;

	FileHandler fileHandler = FileHandler::getInstance();
	int i = 5;
	fileHandler.printNum(&i);

}
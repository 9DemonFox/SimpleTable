
#include "catch.hpp"
#include "TableAmin.h"
#include "Util.h"
#include "ISimpleTable.h"
#include <thread>
#include "fileHelper.h"
#include <cstring>
#include "serialization.h"
//#define DEBUG
#define p(x) cout<<#x<<":"<<x<<endl
#include <mutex>
#include "IndexAmin.h"
#include <string>
#include <time.h>
using namespace SimpleTable;
using namespace stl_serialization;

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

	// 重新创建文件
	isimpletable->IDeleteTable(DATA_FULL_PATH);
	REQUIRE(isimpletable->ICreateTable(DATA_FULL_PATH) == 1);// 创建成功

	// -1和0 模拟columninfo
	for (int k = 1; k < 1000; k++) {
		IRow* r_temp = new IRow(k, 8);
		for (int i = 1; i < 8; i++) {
			r_temp->setAttrOfIndex(i, Utils::getRandomNByteString(8));
		}
		if (k == 5) {
			r_temp->setAttrOfIndex(3, "testrow5");
		}
		isimpletable->IAppendOneRow(DATA_FULL_PATH, *r_temp);
	}

	auto rows = isimpletable->IGetAllRows(DATA_FULL_PATH);
	REQUIRE(rows.size() == 999);
	// 测试得到某些列
	FileHandler* fileHandler = FileHandler::getInstance();
	auto r = isimpletable->IGetProjectedColumns(DATA_FULL_PATH, *new vector<string>{ "  row_id","col_0001" }, *fileHandler);
	REQUIRE(r.getColInfo().columnName_.getAttrOfIndex(0) == "  row_id");
	REQUIRE(r.getColInfo().columnName_.getAttrOfIndex(1) == "col_0001");
	//REQUIRE(r.getColInfo().columnName_->getAttrOfIndex(2) == "col_0005");

	// 测试查询某行
	auto search_result = isimpletable->ISearchRows(DATA_FULL_PATH, "col_0003", "=", "testrow5");
	auto search_rows = search_result.getRows()[0];
	REQUIRE(search_rows.getAttrOfIndex(0) == "5");// 插入到第6行(从0开始)
	REQUIRE(search_rows.getAttrOfIndex(3) == "testrow5");

	IndexRBTree* indexRBTress = new IndexRBTree();

	indexRBTress->init_map_serilization(r);
}


// 测试索引
TEST_CASE("IndexAmin", "[single-file]") {
	string indexTestFile = "testIndexTestFile.db";
	if (Utils::existsFile(indexTestFile))remove(indexTestFile.c_str());
	ISimpleTable* isimpletable = new TableAmin();
	isimpletable->setTableName(indexTestFile);
	// 包含了默认的列名
	REQUIRE(isimpletable->ICreateTable(indexTestFile.c_str()) == 1);// 创建成功
	for (int k = 0; k < 10000; k++) {
		IRow* r_temp = new IRow(k + 1, 8);
		for (int i = 1; i < 8; i++) {
			r_temp->setAttrOfIndex(i, Utils::getRandomNByteString(8));
		}
		r_temp->setAttrOfIndex(2, "row_" + Utils::num2NSizeString(4, k));
		isimpletable->IAppendOneRow(indexTestFile.c_str(), *r_temp);
	} // 创建10000行表
	isimpletable->ICreateIndex("col_0002");
	clock_t start = clock();
	auto r = isimpletable->ISearchRows(indexTestFile.c_str(), "col_0002", "=", "row_0002", true);
	printf("use Index time: %f \n",(double)(clock() - start)/CLOCKS_PER_SEC);
	start = clock();
	r = isimpletable->ISearchRows(indexTestFile.c_str(), "col_0002", "=", "row_0002", false);
	printf("not use Index time: %f", (double)(clock() - start)/CLOCKS_PER_SEC);

	cout << "\n\n";
	r.getRows()[0].printData();

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
	REQUIRE(iColumnInfo->columnName_.dataToString().length() == 100 * (8 + 1) + 1);

}


TEST_CASE("Utils", "[single-file]") {
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

	string test_existsFile = "test_existsFile";
	REQUIRE(Utils::existsFile(test_existsFile) == false);
	fopen(test_existsFile.c_str(), "w+");
	REQUIRE(Utils::existsFile(test_existsFile) == true);
	remove(test_existsFile.c_str());
}

// 测试序列化
TEST_CASE("Serialization", "[single-file]") {
	int _size = 10;
	std::ostringstream _ost;
	MapSerialization<int, vector<int>> ms_src;
	int t;
	for (int i = 0; i < _size; i++) { // 构造数据 每个key 对应 key个元素的vector
		vector<int> temp;
		for (t = 0; t <= i; t++) {
			temp.push_back(t);
		}
		ms_src[i] = temp;
	}
	ms_src.serialization(_ost, "test_serialization.bin"); //  oa  << _ost
	MapSerialization<int, vector<int>> ms_des;
	std::istringstream ist(_ost.str());// initial from _ost
	// ms_des.unserialization(ist);
	ms_des.unserialization("test_serialization.bin");
	REQUIRE(ms_src == ms_des);
	for (std::map<int, vector<int>>::iterator it = ms_des.begin(); it != ms_des.end(); it++)
	{
		int k = it->first;
		for (int k = 0; k <= it->first; k++)
		{
			cout << it->second[k];
		}
		cout << endl;
	}
}

// 测试多线程
TEST_CASE("threads", "[single-file]") {
	vector<thread> threads;
	const char* filePath = "testThreads.txt";
	remove(filePath);
	mutex mtx;
	int i = 0;
	thread p1 = thread(FileHelper::writeFile, &mtx, &i, filePath, 1);
	thread p2 = thread(FileHelper::writeFile, &mtx, &i, filePath, 2);
	p1.join();
	p2.join();
	FILE* file = fopen("testThreads.txt", "r");
	char* buff = (char*)malloc(sizeof(char) * 64);
	fgets(buff, 100, file);
#ifdef DEBUG

#endif // DEBUG
	cout << "file:" << buff << endl;
	REQUIRE(strcmp(buff, "0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnop") == 0);

}


TEST_CASE("FileHandler", "single-file") {
	int i = 100;
	FileHandler* fileHandler = FileHandler::getInstance();
}
#include "TableAmin.h"
#include "RowAmin.h"

namespace SimpleTable{


	int TableAmin::ICreateTable(const char* tablename)
	{
		FILE* file;
		try{
			file=fopen(tablename,"r");// 判断文件是否存在 只读方式打开
			if (file != NULL) {
				cout << "table: "<<tablename<<" already exist\n";
				return 0;
			}
			else
			{
				file = fopen(tablename, "w+");
				if (file == NULL) {
					return -1;// 创建失败
				}
				else {
					fclose(file);
					cout << "table: " << tablename << " is created\n";
					return 1;
				}
			}
		}catch(exception &e){
			cout << e.what();
			return -1;
		}
	}

	int TableAmin::IDeleteTable(const char* tablename) {
		try
		{
			if (std::remove(tablename) == 0) {
				cout << "table: "<<tablename<<" is deleted\n";
			}
			else {
				cout << "failed to delete the tabel " <<tablename<<"\n";
				return 0;
			}
		}
		catch (const std::exception& e)
		{
			cout << e.what();
			return -1;
		}

	}

	//int TableAmin::IAppendOneRow(const char* tableName,RowAmin row) {
	//	FILE *file=fopen(tableName,"a+");//原来的EOF保留
	//	if (ftell(file) == EOF) {

	//	}
	//	string s = to_string(row.rowId_);
	//	int len = s.length();
	//	int i = 0;

	//	for (int i = 0;i < 8;i++) {
	//		
	//	}
	//	return 1;
	//}
}


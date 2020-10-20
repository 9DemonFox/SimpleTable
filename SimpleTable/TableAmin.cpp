#include "TableAmin.h"
#include "RowAmin.h"

namespace SimpleTable { // Ϊ��˳����ʵ���Ҫ


	int TableAmin::ICreateTable(const char* tablename)
	{
		ISetColumnInfo();
		FILE* file;
		try {
			file = fopen(tablename, "r");// �ж��ļ��Ƿ���� ֻ����ʽ��
			if (file != NULL) {
				cout << "table: " << tablename << " already exist\n";
				return 0;
			}
			else
			{
				file = fopen(tablename, "w+");
				if (file == NULL) {
					return -1;// ����ʧ��
				}
				else {
					fseek(file, 0, SEEK_END);
					string ctype = columnInfo_->columnType_->dataToString();
					string cname = columnInfo_->columnName_->dataToString();
					fputs(ctype.c_str(), file);
					fputs(cname.c_str(), file);
					fclose(file);
					cout << "table: " << tablename << " is created\n";
					return 1;
				}
			}
		}
		catch (exception& e) {
			cout << e.what();
			return -1;
		}
	}


	int TableAmin::IDeleteTable(const char* tablename) {
		try
		{
			if (std::remove(tablename) == 0) {
				cout << "table: " << tablename << " is deleted\n";
			}
			else {
				cout << "failed to delete the tabel " << tablename << "\n";
				return 0;
			}
		}
		catch (const std::exception& e)
		{
			cout << e.what();
			return -1;
		}

	}

	/// <summary>
	/// ��������Ϣ
	/// </summary>
	/// <returns></returns>
	int TableAmin::ISetColumnInfo()
	{
		this->columnInfo_->setSerialColumnNanmeAndRanomType(maxColumn_, maxByte_);
		return 1;
	}

	int TableAmin::IAppendOneRow(const char* tableName, IRow row) {
		FILE* file = fopen(tableName, "a+");//ԭ����EOF����
		// TODO �̰߳�ȫ
		fseek(file, 0, SEEK_END);
		return fputs(row.dataToString().c_str(), file);
	}

	string TableAmin::IGetOneRowByIndex(const char* tableName, int index)
	{
		return string();
	}

	IRow TableAmin::getOneRowByColumn(const char* tableName,int columnIndex, string value)
	{
		FILE* file;
		file = fopen(tableName, "r");// �ж��ļ��Ƿ���� ֻ����ʽ��
		int lineCount = 0;
		int maxByte = 0;
		if (file != NULL) {
			while (fgetc(file) != '\n') {
				lineCount++;
			}
			fseek(file, 0, SEEK_SET);
			while (fgetc(file) != seprator_) { // ��һ���ָ���Ϊ��󳤶�
				maxByte++;
			}
			lineCount++;// ���з�
			cout << "lineCount: " << lineCount << endl;
			cout << "maxByte; " << maxByte << endl;
		}
		else {
			throw "table not exist";
		}
		return IRow(1, 100);
	}

}
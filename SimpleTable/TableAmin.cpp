#include "TableAmin.h"
#include "RowAmin.h"
#include <errno.h>
//#define DEBUG
#define pr(x) cout<<#x<<" = "<<x<<endl
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
		this->columnInfo_->setSerialColumnNameAndRanomType(maxColumn_, maxByte_);
		return 1;
	}

	int TableAmin::IAppendOneRow(const char* tableName, IRow row) {
		FILE* file = fopen(tableName, "a+");
		int file_position = fseek(file, 0, SEEK_END);
		// TODO �̰߳�ȫ
#ifdef  DEBUG
		pr(file_position);
#endif //  DEBUG
		string s = Utils::paddingToNByteString(row.dataToString(), byteOfOneRow_, Utils::POSITION::back); // '\0'
#ifdef DEBUG
		const char* buf = s.c_str();
#endif // DEBUG
		fputs(s.c_str(), file);
		fclose(file);
		return 1;
	}

	string TableAmin::IGetOneRowStringByRowID(const char* tableName, int rowID)
	{
		if (rowID <= 0)
		{
			throw "rowID must over than 0";
		}

		FILE* file;
		file = fopen(tableName, "r");// �ж��ļ��Ƿ���� ֻ����ʽ��
		int lineCount = 0;
		int maxByte = 0;
		fseek(file, info_size_, SEEK_SET);
		if (file != NULL) {
			if (fgetc(file) == EOF) { // û���ļ���Ϣ
				return "";
			}
			else {
				fseek(file, -1, SEEK_CUR); // fgetc() �ƶ���һ��������

				fseek(file, byteOfOneRow_ * (rowID - 1), SEEK_CUR);
#ifdef DEBUG
				cout << "position:" << ftell(file);
#endif // DEBUG

				if (char* buffer = (char*)malloc(sizeof(char) * byteOfOneRow_)) {
					fgets(buffer, byteOfOneRow_, file);
					fclose(file);
					return buffer;
				}
			}
		}
		else {
			throw "table not exist";
		}

	}

	IRow TableAmin::getOneRowByRowID(const char* tableName, int rowID, string value)
	{
		return IRow(1, 100);
	}

}
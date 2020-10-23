#include <iostream>
//#include "TableAmin.h"
//#include "ISimpleTable.h"
#include<vector>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <map>
//#define DEBUG
using namespace std;
//using namespace SimpleTable;

const int MAX_COLUMN = 100;
const int MAX_BYTE = 8;
const int MAX_ROW = 1000000;

char* num2string(int id) {
	char* rowId = (char*)malloc(sizeof(char) * (MAX_BYTE + 1));
	int tDigit;
	for (int i = 0; i < MAX_BYTE; i++) {
		tDigit = pow(10, MAX_BYTE - 1 - i);
		if (id < tDigit) {
			rowId[i] = '0';
		}
		else {
			rowId[i] = (char)(id / tDigit + 48);
			id = id % tDigit;
		}
	}
	rowId[MAX_BYTE] = '\0';
	return rowId;
}

int main()
{
	class Row {
	public:
		Row(int id) {
			/// <summary>
			/// ��ʼ��
			/// </summary>
			/// <returns></returns>
			if (id > MAX_ROW) {
				cout << "�����ﵽ����:" << MAX_ROW;
				return;
			}
			else {
				strcpy(rowId, num2string(id));
			}
			initData();
			set_data();
			get_random_row();
		}

		~Row() {
			free(rowId);
			free(data);
		}

		void initData() {
			int rowLength = MAX_BYTE * MAX_COLUMN + MAX_COLUMN - 1 + 1;//�����ָ���MAX_COLUMN - 1�ͻ��з�+1
			char* rand_row = (char*)malloc(sizeof(char) * rowLength);
			if (rand_row == 0) {
				throw("�ڴ����ʧ��");
			}
			for (int i = 0; i < MAX_COLUMN; i++) {
				data[i] = (char*)malloc(sizeof(char) * (MAX_BYTE + 1));
				if (data[i] == 0) {
					throw("�ڴ����ʧ��");
				}
			}
		}

		int setAttrib(int index, char* value) {
			/// <summary>
			/// ��index������valueֵ
			/// </summary>
			/// <returns></returns>
			if (index >= MAX_COLUMN) {
				return -1;//Խ��
			}
			else {
				strncpy(data[index], value, MAX_BYTE);
				cout << *data[index];
				return 1;
			}
		}

		void get_random_row() {
			int rowLength = MAX_BYTE * MAX_COLUMN + MAX_COLUMN - 1 + 1;//�����ָ���MAX_COLUMN - 1�ͻ��з�+1
			if (char* rand_row = (char*)malloc(sizeof(char) * rowLength)) {
				memset(rand_row, '\0', rowLength);
				strncat(rand_row, rowId, MAX_BYTE);
				strncat(rand_row, "|", 1);
				for (int i = 1; i < MAX_COLUMN; i++) {
					strncat(rand_row, data[i - 1], MAX_BYTE);
					strncat(rand_row, "|", 1);
				}
				strncat(rand_row, "\n", 1);
#ifdef DEBUG
				cout << rand_row;
#endif // DEBUG
			}
			else {
				throw("�ڴ����ʧ��");
			}

		}

		void static get_random_attr(char*& randAttr) {
			/// <summary>
			/// ��ȡ8λ�������
			/// </summary>
			/// <returns></returns>
			char tChar;
			unsigned int seed = time(NULL);// ÿ��ִ��̫����������Զ�һ��
			srand(seed + rand());
			int tCharInt;
			for (int i = 0; i < MAX_BYTE; i++) {
				tCharInt = rand() % 27 + 97;
				tChar = tCharInt;//������\,����32-126�Ŀɼ��ַ� һ���ԣ�rand() % (b-a+1)+ a ;    �ͱ�ʾ  a~b ֮���һ���������,���ܰ������� "|"124 ��ȡ123-32
				randAttr[i] = tChar;
			}
			randAttr[MAX_COLUMN] = '\0';
			return;
		}

		void set_data() {
			char* attr = (char*)malloc(sizeof(char) * (MAX_BYTE + 1));
			if (attr != 0) {
				for (int i = 0; i < MAX_COLUMN; i++) {
					get_random_attr(attr);
					strcpy(data[i], attr);
					data[i][MAX_BYTE] = '\0';
				}
				free(attr);
			}
			else {
				throw("�ڴ����ʧ��");
			}
			//for (int i = 1;i <= MAX_COLUMN;i++) {
			//	cout << data[i];
			//}
			//cout << "\nend\n";
		}

		char rowId[MAX_BYTE + 1]; // ��һ�����к�

		char* data[MAX_COLUMN - 1];// 7+1=8, ��һ�����к�
	};

	class Columns {
	public:
		Columns(int columnNum = 100) {
			columnNum_ = columnNum;
			column_string = "";
			setSerialColumnName();
			column2string();
		};
	public:
		/// <summary>
		/// ��ȡ00000001 00000002 ��ʽ������(�൱�ڳ�ʼ����
		/// ��ҵĬ��100��
		/// </summary>
		/// <returns></returns>
		int setSerialColumnName() {

			for (int i = 0; i < MAX_COLUMN; i++) {//tDigit ���� 1��2 ת��ΪMAX_BYTES���ַ���
				columns_.push_back(num2string(i));
			}
			return 1;
		}

		int column2string() {
			vector<string>::iterator iter;
			iter = columns_.begin();
			column_string = "";
			while (iter != columns_.end()) {
				column_string += *iter + "|";// ָ���ָ��
				iter++;
			}
			column_string += "\n";
#ifdef DEBUG
			cout << column_string;
#endif // DEBUG
			return 1;
		}

		vector<string> columns_;

		string column_string;

		int columnNum_;
	};

	class Table {
	public:
		Table(string tableName) {
			tableName_ = tableName;
			rowNum_ = 0;
		}

		int rowNum_;
		string tableName_;
		//Columns Column(100);
		vector <Row> Rows;
		int size;
		string static Row2Stringline(Row row) {
			const int NumOfBytes = MAX_COLUMN * (MAX_BYTE + 1) + 1; // Byte��Ŀ
			char line[NumOfBytes];//8*8+�ָ���+���з�+��ֹ����
			strcat(line, row.rowId);
			for (int i = 0; i < MAX_COLUMN - 1; i++) {
				strcat(line, "|");
				strcat(line, row.data[i]);
			}
			strcat(line, "\n");
			cout << line;
			return line;
		}
	};


	std::cout << "Hello World!\n";
	//ISimpleTable* isimpletable = new TableAmin();
	//isimpletable->ICreateTable("test.db");
	//isimpletable->IDeleteTable("test.db");
	const char* tableName = "test.db";
	FILE* file = fopen(tableName, "a+");//ԭ����EOF����
	fseek(file, 0, SEEK_END);//8*8+8
	//cout << ftell(file);
	//string s = to_string(row.rowId);
	//int len = s.length();
	//int i = 0;

	//for (int i = 0;i < 8;i++) {

	//}
	//return 1;
	Row row(100);
	Columns* c = new Columns();
	//char *attr=(char*)malloc(sizeof(char)*(MAX_BYTES+1));

	//cout<<attr;
	map<int, string>data;
	data[0] = "0";
	string a = data[1];
	cout << "data[0]=" << data[1];
	

	while (true)
	{
	}
}


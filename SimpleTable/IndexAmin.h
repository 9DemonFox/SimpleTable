#include "ISimpleTable.h"
#include<vector>
#include<map>
#include "config.h"
#include "serialization.h"
using namespace stl_serialization;
using namespace std;
using namespace SimpleTable;
/// <summary>
/// �����ʵ������
/// </summary>
class IndexRBTree :public IIndex {
public:

	IndexRBTree() {}

	/// <summary>
	/// �ж��Ƿ��иñ���е�����
	/// </summary>
	/// <returns></returns>
	bool IHasIndex(string tableName, string tableIndex);

	int init_map_serilization(RowsWithInfo rowsWithInfo);

	int ICreateIndex(string tableName, string columnName, ISimpleTable* isimpleTable, FileHandler* fileHandler);


	/// <summary>
	/// 
	/// </summary>
	/// <param name="tableName"></param>
	/// <param name="columnName"></param>
	/// <param name="op"></param>
	/// <param name="parameter"></param>
	/// <param name="result"></param>
	/// <returns>-1 ��index 0�޽�� ���� �����Ŀ</returns>
	int ISearchRows(string tableName, string columnName, string op, string parameter, vector<int>* result);

private:
	MapSerialization<string, vector<int>> map_seri;// �ļ����л���ͨ��

};
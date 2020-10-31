#include "ISimpleTable.h"
#include<vector>
#include<map>
#include "config.h"
#include "serialization.h"
using namespace stl_serialization;
using namespace std;
using namespace SimpleTable;
/// <summary>
/// 红黑树实现索引
/// </summary>
class IndexRBTree :public IIndex {
public:

	IndexRBTree() {}

	/// <summary>
	/// 判断是否有该表该列的索引
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
	/// <returns>-1 无index 0无结果 正数 结果数目</returns>
	int ISearchRows(string tableName, string columnName, string op, string parameter, vector<int>* result);

private:
	MapSerialization<string, vector<int>> map_seri;// 文件序列化的通道

};
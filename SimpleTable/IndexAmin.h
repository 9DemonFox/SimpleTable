#include "ISimpleTable.h"
#include<vector>
#include<map>
using namespace std;
using namespace SimpleTable;
/// <summary>
/// 红黑树实现索引
/// </summary>
class IndexRBTress: IIndex<map<string,vector<int> > > {

	/// <summary>
	/// 判断是否有该表该列的索引
	/// </summary>
	/// <returns></returns>
	bool IHasIndex(string tableName, string tableIndex);

	///// <summary>
	///// 判断索引是否是最新
	///// </summary>
	///// <returns></returns>
	//bool IIsUpToDate();

	/// <summary>
	/// 创建索引
	/// </summary>
	/// <param name="tableName"></param>
	/// <param name="colName"></param>
	/// <returns></returns>
	bool ICreatIndex(string tableName, string colName);

	///// <summary>
	///// 更新索引
	///// </summary>
	///// <param name="tableName"></param>
	///// <param name="colName"></param>
	///// <returns></returns>
	//bool IUpDateIndex(string tableName, string colName);

	///// <summary>
	///// 获取索引
	///// </summary>
	///// <returns></returns>
	//T IGetIndex();
};
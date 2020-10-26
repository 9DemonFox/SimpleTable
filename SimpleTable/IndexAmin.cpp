#include "IndexAmin.h"
#include <fstream>
#include "Util.h"


bool IndexRBTress::IHasIndex(string tableName, string tableIndex)
{
	return Utils::existsFile(tableName) ? Utils::existsFile(tableName + tableIndex) : false;
}

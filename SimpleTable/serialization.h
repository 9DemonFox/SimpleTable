#ifndef STLSERIALIZATION_SERIALIZATION_H
#define STLSERIALIZATION_SERIALIZATION_H
#include "config.h"
#include <string>
#include <sstream>
#include <fstream>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/vector.hpp>
using namespace std;


namespace stl_serialization
{

	template <class T>
	class Serialization : public T
	{
	public:
		void serialization(std::ostringstream& ostream, const char* filePath)
		{
			boost::archive::binary_oarchive oa(ostream);
			oa << *this;
			fstream file;
			file.open(filePath, ios::binary | ios::out);
			file << ostream.str(); // 将数据写入文件
			file.close();
		}

		void serialization(const char* filePath)
		{
			std::ostringstream ostream;
			boost::archive::binary_oarchive oa(ostream);
			oa << *this;
			fstream file;
			file.open(filePath, ios::binary | ios::out);
			file << ostream.str(); // 将数据写入文件
			file.close();
		}

		void unserialization(std::istringstream& istream)
		{
			boost::archive::binary_iarchive ia(istream);
			ia >> *this;
		}

		void unserialization(const char* filePath)
		{
			ifstream file(filePath, ifstream::in);
			ostringstream ost;
			ost << file.rdbuf();
			istringstream istream(ost.str());
			boost::archive::binary_iarchive ia(istream);
			ia >> *this; // 反序列化到当前文件
		}

	private:
		friend class boost::serialization::access;

		template <class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& boost::serialization::base_object<T>(*this);
		}
	};


	template <class T1, class T2>
	class MapSerialization : public Serialization<map<T1, T2> >
	{
	};

} // namespace stl_serialization





#endif // STLSERIALIZATION_SERIALIZATION_H
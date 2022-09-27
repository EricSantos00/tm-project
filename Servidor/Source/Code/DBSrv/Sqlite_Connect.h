
#ifndef __SQLITECONNECT__
#define __SQLITECONNECT__
#include <string>
#include <iostream>
#include <stdio.h>
#include <sqlite3.h>
#include "../Basedef.h"

using namespace std;
namespace SqlDB {

	class nSqlDB
	{


		public:

			static int openDB();
			static int closeDB();
			static int createDB();
			static int openTable();
			static int closeTable();
			static int insertData();
			static int updateData();
			static int deleteData();


		private:

	};


}

#endif

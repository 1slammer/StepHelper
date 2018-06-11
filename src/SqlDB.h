#include <stdio.h>
#include <sqlite3.h> 
#include <string>
#include <iostream>
#include <vector>

using namespace std;
using Record = std::vector<std::string>;
using Records = std::vector<Record>;

class SqlDB
{
public:
   void OpenDB();
   void CloseDB();
   void CreateFourthStepTableIfNotExists();
   Records RetrieveFourthStepInfo();
   void sql_stmt(const char* stmt);
   Records select_stmt(const char* stmt);
private:
   sqlite3 *db;
   
};

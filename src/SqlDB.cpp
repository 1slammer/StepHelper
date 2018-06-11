#include "SqlDB.h"

using namespace std;

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for(i=0; i<argc; i++)
	{
		cout<<azColName[i]<<" = " << (argv[i] ? argv[i] : "NULL")<<"\n";
	}
	cout<<"\n";
	return 0;
}


int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
  Records* records = static_cast<Records*>(p_data);
  try {
    records->emplace_back(p_fields, p_fields + num_fields);
  }
  catch (...) {
    // abort select on failure, don't let exception propogate thru sqlite3 call-stack
    return 1;
  }
  return 0;
}

Records SqlDB::select_stmt(const char* stmt)
{
  Records records;  
  char *errmsg;
  int ret = sqlite3_exec(db, stmt, select_callback, &records, &errmsg);
  if (ret != SQLITE_OK) {
    std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
  }
  else {
    std::cerr << records.size() << " records returned.\n";
  }

  return records;
}

void SqlDB::sql_stmt(const char* stmt)
{
  char *errmsg;
  int ret = sqlite3_exec(db, stmt, 0, 0, &errmsg);
  if (ret != SQLITE_OK) {
    std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
  }
}

void SqlDB::OpenDB() 
{
   char *zErrMsg = 0;
   int rc;
   rc = sqlite3_open("twelve_steps.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   } else {
      fprintf(stderr, "Opened database successfully\n");
   }
}

void SqlDB::CloseDB() 
{
	cout << "Closed Database" << "\n";
    sqlite3_close(db);
}

void SqlDB::CreateFourthStepTableIfNotExists() 
{
	int rc;
    char *zErrMsg = 0;
    string sql = "CREATE TABLE IF NOT EXISTS FOURTHSTEPTABLE";
	string sql2 = " (NAME VARCHAR(30), CAUSE VARCHAR(2000), MY_PART VARCHAR(2000), THREAT VARCHAR(2000))";
	sql = sql + sql2;
	const char *sql_array = sql.c_str();
	rc = sqlite3_exec(db, sql_array, callback, 0, &zErrMsg);
	if( rc!=SQLITE_OK )
	{
		cout<<"SQL error: "<<sqlite3_errmsg(db)<<"\n";
		sqlite3_free(zErrMsg);
	}
	else {
		cout << "Fourth Step Table either exists or was created." << "\n";
	}
}

Records SqlDB::RetrieveFourthStepInfo() 
{
 Records records = select_stmt("SELECT * FROM FOURTHSTEPTABLE");
 return records;
}


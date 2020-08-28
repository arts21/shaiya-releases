#include "pch.h"
#include "database.h"

CDataBase g_DBobj;

//the main function
DWORD __stdcall DBConn(void*)
{
	//checks the database connection
	if (!g_DBobj.LinkDataBase()) return 0;
	return 0;
}

#pragma once

#include "sqlite3.h"

#include "ofxSqliteStreamConstants.h"

OFX_SQLITE_STREAM_BEGIN_NAMESPACE

class Session
{
public:
	
	Session() : db(NULL) {}
	virtual ~Session() { close(); }
	
	virtual void close()
	{
		if (db)
		{
			sqlite3_close(db);
			db = NULL;
		}
	}
	
	bool isOpend() const { return db; }
	
protected:
	
	sqlite3* db;
	
	void exec(const char* sql)
	{
		char *err = NULL;
		sqlite3_exec(db, sql, 0, 0, &err);
		
		if (err != NULL)
		{
			ofLogError("SessionWriter") << err;
			sqlite3_free(err);
		}
	}
};

OFX_SQLITE_STREAM_END_NAMESPACE
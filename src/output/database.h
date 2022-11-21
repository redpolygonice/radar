#ifndef DATABASE_H
#define DATABASE_H

#include "common/types.h"
#include "common/frame.h"

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>

// Sqlite database
class Database
{
private:
	QSqlDatabase _db;

	const QString dbName = "data.db";
	const QString dbHostName = "database";
	const QString tableName = "coordinates";

public:
	Database();
	~Database();

public:
	bool open();
	void close();
	bool isOpen() const { return _db.isOpen(); }
	bool add(const Frame &frame);
	bool add(const FrameList &frames);
	bool remove(const Frame &frame);

private:
	bool createTables();
	bool insertRecord(QSqlQuery &query, const Frame &frame);
};

#endif // DATABASE_H

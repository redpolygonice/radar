#include "database.h"

#include <QVariant>

Database::Database()
{
}

Database::~Database()
{
}

bool Database::open()
{
	_db = QSqlDatabase::addDatabase("QSQLITE");
	_db.setHostName(dbHostName);
	_db.setDatabaseName(dbName);

	if (_db.open())
	{
		if (_db.tables().empty())
			return createTables();
	}
	else
		return false;

	return true;
}

bool Database::createTables()
{
	QSqlQuery query(_db);
	if (!query.exec("CREATE TABLE " + tableName + " ("
					"id INTEGER NOT NULL, "
					"state INTEGER NOT NULL,"
					"ts DATETIME NOT NULL,"
					"x INTEGER NOT NULL,"
					"y INTEGER NOT NULL)"))
	{
		std::cout << query.lastError().text().toStdString() << std::endl;
		return false;
	}

	return true;
}

void Database::close()
{
	_db.close();
}

bool Database::add(const Frame &frame)
{
	QSqlQuery query(_db);
	query.prepare("INSERT INTO " + tableName + " (id, state, ts, x, y)"
					"VALUES (:id, :state, :ts, :x, :y)");

	return insertRecord(query, frame);
}

bool Database::add(const FrameList &frames)
{
	QSqlQuery query(_db);
	query.prepare("INSERT INTO " + tableName + " (id, state, ts, x, y)"
					"VALUES (:id, :state, :ts, :x, :y)");

	for (const Frame &frame : frames)
		insertRecord(query, frame);
	return true;
}

bool Database::remove(const Frame &frame)
{
	return true;
}

bool Database::insertRecord(QSqlQuery &query, const Frame &frame)
{
	query.bindValue(":id", QVariant(frame.id()));
	query.bindValue(":state", QVariant(frame.state()));
	query.bindValue(":ts", QVariant::fromValue(frame.ts()));
	query.bindValue(":x", QVariant(frame.x()));
	query.bindValue(":y", QVariant(frame.y()));

	if (!query.exec())
	{
		std::cout << query.lastError().text().toStdString() << std::endl;
		return false;
	}

	return true;
}

/*
 * File: Database.h
 * Part of M-S Lab project
 * Description: Database class. All the data will be stored here.
 */

#ifndef _DATABASE_H
#define _DATABASE_H

#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "Column.h"
#include "DatabaseIO.h"

class Database {

	friend class DatabaseIO;

	std::vector<Column*> table;

	static DatabaseIO io;

public:

	Database();
	~Database();

	void clear();

	Column* newColumn(const char name[], Column::Type type);
	void addColumn(Column *column);

	Database* random(int n) const;

	void print() const;

	void save(const char filename[]) const;
	void load(const char filename[]);

}; // class Database

#endif // _DATABASE_H
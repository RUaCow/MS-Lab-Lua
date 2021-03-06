/*
 * File: Database.h
 * Part of M-S Lab project
 * Description: Database class. All the data will be stored here.
 */

#ifndef _DATABASE_H
#define _DATABASE_H

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
#include "Column.h"

class Database {

	std::vector<std::pair<std::string, Column*> > table;

public:

	Database();
	~Database();

	Database(const Database &db); // Copy constructor
	void operator= (const Database &db);

	void clear();

	Column* newColumn(const char name[]);
	void addColumn(const char name[], Column *column);

	Database random(int n) const;

	void print() const;

	void save(const std::string &filename) const;
	void load(const std::string &filename);

	// Diagram functions
	void drawPie(int width = 400, int height = 300) const;

private:

	void saveExcel(const std::string &filename) const;
	void loadExcel(const std::string &filename);

}; // class Database

#endif // _DATABASE_H

/*
 * File: DatabaseIO.h
 * Part of M-S Lab project
 * Description: Database utility functions to save and load from different file formats.
 */

#ifndef _ULTRA_DATABASEIO_H
#define _ULTRA_DATABASEIO_H

#include <cstdio>

class Database;

class DatabaseIO {

public:

	DatabaseIO();
	~DatabaseIO();

	void saveText(const char filename[], const Database *db) const;
	void saveEncrypted(const char filename[], const Database *db) const;

	void loadText(const char filename[], Database *db) const;
	void loadEncrypted(const char filename[], Database *db) const;

}; // class DatabaseIO

#endif // _ULTRA_DATABASEIO_H

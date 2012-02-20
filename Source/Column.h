/*
 * File: Column.h
 * Part of M-S Lab project
 * Description: This class holds one column of the database information.
 */

#ifndef _COLUMN_H
#define _COLUMN_H

#include <iostream>
#include <string>
#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>
#include <vector>
#include "Variable.h"

class Database;
class DatabaseIO;

class Column {

	friend class Database;
	friend class DatabaseIO;

public:
	
	enum Type {
		VAR_STRING = 0,
		VAR_INTEGER = 1,
		VAR_REAL = 2
	};

private:
	
	Type type;
	char name[MAX_STR_LEN];
	std::vector<Variable> data;

public:

	Column(const char name[], Type type);
	~Column();

	void push_back(const Variable &var);
	void push(int size, luabind::object const& lua_arr);

	bool isString() const;
	bool isInteger() const;
	bool isReal() const;

	void print() const;

}; // class Column

#endif // _COLUMN_H

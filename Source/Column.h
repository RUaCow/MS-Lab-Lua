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

class Column {

	std::vector<std::string> data;

public:

	Column();
	~Column();

	void push_back(const std::string &var);
	void push(int size, luabind::object const& lua_arr);

	void print() const;

	std::string at(const int index) const;
	unsigned getSize() const;

}; // class Column

#endif // _COLUMN_H

/*
 * File: Session.h
 * Part of M-S Lab project
 * Description: Every session has its own lua status.
 */

#ifndef _SESSION_H
#define _SESSION_H

#include <iostream>
#include <luabind/lua_include.hpp>
#include <luabind/luabind.hpp>
#include "Database.h"

void echo(const char str[]);

class Session {

	lua_State *state;

public:

	Session();
	~Session();

	void doString(const char str[]);
	void doFile(const char filename[]);

	void start();
	void close();

}; // class Session

#endif // _SESSION_H

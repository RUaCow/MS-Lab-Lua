/*
 * File: Variable.h
 * Part of M-S Lab project
 * Description: This class holds one variable in string format.
 */

#ifndef _VARIABLE_H
#define _VARIABLE_H

#include <cstdlib>
#include <cstring>
#include <cstdio>

const int MAX_STR_LEN = 256;

class Variable {

	char ptr[MAX_STR_LEN];

public:

	Variable();
	Variable(const char value[]);
	Variable(int value);
	Variable(float value);

	~Variable();

	void clean();

	const char* toString() const;
	int toInteger() const;
	float toReal() const;

}; // class Variable

#endif // _VARIABLE_H

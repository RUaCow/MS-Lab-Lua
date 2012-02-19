/*
 * File: Console.h
 * Part of M-S Lab project
 * Description: Application console window
 */

#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <wx/wx.h>

class Console : public wxTextCtrl {

	static Console *singleton_ptr;

public:

	Console(wxWindow *parent);
	~Console();

	static Console& GetSingleton();
	static Console* GetSingletonPtr();

}; // class Console

#endif // _CONSOLE_H

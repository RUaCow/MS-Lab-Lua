/*
 * File: Console.h
 * Part of M-S Lab project
 * Description: Application console window
 */

#ifndef _CONSOLE_H
#define _CONSOLE_H

#include "Singleton.h"
#include <wx/wx.h>

class Console : public wxTextCtrl, public Singleton<Console> {

public:

	Console(wxWindow *parent);
	~Console();

}; // class Console

#endif // _CONSOLE_H

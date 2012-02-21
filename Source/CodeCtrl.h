/*
 * File: CodeCtrl.h
 * Part of M-S Lab project
 * Description: Code editor widget.
 */

#ifndef _CODECTRL_H
#define _CODECTRL_H

#include <wx/wx.h>
#include "Session.h"

class MainFrame;

class CodeCtrl : public wxTextCtrl {

	friend class MainFrame;

	Session session;
	wxString filename;
	wxString fileaddr;
	// TODO: bool isChanged;

public:

	CodeCtrl(wxWindow *parent); // Constructor
	~CodeCtrl(); // Destructor

	void save();
	void save(const wxString &filename, const wxString &fileaddr);
	void load(const wxString &filename, const wxString &fileaddr);

	void execute();

}; // class CodeCtrl

#endif // _CODECTRL_H

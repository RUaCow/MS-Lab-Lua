/*
 * File: MainFrame.h
 * Part of M-S Lab project
 * Description: Main application window
 */

#ifndef _MAINFRAME_H
#define _MAINFRAME_H

#include <wx/wx.h>
#include "FrameManager.h"

#include "Session.h"
#include "Console.h"

class MainFrame : public wxFrame {

	wxFrameManager manager;

	wxTextCtrl *textCode;
	wxString filename;

	Console *console;

	Session session;

	// File menu items
	wxMenuItem *itemNew;
	wxMenuItem *itemOpen;
	wxMenuItem *itemSave;
	wxMenuItem *itemSaveAs;
	wxMenuItem *itemExit;

	// Edit Menu Items
	wxMenuItem *itemUndo;
	wxMenuItem *itemRedo;
	wxMenuItem *itemCut;
	wxMenuItem *itemCopy;
	wxMenuItem *itemPaste;
	wxMenuItem *itemSelectAll;

	// Project menu
	wxMenuItem *itemExecute;

public:

	MainFrame();
	~MainFrame();

private:

	void onNew(wxCommandEvent &event);
	void onOpen(wxCommandEvent &event);
	void onSave(wxCommandEvent &event);
	void onSaveAs(wxCommandEvent &event);
	void onExit(wxCommandEvent &event);

	void onUndo(wxCommandEvent &event);
	void onRedo(wxCommandEvent &event);
	void onCut(wxCommandEvent &event);
	void onCopy(wxCommandEvent &event);
	void onPaste(wxCommandEvent &event);
	void onSelectAll(wxCommandEvent &event);

	void onExecute(wxCommandEvent &event);
	
}; // class MainFrame

#endif // _MAINFRAME_H

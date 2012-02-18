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

class MainFrame : public wxFrame {

	wxFrameManager manager;

	wxTextCtrl *cmdCtrl;

	Session session;

public:

	MainFrame();
	~MainFrame();

private:

	void executeCommand(wxCommandEvent &event);

}; // class MainFrame

#endif // _MAINFRAME_H

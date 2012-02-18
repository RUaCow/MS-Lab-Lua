#include "MainFrame.h"
#include <iostream>
using namespace std;

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, wxT("M-S Lab v0.0.1 (Lua)")) {
	manager.SetFrame(this);

	cmdCtrl = new wxTextCtrl(this, wxID_ANY, wxT(">> "));
	cmdCtrl->SetFont(wxFont(11, 70, 90, 90, false, wxT("Courier New")));
	cmdCtrl->SetFocus();
	cmdCtrl->SetSelection(cmdCtrl->XYToPosition(0,0), cmdCtrl->XYToPosition(0,0));
	cmdCtrl->SetInsertionPointEnd();
	manager.AddPane(cmdCtrl, wxCENTER);
	
	manager.Update();

	// Connect events
	Connect(cmdCtrl->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(MainFrame::executeCommand));
}

MainFrame::~MainFrame() {
	manager.UnInit();
}

void MainFrame::executeCommand(wxCommandEvent &event) {
	//manager->setByString(std::string(wxString(textboxCmd->GetValue().substr(3)).char_str()));
	session.doString(wxString(cmdCtrl->GetValue().substr(3)).char_str());
	cmdCtrl->Clear();
	cmdCtrl->AppendText(wxT("\n>> "));
	cmdCtrl->SetInsertionPointEnd();
}

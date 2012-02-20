#include "MainFrame.h"
#include <iostream>
using namespace std;

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, wxT("M-S Lab v0.0.1 (Lua)")) {
	filename = wxEmptyString;

	manager.SetFrame(this);

	wxMenu *menuFile = new wxMenu();
	wxMenu *menuEdit = new wxMenu();
	wxMenu *menuProject = new wxMenu();

	itemNew = new wxMenuItem(menuFile, wxID_NEW, wxT("New Script\tCtrl+N"));
	menuFile->Append(itemNew);
	itemOpen = new wxMenuItem(menuFile, wxID_OPEN, wxT("Open File\tCtrl+O"));
	menuFile->Append(itemOpen);
	menuFile->AppendSeparator();
	itemSave = new wxMenuItem(menuFile, wxID_SAVE, wxT("Save File\tCtrl+S"));
	menuFile->Append(itemSave);
	itemSaveAs = new wxMenuItem(menuFile, wxID_SAVEAS, wxT("Save File As"));
	menuFile->Append(itemSaveAs);
	menuFile->AppendSeparator();
	itemExit = new wxMenuItem(menuFile, wxID_EXIT, wxT("Exit\tAlt+F4"));
	menuFile->Append(itemExit);

	itemUndo = new wxMenuItem(menuEdit, wxID_UNDO, wxT("Undo\tCtrl+Z"));
	menuEdit->Append(itemUndo);
	itemRedo = new wxMenuItem(menuEdit, wxID_REDO, wxT("Redo\tCtrl+Y"));
	menuEdit->Append(itemRedo);
	menuEdit->AppendSeparator();
	itemCut = new wxMenuItem(menuEdit, wxID_CUT, wxT("Cut\tCtrl+X"));
	menuEdit->Append(itemCut);
	itemCopy = new wxMenuItem(menuEdit, wxID_COPY, wxT("Copy\tCtrl+C"));
	menuEdit->Append(itemCopy);
	itemPaste = new wxMenuItem(menuEdit, wxID_PASTE, wxT("Paste\tCtrl+V"));
	menuEdit->Append(itemPaste);
	menuEdit->AppendSeparator();
	itemSelectAll = new wxMenuItem(menuEdit, wxID_SELECTALL, wxT("Select All\tCtrl+A"));
	menuEdit->Append(itemSelectAll);

	itemExecute = new wxMenuItem(menuProject, wxID_ANY, wxT("Execute\tCtrl+F5"));
	menuProject->Append(itemExecute);

	wxMenuBar *menubar = new wxMenuBar();
	menubar->Append(menuFile, wxT("&File"));
	menubar->Append(menuEdit, wxT("&Edit"));
	menubar->Append(menuProject, wxT("&Project"));
	this->SetMenuBar(menubar);

	// Create statusbar
	CreateStatusBar();
	SetStatusText(wxT("Welcome to M-S Lab!"));

	// Create controls
	
	textCode = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxHSCROLL);
	textCode->SetFont(wxFont(11, 70, 90, 90, false, wxT("Courier New")));
	textCode->SetFocus();
	manager.AddPane(textCode, wxCENTER);
	
	console = new Console(this);
	console->SetFont(wxFont(11, 70, 90, 90, false, wxT("Courier New")));
	manager.AddPane(console, wxBOTTOM);

	manager.Update();

	// Connect events
	Connect(itemNew->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onNew));
	Connect(itemOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onOpen));
	Connect(itemSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onSave));
	Connect(itemSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onSaveAs));
	Connect(itemExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onExit));

	Connect(itemUndo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onUndo));
	Connect(itemRedo->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onRedo));
	Connect(itemCut->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onCut));
	Connect(itemCopy->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onCopy));
	Connect(itemPaste->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onPaste));
	Connect(itemSelectAll->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onSelectAll));

	Connect(itemExecute->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onExecute));
}

MainFrame::~MainFrame() {
	// TODO: Ask if the file is changed
	manager.UnInit();
}

void MainFrame::onNew(wxCommandEvent &event) {
	// TODO: Ask if the file is changed
	textCode->Clear();
	filename = wxEmptyString;
}

void MainFrame::onOpen(wxCommandEvent &event) {
	// TODO: Ask if the file is changed
	wxFileDialog dialog(this, wxT("Open file"), wxEmptyString, wxEmptyString, wxT("Lua script files (*.lua)|*.lua"), wxFD_OPEN);
	if(dialog.ShowModal() == wxID_OK) {
		textCode->LoadFile(dialog.GetPath());
		filename = dialog.GetPath();
	}
}

void MainFrame::onSave(wxCommandEvent &event) {
	if(!filename) {
		wxFileDialog dialog(this, wxT("Save file"), wxEmptyString, wxEmptyString, wxT("Lua script files (*.lua)|*.lua"), wxFD_SAVE);
		if(dialog.ShowModal() == wxID_OK) 
			filename = dialog.GetPath();
	}
	textCode->SaveFile(filename);
}

void MainFrame::onSaveAs(wxCommandEvent &event) {
	wxFileDialog dialog(this, wxT("Save file"), wxEmptyString, wxEmptyString, wxT("Lua script files (*.lua)|*.lua"), wxFD_SAVE);
	if(dialog.ShowModal() == wxID_OK) {
		textCode->SaveFile(dialog.GetPath());
		filename = dialog.GetPath();
	}
}

void MainFrame::onExit(wxCommandEvent &event) {
	this->~MainFrame();
}

void MainFrame::onUndo(wxCommandEvent &event) {
	if(this->FindFocus() == textCode)
		textCode->Undo();
}

void MainFrame::onRedo(wxCommandEvent &event) {
	if(this->FindFocus() == textCode)
		textCode->Redo();
}

void MainFrame::onCut(wxCommandEvent &event) {
	if(this->FindFocus() == textCode)
		textCode->Cut();
}

void MainFrame::onCopy(wxCommandEvent &event) {
	if(this->FindFocus() == textCode)
		textCode->Copy();
}

void MainFrame::onPaste(wxCommandEvent &event) {
	if(this->FindFocus() == textCode)
		textCode->Paste();
}

void MainFrame::onSelectAll(wxCommandEvent &event) {
	if(this->FindFocus() == textCode)
		textCode->SelectAll();
}

void MainFrame::onExecute(wxCommandEvent &event) {
	wxCommandEvent tmp;
	onSave(tmp);
	console->Clear();

	Console::GetSingleton() << wxT("Restarting session\n");
	session.close();
	session.start();
	Console::GetSingleton() << wxT("Executing: ") << filename << "\n";
	session.doFile(filename.char_str());
	Console::GetSingleton() << "Execution done" << "\n";
}

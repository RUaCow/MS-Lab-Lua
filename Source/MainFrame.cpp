#include "MainFrame.h"
#include "CodeCtrl.h"
using namespace std;

MainFrame::MainFrame() : wxFrame(NULL, wxID_ANY, wxT("M-S Lab v0.0.1 (Lua)")) {
	manager.SetFrame(this);

	wxMenu *menuFile = new wxMenu();
	wxMenu *menuEdit = new wxMenu();
	wxMenu *menuProject = new wxMenu();

	itemNew = new wxMenuItem(menuFile, wxID_NEW, wxT("New Script\tCtrl+T"));
	menuFile->Append(itemNew);
	itemOpen = new wxMenuItem(menuFile, wxID_OPEN, wxT("Open File\tCtrl+O"));
	menuFile->Append(itemOpen);
	menuFile->AppendSeparator();
	itemSave = new wxMenuItem(menuFile, wxID_SAVE, wxT("Save File\tCtrl+S"));
	menuFile->Append(itemSave);
	itemSaveAs = new wxMenuItem(menuFile, wxID_SAVEAS, wxT("Save File As"));
	menuFile->Append(itemSaveAs);
	menuFile->AppendSeparator();
	itemClose = new wxMenuItem(menuFile, wxID_CLOSE, wxT("Close File\tCtrl+W"));
	menuFile->Append(itemClose);
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
	
	notebook = new wxNotebook(this, wxID_ANY);
	manager.AddPane(notebook, wxCENTER);
	
	console = new Console(this);
	manager.AddPane(console, wxBOTTOM);

	manager.Update();

	// Connect events
	Connect(itemNew->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onNew));
	Connect(itemOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onOpen));
	Connect(itemSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onSave));
	Connect(itemSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onSaveAs));
	Connect(itemClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainFrame::onClose));
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
	manager.UnInit();
}

void MainFrame::onNew(wxCommandEvent &event) {
	notebook->AddPage(new CodeCtrl(notebook), wxEmptyString, true);
}

void MainFrame::onOpen(wxCommandEvent &event) {
	wxFileDialog dialog(this, wxT("Open file"), wxEmptyString, wxEmptyString, wxT("Lua script files (*.lua)|*.lua"), wxFD_OPEN);
	if(dialog.ShowModal() == wxID_OK) {
		CodeCtrl *control = new CodeCtrl(notebook);
		control->load(dialog.GetFilename(), dialog.GetPath());
		notebook->AddPage(control, dialog.GetFilename(), true);
	}
}

void MainFrame::onSave(wxCommandEvent &event) {
	CodeCtrl *active = (CodeCtrl*) notebook->GetCurrentPage();
	if(!active)
		return;

	if(active->fileaddr != wxEmptyString)
		active->save();
	else {
		wxFileDialog dialog(this, wxT("Save file"), wxEmptyString, wxEmptyString, wxT("Lua script files (*.lua)|*.lua"), wxFD_SAVE);
		if(dialog.ShowModal() == wxID_OK)
			active->save(dialog.GetFilename(), dialog.GetPath());
		int pageNumber = 0;
		for(int i = 0; i < notebook->GetPageCount(); i ++)
			if(notebook->GetPage(i) == active)
				pageNumber = i;
		notebook->SetPageText(pageNumber, dialog.GetFilename());

	}
}

void MainFrame::onSaveAs(wxCommandEvent &event) {
	CodeCtrl *active = (CodeCtrl*) notebook->GetCurrentPage();
	if(!active)
		return;

	wxFileDialog dialog(this, wxT("Save file"), wxEmptyString, wxEmptyString, wxT("Lua script files (*.lua)|*.lua"), wxFD_SAVE);
	if(dialog.ShowModal() == wxID_OK) {
		active->save(dialog.GetFilename(), dialog.GetPath());
		int pageNumber = 0;
		for(int i = 0; i < notebook->GetPageCount(); i ++)
			if(notebook->GetPage(i) == active)
				pageNumber = i;
		notebook->SetPageText(pageNumber, dialog.GetFilename());
	}
}

void MainFrame::onClose(wxCommandEvent &event) {
	CodeCtrl *active = (CodeCtrl*) notebook->GetCurrentPage();
	if(!active)
		return;

	int pageNumber = 0;
	for(int i = 0; i < notebook->GetPageCount(); i ++)
		if(notebook->GetPage(i) == active)
			pageNumber = i;
	notebook->DeletePage(pageNumber);
}

void MainFrame::onExit(wxCommandEvent &event) {
	this->~MainFrame();
}

void MainFrame::onUndo(wxCommandEvent &event) {
	wxWindow *active = this->FindFocus();
	if(!active)
		return;

	if(active != console)
		if(dynamic_cast<CodeCtrl*>(active))
			((CodeCtrl*)active)->Undo();
}

void MainFrame::onRedo(wxCommandEvent &event) {
	wxWindow *active = this->FindFocus();
	if(!active)
		return;

	if(active != console)
		if(dynamic_cast<CodeCtrl*>(active))
			((CodeCtrl*)active)->Redo();
}

void MainFrame::onCut(wxCommandEvent &event) {
	wxWindow *active = this->FindFocus();
	if(!active)
		return;

	if(active != console)
		if(dynamic_cast<CodeCtrl*>(active))
			((CodeCtrl*)active)->Cut();
}

void MainFrame::onCopy(wxCommandEvent &event) {
	wxWindow *active = this->FindFocus();
	if(!active)
		return;

	if(active == console)
		console->Copy();
	else if(dynamic_cast<CodeCtrl*>(active))
		((CodeCtrl*)active)->Copy();
}

void MainFrame::onPaste(wxCommandEvent &event) {
	wxWindow *active = this->FindFocus();
	if(!active)
		return;

	if(active != console)
		if(dynamic_cast<CodeCtrl*>(active))
			((CodeCtrl*)active)->Paste();
}

void MainFrame::onSelectAll(wxCommandEvent &event) {
	wxWindow *active = this->FindFocus();
	if(!active)
		return;

	if(active == console)
		console->SelectAll();
	else if(dynamic_cast<CodeCtrl*>(active))
		((CodeCtrl*)active)->SelectAll();
}

void MainFrame::onExecute(wxCommandEvent &event) {
	CodeCtrl *control = (CodeCtrl*) notebook->GetCurrentPage();
	if(!control)
		return;

	// TODO: Fix calling method
	wxCommandEvent tmp;
	onSave(tmp);

	control->execute();
}

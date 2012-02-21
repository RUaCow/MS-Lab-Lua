#include "CodeCtrl.h"
#include "Console.h"
using namespace std;

CodeCtrl::CodeCtrl(wxWindow *parent) : wxTextCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxHSCROLL) {
	this->SetFont(wxFont(11, 70, 90, 90, false, wxT("Courier New")));

	filename = wxEmptyString;
	fileaddr = wxEmptyString;
}

CodeCtrl::~CodeCtrl() {

}

void CodeCtrl::save() {
	this->SaveFile(fileaddr);
}

void CodeCtrl::save(const wxString &filename, const wxString &fileaddr) {
	this->fileaddr = fileaddr;
	this->filename = filename;
	this->SaveFile(fileaddr);
}

void CodeCtrl::load(const wxString &filename, const wxString &fileaddr) {
	this->fileaddr = fileaddr;
	this->filename = filename;
	this->LoadFile(fileaddr);
}

void CodeCtrl::execute() {
	if(!fileaddr)
		return;

	Console::GetSingleton().Clear();
	Console::GetSingleton() << wxT("Restarting session\n");
	session.close();
	session.start();
	Console::GetSingleton() << wxT("Executing: ") << fileaddr << wxT("\n");
	session.doFile(fileaddr.char_str());
	Console::GetSingleton() << wxT("Execution done") << wxT("\n");
}

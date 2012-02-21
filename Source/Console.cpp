#include "Console.h"

Console::Console(wxWindow *parent) : wxTextCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY) {
	this->SetFont(wxFont(11, 70, 90, 90, false, wxT("Courier New")));
}

Console::~Console() {

}

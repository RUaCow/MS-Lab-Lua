#include "Console.h"

Console* Console::singleton_ptr = NULL;

Console::Console(wxWindow *parent) : wxTextCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_PROCESS_ENTER) {
	singleton_ptr = this;
}

Console::~Console() { }

Console& Console::GetSingleton() {
	return (*singleton_ptr);
}

Console* Console::GetSingletonPtr() {
	return singleton_ptr;
}

#include "MainApp.h"

bool MainApp::OnInit() {
	MainFrame *window = new MainFrame();
	window->Show();
	return true;
}

IMPLEMENT_APP(MainApp)

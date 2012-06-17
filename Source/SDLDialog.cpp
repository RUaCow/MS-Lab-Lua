#include "SDLDialog.h"

IMPLEMENT_CLASS(SDLDialog, wxDialog)

BEGIN_EVENT_TABLE(SDLDialog, wxDialog)
    EVT_PAINT(SDLDialog::onPaint)
    EVT_IDLE(SDLDialog::onIdle)
	EVT_CLOSE(SDLDialog::onClose)
END_EVENT_TABLE()

SDLDialog::SDLDialog(wxWindow *parent, int w, int h) : wxDialog(parent, wxID_ANY, wxT("M-S Lab Diagram View"), wxDefaultPosition, wxSize(w, h)) {
	surface = SDL_CreateRGBSurface(SDL_HWSURFACE, GetSize().x, GetSize().y, 24, 0, 0, 0, 0);
}

SDLDialog::~SDLDialog() {

}

SDL_Surface* SDLDialog::getSurface() {
	return surface;
}

void SDLDialog::onPaint(wxPaintEvent &event) {
	wxBitmap bmp(wxImage(surface->w, surface->h, static_cast<unsigned char*>(surface->pixels), true));
    wxBufferedPaintDC dc(this, bmp);
}

void SDLDialog::onIdle(wxIdleEvent &event) {
	Refresh(false);
}

void SDLDialog::onClose(wxCloseEvent &event) {
	SDL_FreeSurface(surface);
	this->Destroy();
}

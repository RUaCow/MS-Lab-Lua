/*
 * File: SDLDialog.h
 * Part of M-S Lab project
 * Description: This class implements SDL inside a wxDialog to draw diagrams.
 */

#ifndef _SDLDIALOG_H
#define _SDLDIALOG_H

#include <wx/wx.h>
#include <wx/dcbuffer.h>
#include <SDL/SDL.h>
#undef main

class SDLDialog : public wxDialog {
	
	DECLARE_CLASS(SDLDialog)
	DECLARE_EVENT_TABLE()

	SDL_Surface *surface;

public:

	SDLDialog(wxWindow *parent, int w, int h);
	~SDLDialog();

	SDL_Surface* getSurface();

private:

	void onPaint(wxPaintEvent &event);
	void onIdle(wxIdleEvent &event);
	void onClose(wxCloseEvent &event);

}; // class SDLDialog

#endif // _SDLDIALOG_H

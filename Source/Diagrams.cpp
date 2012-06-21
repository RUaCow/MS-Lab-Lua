#include "Database.h"
#include "SDLDialog.h"
#include "MainFrame.h"
#include <SDL/SDL_gfxPrimitives.h>
#include <boost/lexical_cast.hpp>

using namespace std;

#define RTD (180.0f / float(M_PI))
#define DTR (float(M_PI) / 180.0f)

void Database::drawPie(int width, int height) const {
	SDLDialog *dlg = new SDLDialog(MainFrame::GetSingletonPtr(), width, height);
	
	int sum = 0;
	for(int i = 0; i < table[0].second->getSize(); i ++)
		sum += boost::lexical_cast<int>(table[0].second->at(i));

	int x = width/2, y = height/2;
	int r = min(width, height)/2 - 50;

	float start = 0;
	for(int i = 0; i < table[0].second->getSize(); i ++) {
		float data = boost::lexical_cast<int>(table[0].second->at(i));
		float end = start + (data * 360 / sum);
		
		int red = rand()%255, green = rand()%255, blue = rand()%255;
		filledPieRGBA(dlg->getSurface(), x, y, r, start, end, red, green, blue, 255);

		int xt = x + (r-15)*cos((start + end)/2 * DTR);
		int yt = y + (r-15)*sin((start + end)/2 * DTR);

		stringRGBA(dlg->getSurface(), xt, yt, "test", 255 - red, 255 - green, 255 - blue, 255);

		start = end;
	}

	dlg->Show();
}

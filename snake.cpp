#include <iostream>
#include <SDL.h>

static const unsigned W_W = 800;
static const unsigned W_H = 600;
static const unsigned B_W = 256;
static const unsigned B_H = 256;

int main(int argc, char* argv[])
{
	SDL_Surface *display = NULL;
	SDL_Event event;
	SDL_Rect box;
	unsigned color;
	unsigned bkg_color;
	bool running;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cerr << "SDL_INIT Failed: "
			<< SDL_GetError() << std::endl;
		return -1;
	}

	display = SDL_SetVideoMode(W_W, W_H,
			32, SDL_HWSURFACE | SDL_DOUBLEBUF);

	if (!display)
	{
		std::cerr << "SDL_SetVideoMode failed: "
			<< SDL_GetError() << std::endl;
		return -1;
	}

	SDL_WM_SetCaption("First SDL Application", NULL);

	box.w = B_W;
	box.h = B_H;
	box.x = (W_W - B_W) / 2;
	box.y = (W_H - B_H) / 2;

	bkg_color = SDL_MapRGB(display->format, 0, 0, 0);
	color = SDL_MapRGB(display->format, 0, 0, 255);
	running = true;

	SDL_FillRect(display, NULL, bkg_color);
	SDL_FillRect(display, &box, color);
	SDL_Flip(display);

	while (running)
	{
		while(SDL_PollEvent(&event))
		{
			switch(event.type)
			{
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE)
					{
						running = false;
						break;
					}
			}
		}

		SDL_Delay(20);
	}

	SDL_Quit();
	return 0;
}

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
	SDL_Rect boundaries;
	unsigned speed;
	unsigned color;
	unsigned bkg_color;
	bool running;
	unsigned char *keys;

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

	boundaries.x = 0;
	boundaries.y = 0;
	boundaries.w = W_W - box.w;
	boundaries.h = W_H - box.h;

	speed = 6;

	bkg_color = SDL_MapRGB(display->format, 0, 0, 0);
	color = SDL_MapRGB(display->format, 0, 0, 255);
	running = true;

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
		keys = SDL_GetKeyState(NULL);

		SDL_FillRect(display, NULL, bkg_color);
		SDL_FillRect(display, &box, color);
		SDL_Flip(display);

		// y
		if (keys[SDLK_UP])
		{
			box.y -= speed;
			if (box.y < boundaries.y)
				box.y = boundaries.y;
		}
		else if (keys[SDLK_DOWN])
		{
			box.y += speed;
			if (box.y > boundaries.h)
				box.y = boundaries.h;
		}
		// x
		if (keys[SDLK_LEFT])
		{
			box.x -= speed;
			if (box.x < boundaries.x)
				box.x = boundaries.x;
		}
		else if (keys[SDLK_RIGHT])
		{
			box.x += speed;
			if (box.x > boundaries.w)
				box.x = boundaries.w;
		}

		SDL_Delay(20);
	}

	SDL_Quit();
	return 0;
}

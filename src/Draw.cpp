#include "Draw.h"

Draw::Draw(SDL_Renderer* renderer)
{
	error = false;
	SDL_Surface* charset_s = SDL_LoadBMP("src/bmp/cs8x8.bmp");
	if (charset_s == NULL)
	{
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		error = true;
	}
	SDL_Surface* charset_s2 = SDL_LoadBMP("src/bmp/charset3.bmp");
	if (charset_s2 == NULL)
	{
		printf("SDL_LoadBMP(charset2.bmp) error: %s\n", SDL_GetError());
		error = true;
	}
	charset = SDL_CreateTextureFromSurface(renderer, charset_s);
	charset2 = SDL_CreateTextureFromSurface(renderer, charset_s2);

	SDL_Surface* background_s = SDL_LoadBMP("src/bmp/background.bmp");
	if (background_s == NULL)
	{
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		error = true;
	}
	else {
		background = SDL_CreateTextureFromSurface(renderer,background_s);
	}
	this->renderer = renderer;

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,SDL_TEXTUREACCESS_STREAMING,SCREEN_WIDTH, SCREEN_HEIGHT);

	black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	//SDL_SetColorKey(charset, true, 0x000000);
}

Draw::~Draw()
{
	SDL_DestroyTexture(charset);
	SDL_DestroyTexture(charset2);
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(scrtex);
	SDL_FreeSurface(screen);
	//SDL_FreeSurface(background);
}

bool Draw::drawPartOfTexture(SDL_Renderer* renderer, SDL_Texture* texture, int X, int Y, SDL_Rect SrcR, double angle, SDL_RendererFlip flip) {
	if (renderer == NULL || texture == NULL) {
		return false;
	}
	SDL_Rect DestR = { X,Y,SrcR.w, SrcR.h };
	SDL_Point center = { SrcR.w/2, SrcR.h/2 };
	SDL_RenderCopyEx(renderer, texture, &SrcR, &DestR, angle, &center, flip);
	return true;
}


// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void Draw::DrawString(int x, int y, const char* text,
	SDL_Texture* charset, int size) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = size;
	s.h = size;
	d.w = size;
	d.h = size;
	while (*text) {
		c = *text & 255;
		px = (c % (16)) * size;
		py = (c / (16)) * size;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_RenderCopy(this->renderer, charset, &s, &d);
		//SDL_BlitSurface(charset, &s, screen, &d);
		x += size;
		text++;
	};
};

// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void Draw::DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
};

// draw a single pixel
void Draw::DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8* p = (Uint8*)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32*)p = color;
};


// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void Draw::DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for (int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
	};
};


// draw a rectangle of size l by k
void Draw::DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
	Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for (i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
};


void Draw::DrawFullScreenTexture()
{
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
}

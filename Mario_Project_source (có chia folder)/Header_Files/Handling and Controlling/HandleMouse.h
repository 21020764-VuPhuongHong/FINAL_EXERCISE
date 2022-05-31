#ifndef HandleMouse_H
#define HandleMouse_H

#include "SDL_Utility.h"

enum ButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3
};

class MouseButton
{
private:

	int BUTTON_WIDTH;
	int BUTTON_HEIGHT;

	SDL_Point mPosition;

	ButtonSprite mCurrentSprite;
public:
	MouseButton();

	void setPosition(int x, int y);

	void handleEvent(SDL_Event& e);

	ButtonSprite getCurrentSprite();

	void freeCurrentSpriteToUp();

	void freeCurrentSpriteToOut();

	void setButtonDimensions(int x, int y);
};

#endif 

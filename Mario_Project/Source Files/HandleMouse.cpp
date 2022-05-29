#include "HandleMouse.h"

MouseButton::MouseButton()
{
	mPosition.x = 0;
	mPosition.y = 0;

	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;

	BUTTON_WIDTH = 0;
	BUTTON_HEIGHT = 0;
}

void MouseButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

void MouseButton::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		bool inside = true;

		if (x < mPosition.x)
		{
			inside = false;
		}
		else if (x > mPosition.x + BUTTON_WIDTH)
		{
			inside = false;
		}
		else if (y < mPosition.y)
		{
			inside = false;
		}
		else if (y > mPosition.y + BUTTON_HEIGHT)
		{
			inside = false;
		}

		if (!inside)
		{
			mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
		}
		else
		{
			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (e.button.button == SDL_BUTTON_LEFT) {
					mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
					break;
				}
			case SDL_MOUSEBUTTONUP:
				mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
	}
}

ButtonSprite MouseButton::getCurrentSprite()
{
	return mCurrentSprite;
}

void MouseButton::freeCurrentSpriteToUp() {
	mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
}

void MouseButton::freeCurrentSpriteToOut() {
	mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
}

void MouseButton::setButtonDimensions(int x, int y)
{
	BUTTON_WIDTH = x;
	BUTTON_HEIGHT = y;
}


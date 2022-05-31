#include "CustomSummerDecoration.h"
#include "SDL_Utility.h"


SDL_Surface* CustomSummerDecoration::decorationImages;

CustomSummerDecoration::CustomSummerDecoration(SummerDecorationType type, Position position)
{
	this->position = position;
	decorationType = type;
	size = Size(140, 140);
}

//Vat trang tri cho summer world la hang rao go (fence)
void CustomSummerDecoration::loadDecorationImages(SDL_Surface* display)
{
	decorationImages = loadPNG("img/ie_imgs/fence.png", display);
}

void CustomSummerDecoration::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		drawSurface(display, decorationImages, position.getX() - beginningOfCamera, position.getY());
	}
}
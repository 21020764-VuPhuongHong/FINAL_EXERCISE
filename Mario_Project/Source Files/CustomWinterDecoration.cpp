#include "CustomWinterDecoration.h"
#include "SDL_Utility.h"

 //Vat trang tri cho winter world gom cac ngoi sao, dam may va bien chi dan (signpost)

std::array<SDL_Surface*, 8> CustomWinterDecoration::decorationImages;

Size CustomWinterDecoration::getSizeFromDecorationType() const
{
	if (decorationType >= WinterDecorationType::YELLOW_STAR && decorationType <= WinterDecorationType::BLUE_STAR) {
		return Size(9, 10);
	}
	else if (decorationType == WinterDecorationType::SMALL_WINTER_CLOUD) {
		return Size(156, 72);
	}
	else if (decorationType == WinterDecorationType::WINTER_CLOUD) {
		return Size(236, 96);
	}
	else {
		return Size(58, 58);
	}
}

CustomWinterDecoration::CustomWinterDecoration(WinterDecorationType type, Position position)
{
	this->position = position;
	decorationType = type;
	size = getSizeFromDecorationType();
}

void CustomWinterDecoration::loadDecorationImages(SDL_Surface* display)
{
	decorationImages[0] = loadPNG("img/ie_imgs/sky_star1.png", display);
	decorationImages[1] = loadPNG("img/ie_imgs/sky_star2.png", display);
	decorationImages[2] = loadPNG("img/ie_imgs/sky_star3.png", display);
	decorationImages[3] = loadPNG("img/ie_imgs/sky_star4.png", display);
	decorationImages[4] = loadPNG("img/ie_imgs/winter_cloud1.png", display);
	decorationImages[5] = loadPNG("img/ie_imgs/winter_cloud2.png", display);
	decorationImages[6] = loadPNG("img/ie_imgs/signpost.png", display);
	decorationImages[7] = loadPNG("img/ie_imgs/second_signpost.png", display);
}

void CustomWinterDecoration::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* decorationImg = decorationImages[static_cast<int>(decorationType) - 1];
		drawSurface(display, decorationImg, position.getX() - beginningOfCamera, position.getY());
	}
}
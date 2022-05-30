#include "Castle.h"
#include "SDL_Utility.h"


std::array<SDL_Surface*, 2> Castle::castleImages;

//size cho biet kich thuoc cua hinh anh chu khong co tac dung gi khac
Castle::Castle(Position position, bool bigCastleFlag)
{
	this->position = position;
	this->bigCastleFlag = bigCastleFlag;
	size = (bigCastleFlag ? Size(360, 497) : Size(190, 269));
}

void Castle::loadCastleImages(SDL_Surface* display)
{
	castleImages[0] = loadPNG("img/ie_imgs/castle.png", display);
	castleImages[1] = loadPNG("img/ie_imgs/big_castle.png", display);
}

//Hien thi castle tuy theo level
void Castle::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* castleImg = castleImages[bigCastleFlag];
		drawSurface(display, castleImg, position.getX() - beginningOfCamera, position.getY());
	}
}
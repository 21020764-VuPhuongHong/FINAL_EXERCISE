#include "Cloud.h"

#include "SDL_Utility.h"


std::array<SDL_Surface*, 3> Cloud::cloudImages;

Size Cloud::getSizeFromModel() const
{
	if (model == 1) {
		return Size(138, 64);
	}
	else if (model == 2) {
		return Size(155, 84);
	}
	else {
		return Size(236, 96);
	}
}

Cloud::Cloud(int type, Position position)
{
	this->position = position;
	model = type;
	size = getSizeFromModel();
}

void Cloud::loadCloudImages(SDL_Surface* display)
{
	for (std::size_t i = 0; i < cloudImages.size(); ++i) {
		std::string filename = "img/ie_imgs/cloud";
		filename += std::to_string(i + 1);
		filename += ".png";
		cloudImages[i] = loadPNG(filename, display);
	}
}

void Cloud::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera)) {
		SDL_Surface* cloudImg = cloudImages[model - 1];
		drawSurface(display, cloudImg, position.getX() - beginningOfCamera, position.getY());
	}
}
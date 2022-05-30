#ifndef CustomWinterDecoration_H
#define CustomWinterDecoration_H

#include <array>
#include "InanimateObject.h"

class Position;
struct SDL_Surface;

enum class WinterDecorationType
{
	YELLOW_STAR = 1,
	GOLDEN_STAR = 2,
	WHITE_STAR = 3,
	BLUE_STAR = 4,
	SMALL_WINTER_CLOUD = 5,
	WINTER_CLOUD = 6,
	SIGNPOST = 7,
	SECOND_SIGNPOST = 8
};
 

class CustomWinterDecoration : public InanimateObject
{
private:
	static std::array<SDL_Surface*, 8> decorationImages;
	WinterDecorationType decorationType;
	Size getSizeFromDecorationType() const;

public:
	CustomWinterDecoration(WinterDecorationType type, Position position);
	static void loadDecorationImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif 
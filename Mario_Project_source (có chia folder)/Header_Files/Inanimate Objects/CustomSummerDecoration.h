#ifndef CustomSummerDecoration_H
#define CustomSummerDecoration_H

#include "InanimateObject.h"

class Position;
struct SDL_Surface;

enum class SummerDecorationType
{
	FENCE = 1
};


class CustomSummerDecoration : public InanimateObject
{
private:
	static SDL_Surface* decorationImages;
	SummerDecorationType decorationType;

public:
	CustomSummerDecoration(SummerDecorationType type, Position position);
	static void loadDecorationImages(SDL_Surface* display);
	void draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const override;
};

#endif 
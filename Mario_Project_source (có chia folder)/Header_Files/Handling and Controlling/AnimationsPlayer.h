#ifndef AnimationsPlayer_H							
#define AnimationsPlayer_H

#include <memory>					

class Player;
class Screen;
class Camera;
class World;
enum class Direction;
struct SDL_Surface;

class AnimationsPlayer final				
{
private:
	static std::array<SDL_Surface*, 5> deadMarioImages;
	static std::array<int, 10> xPositions;
	static std::array<int, 10> yPositions;
	static constexpr int MARIO_DYING_ANIMATION_FRAMES_NUMBER = 2400;
	static constexpr int MARIO_PIPE_TRAVELLING_ANIMATION_FRAMES_NUMBER = 350;
	static constexpr int FIREWORKS_FRAMES_NUMBER = 2500;				
	static void addExplosions(World &world, int i, Screen &screen);
	static void drawBasicScreenElements(Screen &screen);
	static void drawFireworks(World &world, Screen &screen, int bgScrollingOffset = 0);				
	static void playAddingPointsAnimation(World &world, bool checker, Screen &screen, int bgScrollingOffset = 0);

public:
	AnimationsPlayer() = delete;
	static void loadAnimationsPlayerImages(SDL_Surface* display);
	static void playMarioDyingAnimation(World &world, Screen &screen, int bgScrollingOffset = 0);
	static void playMarioPipeTravellingAnimation(World &world, Direction direction, Screen &screen, int bgScrollingOffset = 0);
	static void playBridgeSpoilingAnimation(World &world, Screen &screen, int bgScrollingOffset = 0);
	static void playLevelFinishedAnimation(World &world, Screen &screen, int bgScrollingOffset = 0);
	static void playWorldFinishedAnimation(World &world, Screen &screen, int bgScrollingOffset = 0);
	static void playCustomWorldFinishedAnimation(World &world, int level, Screen &screen, int bgScrollingOffset = 0);
};

#endif 
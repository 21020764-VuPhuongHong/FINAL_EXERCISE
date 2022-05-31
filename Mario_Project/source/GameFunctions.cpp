#include "GameFunctions.h"
#include "SoundController.h"
#include "KeyboardController.h"
#include "PreloadingImages.h"
#include "AnimationsPlayer.h"
#include "Level.h"
#include "World.h"
#include "Screen.h"
#include "Camera.h"
#include "Player.h"
#include "WorldInteractionFunctions.h"
#include "MenuManager.h"
#include "FileNotLoadedException.h"

//Cac ham set up
void setCameraPointer(Player &player, World& world, Screen& screen, std::shared_ptr<Camera> camera)
{
	player.setCamera(camera);
	world.setCamera(camera);
	screen.setCamera(camera);
}

void setPlayerPointer(World &world, Screen& screen, std::shared_ptr<Player> player)
{
	world.setPlayer(player);
	screen.setPlayer(player);
}

bool isLevelClassic(int level)
{
	return (level > 0 && level < 5);
}

bool isLevelTheLast(int level)
{
	return (level == 4);
}

bool isLevelCustom(int level)
{
	return (level == 77 || level == 88);		
}

bool isCheckPointLeadingToHiddenStage(int level, int checkPointMark)		
{
	if ((level != 3 && level != 4) && checkPointMark == 1) {
		return true;
	}
	else if (level == 88 && checkPointMark == 4) {
		return true;
	}

	return false;
}

bool isPlayerEnteringPipe(int level, int checkPointMark)		
{
	if ((level == 1 || level == 2) && checkPointMark == 1) {
		return true;
	}
	else if (level == 77 && (checkPointMark == 1 || checkPointMark == 3)) {
		return true;
	}
	else if (level == 88 && (checkPointMark >= 2 && checkPointMark <= 6)) {
		return true;
	}

	return false;
}

bool isPlayerExitingPipe(int level, int checkPointMark)			
{
	if ((level == 1 && checkPointMark == 2) || (level == 2 && (checkPointMark == 2 || checkPointMark == 3))) {
		return true;
	}
	else if (level == 77 && (checkPointMark == 2 || checkPointMark == 3)) {
		return true;
	}
	else if (level == 88 && (checkPointMark >= 1 && checkPointMark <= 6)) {
		return true;
	}

	return false;
}

void resetScreenForClassicLevels(Screen &screen, int level, int checkPointMark)
{
	if (level == 1) {
		if (checkPointMark == -1) {						
			screen.resetScreen(0, 640);
		}
		else if (checkPointMark == 1) {
			screen.resetScreen(0, 640, false);
		}
		else if (checkPointMark == 2) {
			screen.resetScreen(5060, 5700, false);
		}
	}
	else if (level == 2) {
		if (checkPointMark == -1) {
			screen.resetScreen(0, 640);
		}
		else if (checkPointMark == 1 || checkPointMark == 3) {
			screen.resetScreen(0, 640, false);
		}
		else if (checkPointMark == 2) {
			screen.resetScreen(3560, 4200, false);
		}
	}
	else if (level == 3 || level == 4) {
		screen.resetScreen(0, 640);
	}
}

void resetScreenForCustomLevels(Screen &screen, int level, int checkPointMark)
{
	if (level == 77) {
		if (checkPointMark == -1) {
			screen.resetScreen(0, 640);
		}
		else if (checkPointMark == 1 || checkPointMark == 3) {
			screen.resetScreen(0, 640, false);
		}
		else if (checkPointMark == 2) {
			screen.resetScreen(6860, 7500, false);
		}
	}
	else if (level == 88) {
		if (checkPointMark == -1) {
			screen.resetScreen(0, 640);
		}
		else if (checkPointMark == 1 || (checkPointMark >= 3 && checkPointMark <= 6)) {
			screen.resetScreen(0, 640, false);
		}
		else if (checkPointMark == 2) {
			screen.resetScreen(3000, 3640, false);
		}
	}
}

void resetScreen(Screen &screen, int level, int checkPointMark)
{
	if (isLevelClassic(level)) {
		resetScreenForClassicLevels(screen, level, checkPointMark);
	}
	else if (isLevelCustom(level)) {
		resetScreenForCustomLevels(screen, level, checkPointMark);
	}
}

void changeLevel(int level, World &world, bool playerState)
{
	if (level == 1) {
		Level::setFirstLevel(world, playerState);
	}
	else if (level == 2) {
		Level::setSecondLevel(world, playerState);
	}
	else if (level == 3) {
		Level::setThirdLevel(world);
	}
	else if (level == 4) {
		Level::setFourthLevel(world);
	}
	else if (level == 77) {
		Level::setWinterWorld(world);
	}
	else if (level == 88) {
		Level::setSummerWorld(world);
	}
}

void setWorld(int level, Player &player, World &world, bool playerState)
{
	if (playerState) {
		player.setPositionXY(level);
	}
	else {
		player.reborn(level);
	}

	changeLevel(level, world, playerState);
}

void setSubWorldForClassicLevels(int level, int checkPointMark, World &world)		
{
	if (level == 1) {
		if (checkPointMark == 1) {
			Level::setFirstHiddenStage(world);
		}
		else {
			Level::setFirstLevel(world, false);
		}
	}
	else if (level == 2) {
		if (checkPointMark == 1) {
			Level::setSecondHiddenStage(world);
		}
		else if (checkPointMark == 2) {
			Level::setSecondLevel(world, false);
		}
		else if (checkPointMark == 3) {
			Level::setSecondStageOnSecondLevel(world);
		}
	}
}

void setSubWorldForCustomLevels(int level, int checkPointMark, World &world)
{
	if (level == 77) {
		if (checkPointMark == 1) {
			Level::setWinterHiddenStage(world);
		}
		else if (checkPointMark == 2) {
			Level::setWinterWorld(world);
		}
		else if (checkPointMark == 3) {
			Level::setSecondStageOnWinterWorld(world);
		}
	}
	else if (level == 88) {
		if (checkPointMark == 1) {
			Level::setSummerHiddenStage(world);		
		}
		else if (checkPointMark == 2) {
			Level::setSummerWorld(world);
		}
		else if (checkPointMark == 3 || checkPointMark == 5) {
			Level::setSecondStageOnSummerWorld(world);
		}
		else if (checkPointMark == 4) {
			Level::setSecondSummerHiddenStage(world);
		}
		else if (checkPointMark == 6) {
			Level::setThirdStageOnSummerWorld(world);
		}
	}
}

void setSubWorld(int level, int checkPointMark, Player &player, World &world)
{
	player.resetSteps();											
	player.setPositionXY(level, checkPointMark);

	if (isLevelClassic(level)) {
		setSubWorldForClassicLevels(level, checkPointMark, world);
	}
	else if (isLevelCustom(level)) {
		setSubWorldForCustomLevels(level, checkPointMark, world);
	}
}

void adjustCamera(int level, int checkPointMark)
{
	if (isCheckPointLeadingToHiddenStage(level, checkPointMark)) {
		Camera::disableCameraMoving();
	}
	else {
		Camera::enableCameraMoving();
	}
}

void initSound()
{
	bool soundInitStatus = SoundController::initSoundMixer();
	if (soundInitStatus) {
		SoundController::loadSounds();
	}
	else {
		showSoundErrorWindow();
	}
}

//Quan ly menu game
void handleMenu(bool * exitStatus, int * gameSpeed, int * level, Screen &screen, bool & quit)
{
	MenuManager menu = MenuManager();
	SDL_Event menuEvent;

	while (menu.isStillOpen()) {
		menu.drawMenu(screen);

		if (SDL_PollEvent(&menuEvent)) {
			if (menuEvent.type == SDL_QUIT) {
				quit = true;
				break;
			}
			menu.handleMouse(menuEvent);

		}
	}

	*gameSpeed = menu.getGameSpeed();
	*level = menu.getLevel();

	if (menu.getExitStatus()) {
		*exitStatus = true;
	}
}

//Khi hoan thanh 1 level
void showLevelFinishingAnimation(Player &player, World &world, Screen &screen, int level, int bgScrollingOffset)
{
	SoundController::playFlagDownEffect();
	world.switchOnFlag();
	player.setSlidingParameters();
	getPointsFromFlag(player, world);

	while (!world.isFlagDown()) {
		world.performActions();
		screen.updateScreen(world, bgScrollingOffset);
	}
	player.setFinishingRunParameters(185);

	AnimationsPlayer::playLevelFinishedAnimation(world, screen, bgScrollingOffset);
}

//Khi hoan thanh classic world
void showWorldFinishingAnimation(Player &player, World &world, Screen &screen, int bgScrollingOffset)
{
	AnimationsPlayer::playBridgeSpoilingAnimation(world, screen, bgScrollingOffset);
	player.setFinishingRunParameters(275);
	AnimationsPlayer::playWorldFinishedAnimation(world, screen, bgScrollingOffset);
}

//Khi hoan thanh winter world
void showWinterWorldFinishingAnimation(Player &player, World &world, Screen &screen, int bgScrollingOffset)
{
	SoundController::playFlagDownEffect();
	world.switchOnFlag();
	player.setSlidingParameters();
	getPointsFromFlag(player, world);

	while (!world.isFlagDown()) {
		world.performActions();
		screen.updateScreen(world, bgScrollingOffset);
	}
	player.setFinishingRunParameters(185);

	AnimationsPlayer::playCustomWorldFinishedAnimation(world, 77, screen, bgScrollingOffset);
}

//Khi hoan thanh summer world
void showSummerWorldFinishingAnimation(Player &player, World &world, Screen &screen, int bgScrollingOffset)		
{
	AnimationsPlayer::playBridgeSpoilingAnimation(world, screen, bgScrollingOffset);
	player.setFinishingRunParameters(360);
	AnimationsPlayer::playCustomWorldFinishedAnimation(world, 88, screen, bgScrollingOffset);
}

//Ham runGame chua game loop
void runGame()
{
	bool loadResourcesStatus = true;

	Screen screen = Screen();
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(Camera(0, Screen::SCREEN_WIDTH));

	int initStatus = screen.getInitStatus();
	if (initStatus) {
		//Do cai dat trong class Screen nen khi initStatus == 2 tuc la da show file error window roi
		if (initStatus != 2) {							
			showScreenErrorWindow();
		}
		return;
	}

	initSound();

	try {													
		preloadImages(screen.getDisplay());				
	}
	catch (const FileNotLoadedException & e) {
		loadResourcesStatus = false;
		showFileErrorWindow(e.what());
	}

	bool exitStatus = false;
	int gameSpeed = 7;

	bool quit = false;

	int bgScrollingOffset = 0;

	while (true) {
		SoundController::stopMusic();					
		int level = 1, checkPointMark = -1;

		if (loadResourcesStatus) {
			handleMenu(&exitStatus, &gameSpeed, &level, screen, quit);
		}

		if (!loadResourcesStatus || exitStatus || quit) {
			break;
		}

		SDL_Event event;

		const Uint8* state = SDL_GetKeyboardState(nullptr);

		bool playerState = true, winStatus = false, timeState = true;
		

		World world = World();
		world.setGameSpeed(gameSpeed);

		KeyboardController controller = KeyboardController();

		std::shared_ptr<Player> player = std::make_shared<Player>(Player(Position(35, 400)));

		setCameraPointer(*player, world, screen, camera);
		setPlayerPointer(world, screen, player);

		screen.setLevel(level);

		while (player->getLives() && !winStatus) {
			if (checkPointMark == -1) {
				setWorld(level, *player, world, playerState);		
				playerState = true;
				screen.drawStartScreen();
			}
			else {
				screen.drawChangeStageOfLevelScreen();
				setSubWorld(level, checkPointMark, *player, world);		
			}
			adjustCamera(level, checkPointMark);
			resetScreen(screen, level, checkPointMark);			

			if (isPlayerExitingPipe(level, checkPointMark)) {
				AnimationsPlayer::playMarioPipeTravellingAnimation(world, Direction::Up, screen, bgScrollingOffset);		
			}

			SoundController::playBackgroundMusic();

			while (playerState && timeState && !winStatus) {
				if (bgScrollingOffset < -Screen::SCREEN_WIDTH)
				{
					bgScrollingOffset = 0;
				}
				screen.updateScreen(world, bgScrollingOffset);

				while (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						quit = true;
						break;
					}

					if (state[SDL_SCANCODE_RIGHT]) {
						--bgScrollingOffset;
					}

					//forceActions : ham quan ly arrows va spacebar
					if (playerState) {
						controller.handleKeysState(state);
						controller.forceActions(*player, world);

						if (player->isDead()) {
							playerState = false;
						}
						controller.clearKeysState();
					}
				}

				if (quit) {
					break;
				}

				if (playerState) {
					controller.forceActions(*player, world);
				}

				checkPointMark = world.getLastReachedCheckPointMark();
				if (checkPointMark != -1) {
					SoundController::playPipeTravelEffect();

					if (isPlayerEnteringPipe(level, checkPointMark)) {
						AnimationsPlayer::playMarioPipeTravellingAnimation(world, Direction::Down, screen, bgScrollingOffset);	
					}
					break;
				}

				if (world.isPlayerFinishingWorld() && !winStatus) {
					if (isLevelClassic(level)) {
						if (isLevelTheLast(level)) {
							showWorldFinishingAnimation(*player, world, screen, bgScrollingOffset);			
							winStatus = true;
						}
						else {
							showLevelFinishingAnimation(*player, world, screen, level, bgScrollingOffset);			
							++level;
							screen.setLevel(level);
						}
						break;
					}
					else if (isLevelCustom(level)) {
						if (level == 77) {
							showWinterWorldFinishingAnimation(*player, world, screen, bgScrollingOffset);		
						}
						else {
							showSummerWorldFinishingAnimation(*player, world, screen, bgScrollingOffset);		
						}

						winStatus = true;
						break;
					}
				}

				if (player->isDead()) {
					playerState = false;
				}
				else if (screen.isTimePassed() && !winStatus) {
					timeState = false;
				}
			}

			if (quit) {
				break;
			}

			if (!playerState) {
				AnimationsPlayer::playMarioDyingAnimation(world, screen, bgScrollingOffset);			
			}
			else if (!timeState) {
				screen.drawTimeUpScreen();
				SoundController::playTimePassedMusic();
			}
		}

		if (quit) {
			break;
		}

		if (!winStatus) {
			SoundController::playGameOverMusic();
			screen.drawGameOverScreen();
		}
	}

	SoundController::closeSoundController();
}
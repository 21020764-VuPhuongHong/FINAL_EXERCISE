#include "MenuManager.h"
#include "SoundController.h"
#include "Screen.h"			


std::array<SDL_Surface*, 12> MenuManager::SubmenuManager::submenuImages;
std::array<SDL_Surface*, 9> MenuManager::SubmenuManager::digitImages;
std::array<SDL_Surface*, 12> MenuManager::menuImages;
std::array<SDL_Surface*, 3> MenuManager::HelpBoxManager::helpBoxImages;

std::array<MouseButton, 4> menuButtons;
std::array<MouseButton, 7> submenuButtons;
MouseButton helpBoxButton;

//Cai dat kich thuoc va toa do cac nut bam tren submenu
void setSubmenuButtonsPosition() 
{
	submenuButtons[0].setButtonDimensions(36, 45);
	submenuButtons[0].setPosition(118, 49);
	submenuButtons[1].setButtonDimensions(26, 45);
	submenuButtons[1].setPosition(506, 49);
	submenuButtons[2].setButtonDimensions(36, 45);
	submenuButtons[2].setPosition(117, 155);
	submenuButtons[3].setButtonDimensions(26, 45);
	submenuButtons[3].setPosition(516, 155);
	submenuButtons[4].setButtonDimensions(36, 45);
	submenuButtons[4].setPosition(118, 252);
	submenuButtons[5].setButtonDimensions(26, 45);
	submenuButtons[5].setPosition(512, 251);
	submenuButtons[6].setButtonDimensions(142, 55);
	submenuButtons[6].setPosition(246, 361);
}

void MenuManager::SubmenuManager::loadSubmenuSprites(SDL_Surface* display)
{
	submenuImages[0] = loadPNG("img/menu_imgs/submenu.png", display);
	submenuImages[1] = loadPNG("img/menu_imgs/menu_return1.png", display);
	submenuImages[2] = loadPNG("img/menu_imgs/menu_return2.png", display);
	submenuImages[3] = loadPNG("img/menu_imgs/menu_classic.png", display);
	submenuImages[4] = loadPNG("img/menu_imgs/menu_custom.png", display);
	submenuImages[5] = loadPNG("img/menu_imgs/arrow_left_button1.png", display);
	submenuImages[6] = loadPNG("img/menu_imgs/arrow_right_button1.png", display);
	submenuImages[7] = loadPNG("img/menu_imgs/menu_winter_world.png", display);
	submenuImages[8] = loadPNG("img/menu_imgs/menu_summer_world.png", display);
	submenuImages[9] = loadPNG("img/menu_imgs/menu_third_option.png", display);
	submenuImages[10] = loadPNG("img/menu_imgs/arrow_left_button2.png", display);
	submenuImages[11] = loadPNG("img/menu_imgs/arrow_right_button2.png", display);
}

void MenuManager::SubmenuManager::loadSubmenuDigits(SDL_Surface* display)
{
	for (std::size_t i = 0; i < digitImages.size(); ++i) {
		std::string filename = "img/submenu_digit_imgs/";
		filename += std::to_string(i + 1);
		filename += ".png";
		digitImages[i] = loadPNG(filename, display);
	}
}

//winter world co index la 7 vi anh menu_winter_world duoc load vao submenuImages[7], tuong tu voi index cua summer world 
int MenuManager::SubmenuManager::getCustomWorldIndex() const
{
	return (customWorld == CustomWorld::WinterWorld ? 7 : 8);
}

void MenuManager::SubmenuManager::changeCustomWorld()
{
	if (customWorld == CustomWorld::WinterWorld) {
		customWorld = CustomWorld::SummerWorld;
	}
	else {
		customWorld = CustomWorld::WinterWorld;
	}
}

MenuManager::SubmenuManager::SubmenuManager()
{
	gameSpeed = 7;
	customGame = false;
	returnStatus = false;
	customWorld = CustomWorld::WinterWorld;
}

void MenuManager::SubmenuManager::resetReturnStatus()
{
	returnStatus = false;
}

void MenuManager::SubmenuManager::loadSubmenuImages(SDL_Surface* display)
{
	loadSubmenuSprites(display);
	loadSubmenuDigits(display);
}

//Hien thi submenu
void MenuManager::SubmenuManager::drawSubmenu(Screen& screen) const
{
	drawSurface(screen.getDisplay(), submenuImages[0], 320, 240);
	drawSurface(screen.getDisplay(), submenuImages[3 + static_cast<int>(customGame)], 435, 174);
	drawSurface(screen.getDisplay(), digitImages[gameSpeed - 1], 450, 75);
	drawSurface(screen.getDisplay(), submenuButtons[0].getCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT ?
																		submenuImages[5] : submenuImages[10], 136, 72);
	drawSurface(screen.getDisplay(), submenuButtons[1].getCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT ?
																		submenuImages[6] : submenuImages[11], 519, 72);
	drawSurface(screen.getDisplay(), submenuButtons[2].getCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT ?
																		submenuImages[5] : submenuImages[10], 135, 178);
	drawSurface(screen.getDisplay(), submenuButtons[3].getCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT ?
																		submenuImages[6] : submenuImages[11], 529, 178);
	if (customGame) {
		drawSurface(screen.getDisplay(), submenuImages[9], 335, 280);
		drawSurface(screen.getDisplay(), submenuImages[getCustomWorldIndex()], 439, 280);
		drawSurface(screen.getDisplay(), submenuButtons[4].getCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT ?
																		submenuImages[5] : submenuImages[10], 136, 275);
		drawSurface(screen.getDisplay(), submenuButtons[5].getCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT ?
																		submenuImages[6] : submenuImages[11], 529, 274);
	}

	drawSurface(screen.getDisplay(), submenuButtons[6].getCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT ?
																		submenuImages[1] : submenuImages[2], 323, 392);

	screen.updateView();
}

//Quan ly tuong tac chuot voi cac nut bam cua submenu
void MenuManager::SubmenuManager::handleEachSubmenuButton()
{
	if (submenuButtons[0].getCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) {
		gameSpeed--;
		if (gameSpeed == 0) {
			gameSpeed = 9;
		}
		SoundController::playSubmenuEffect();
		submenuButtons[0].freeCurrentSpriteToUp();
	}
	else if (submenuButtons[1].getCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) {
		gameSpeed++;
		if (gameSpeed == 10) {
			gameSpeed = 1;
		}
		SoundController::playSubmenuEffect();
		submenuButtons[1].freeCurrentSpriteToUp();
	}
	else if (submenuButtons[2].getCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) {
		customGame = !customGame;
		SoundController::playSubmenuEffect();
		submenuButtons[2].freeCurrentSpriteToUp();
	}
	else if (submenuButtons[3].getCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) {
		customGame = !customGame;
		SoundController::playSubmenuEffect();
		submenuButtons[3].freeCurrentSpriteToUp();
	}
	else if (submenuButtons[4].getCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) {
		changeCustomWorld();
		SoundController::playSubmenuEffect();
		submenuButtons[4].freeCurrentSpriteToUp();
	}
	else if (submenuButtons[5].getCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) {
		changeCustomWorld();
		SoundController::playSubmenuEffect();
		submenuButtons[5].freeCurrentSpriteToUp();
	}
	else if (submenuButtons[6].getCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) {
		SoundController::playReturnedToMenuEffect();
		returnStatus = true;
		submenuButtons[6].freeCurrentSpriteToUp();
		return;
	}
}

void MenuManager::SubmenuManager::handleSubmenuButtons(SDL_Event& event)
{
	setSubmenuButtonsPosition();
	for (int i = 0; i < 7; ++i)
	{
		submenuButtons[i].handleEvent(event);
		if (returnStatus)
			return;
	}

	handleEachSubmenuButton();
}

//Cai dat kich thuoc va toa do cua nut return tren helpbox
void setHelpBoxButtonPosition() 
{
	helpBoxButton.setButtonDimensions(130, 48);
	helpBoxButton.setPosition(245, 311);
}

void MenuManager::HelpBoxManager::loadHelpBoxImages(SDL_Surface* display) 
{
	helpBoxImages[0] = loadPNG("img/menu_imgs/help_box.png", display);
	helpBoxImages[1] = loadPNG("img/menu_imgs/menu_return1.png", display);
	helpBoxImages[2] = loadPNG("img/menu_imgs/menu_return2.png", display);
}

void MenuManager::HelpBoxManager::drawHelpBox(Screen& screen) const
{
	drawSurface(screen.getDisplay(), helpBoxImages[0], 320, 240);
	drawSurface(screen.getDisplay(), helpBoxButton.getCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT ?
																		helpBoxImages[1] : helpBoxImages[2], 310, 335);

	screen.updateView();
}

MenuManager::HelpBoxManager::HelpBoxManager()
{
	returnStatus = false;
}

void MenuManager::HelpBoxManager::resetReturnStatus()
{
	returnStatus = false;
}

//Quan ly tuong tac chuot voi nut return tren helpbox
void MenuManager::HelpBoxManager::handleHelpBoxButton(SDL_Event& event)
{
	setHelpBoxButtonPosition();
	helpBoxButton.handleEvent(event);

	if (helpBoxButton.getCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) {
		SoundController::playReturnedToMenuEffect();
		helpBoxButton.freeCurrentSpriteToOut();
		returnStatus = true;
		return;
	}
}

//Cai dat kich thuoc va toa do cac nut bam tren main_menu cua game
void setMenuButtonsPosition()
{
	menuButtons[0].setButtonDimensions(140, 60);
	menuButtons[0].setPosition(415, 80);
	menuButtons[1].setButtonDimensions(140, 60);
	menuButtons[1].setPosition(415, 145);
	menuButtons[2].setButtonDimensions(140, 60);
	menuButtons[2].setPosition(415, 210);
	menuButtons[3].setButtonDimensions(140, 60);
	menuButtons[3].setPosition(415, 275);
}

void MenuManager::loadMenuImages(SDL_Surface* display)
{
	menuImages[0] = loadPNG("img/menu_imgs/menu.png", display);
	menuImages[1] = loadPNG("img/menu_imgs/menu_textbox.png", display);
	menuImages[2] = loadPNG("img/menu_imgs/SUPERMARIO_text.png", display);
	menuImages[3] = loadPNG("img/menu_imgs/menu_button_textbox.png", display);
	menuImages[4] = loadPNG("img/menu_imgs/menu_play_button1.png", display);
	menuImages[5] = loadPNG("img/menu_imgs/menu_options_button1.png", display);
	menuImages[6] = loadPNG("img/menu_imgs/menu_help_button1.png", display);
	menuImages[7] = loadPNG("img/menu_imgs/menu_exit_button1.png", display);
	menuImages[8] = loadPNG("img/menu_imgs/menu_play_button2.png", display);
	menuImages[9] = loadPNG("img/menu_imgs/menu_options_button2.png", display);
	menuImages[10] = loadPNG("img/menu_imgs/menu_help_button2.png", display);
	menuImages[11] = loadPNG("img/menu_imgs/menu_exit_button2.png", display);

	SubmenuManager::loadSubmenuImages(display);
	HelpBoxManager::loadHelpBoxImages(display);
}

//Hien thi main_menu
void MenuManager::drawMainMenu(Screen &screen) const
{
	drawSurface(screen.getDisplay(), menuImages[0], 320, 240);
	drawSurface(screen.getDisplay(), menuImages[1], 200, 160);	
	drawSurface(screen.getDisplay(), menuImages[2], 208, 190);
	drawSurface(screen.getDisplay(), menuImages[3], 485, 110);
	drawSurface(screen.getDisplay(), menuImages[3], 485, 175);
	drawSurface(screen.getDisplay(), menuImages[3], 485, 240);
	drawSurface(screen.getDisplay(), menuImages[3], 485, 305);
	drawSurface(screen.getDisplay(), menuButtons[0].getCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT ? 
																		menuImages[4] : menuImages[8], 487, 110);
	drawSurface(screen.getDisplay(), menuButtons[1].getCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT ?
																		menuImages[5] : menuImages[9], 487, 175);
	drawSurface(screen.getDisplay(), menuButtons[2].getCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT ?
																		menuImages[6] : menuImages[10], 488, 240);
	drawSurface(screen.getDisplay(), menuButtons[3].getCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT ?
																		menuImages[7] : menuImages[11], 488, 305);

	screen.updateView();
}

//Quan ly tuong tac chuot voi cac nut bam tren main_menu
void MenuManager::handleEachMenuButton()
{
	if (menuButtons[0].getCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) {
		startGameStatus = true;
		menuButtons[0].freeCurrentSpriteToOut();
		SoundController::playSubmenuEffect();
	}
	else if (menuButtons[1].getCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) {
		submenu = true;
		menuButtons[1].freeCurrentSpriteToOut();
		SoundController::playSubmenuEffect();
	}
	else if (menuButtons[2].getCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) {
		help = true;
		menuButtons[2].freeCurrentSpriteToOut();
		SoundController::playSubmenuEffect();
	}
	else if (menuButtons[3].getCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) {
		exitStatus = true;
		menuButtons[3].freeCurrentSpriteToOut();
		SoundController::playSubmenuEffect();
	}
}

void MenuManager::handleMenuButtons(SDL_Event& event)
{
	setMenuButtonsPosition();
	for (int i = 0; i < 4; ++i)
	{
		menuButtons[i].handleEvent(event);
	}
	handleEachMenuButton();
}

MenuManager::MenuManager()
{
	startGameStatus = false;
	exitStatus = false;
	help = false;
	submenu = false;
	submenuManager = SubmenuManager();
	helpBoxManager = HelpBoxManager();
}

bool MenuManager::isStillOpen() const
{
	if (!startGameStatus && !exitStatus) {
		return true;
	}

	return false;
}

bool MenuManager::getExitStatus() const
{
	return exitStatus;
}

int MenuManager::getGameSpeed() const
{
	return submenuManager.gameSpeed;
}

int MenuManager::getLevel() const
{
	if (submenuManager.customGame) {
		return (submenuManager.customWorld == CustomWorld::WinterWorld ? 77 : 88);				
	}

	return 1;
}

//Quyet dinh hien thi main_menu/ submenu/ helpbox
void MenuManager::drawMenu(Screen &screen)
{
	if (submenuManager.returnStatus) {
		submenu = false;
		submenuManager.resetReturnStatus();
	}
	if (helpBoxManager.returnStatus) {
		help = false;
		helpBoxManager.resetReturnStatus();
	}

	if (!submenu && !help) {
		drawMainMenu(screen);
	}
	else if (submenu && !help) {
		submenuManager.drawSubmenu(screen);
	}
	else if (help && !submenu) {
		helpBoxManager.drawHelpBox(screen);
	}
}

//Quan ly tuong tac chuot tren menu game
void MenuManager::handleMouse(SDL_Event& event)
{
	if (!submenu && !help) {
		handleMenuButtons(event);
	}
	else if (submenu && !help) {
		submenuManager.handleSubmenuButtons(event);
	}
	else if (help && !submenu) {
		helpBoxManager.handleHelpBoxButton(event);
	}
}
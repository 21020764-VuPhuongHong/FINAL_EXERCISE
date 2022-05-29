#ifndef MenuManager_H
#define MenuManager_H

#include <array>
#include "SDL_Utility.h"
#include "HandleMouse.h"

class Screen;
struct SDL_Surface;
class MouseButton;


enum class CustomWorld
{
	WinterWorld,
	SummerWorld
};


void setMenuButtonsPosition();
void setHelpBoxButtonPosition();
void setSubmenuButtonsPosition();

class MenuManager
{
private:
	class SubmenuManager
	{
	private:
		static std::array<SDL_Surface*, 12> submenuImages;
		static std::array<SDL_Surface*, 9> digitImages;
		static void loadSubmenuSprites(SDL_Surface* display);
		static void loadSubmenuDigits(SDL_Surface* display);
		int getCustomWorldIndex() const;
		void changeCustomWorld();
		void handleEachSubmenuButton();

	public:
		int gameSpeed;
		bool customGame;
		bool returnStatus;
		CustomWorld customWorld;
		SubmenuManager();
		static void loadSubmenuImages(SDL_Surface* display);
		void resetReturnStatus();
		void drawSubmenu(Screen &screen) const;
		void handleSubmenuButtons(SDL_Event& event);
	};

	class HelpBoxManager
	{
	private:
		static std::array<SDL_Surface*, 3> helpBoxImages;
		
	public:
		bool returnStatus;
		HelpBoxManager();
		static void loadHelpBoxImages(SDL_Surface* display);
		void resetReturnStatus();
		void drawHelpBox(Screen& screen) const;
		void handleHelpBoxButton(SDL_Event& event);
		
	};

	static std::array<SDL_Surface*, 12> menuImages;
	bool startGameStatus;
	bool exitStatus;
	bool help;
	bool submenu;
	SubmenuManager submenuManager;
	HelpBoxManager helpBoxManager;
	void drawMainMenu(Screen &screen) const;
	void handleEachMenuButton();
	void handleMenuButtons(SDL_Event& event);

public:
	MenuManager();
	static void loadMenuImages(SDL_Surface* display);
	bool isStillOpen() const;
	bool getExitStatus() const;
	int getGameSpeed() const;
	int getLevel() const;
	void drawMenu(Screen &screen);
	void handleMouse(SDL_Event& event);
};

#endif 
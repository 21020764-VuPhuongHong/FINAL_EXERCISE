#include "FireMissile.h"
#include "SoundController.h"
#include "SDL_Utility.h"
#include "Player.h"
#include "World.h"
#include "CollisionHandling.h"


std::array<SDL_Surface*, 3> FireMissile::missileImages;

bool FireMissile::isRightTime()
{
	auto timePoint = std::chrono::steady_clock::now();
	auto difference = std::chrono::duration_cast<std::chrono::milliseconds>(timePoint - lastSoundTime).count();
	if (difference > 4500) {
		return true;
	}

	return false;
}

void FireMissile::changeModel()
{
	++changeModelCounter;
	if (changeModelCounter % 7 == 0) {
		model = (model == 1 ? 2 : 1);
	}
}

//Dieu chinh toa do y de bomb roi xuong
void FireMissile::fallDown(World &world)
{
	int alignment = computeVerticalAlignment(Direction::Down, movement.getVerticalSpeed(), *this, world);
	int distance = movement.getVerticalSpeed() - alignment;

	if (distance != 0) {
		position.setY(position.getY() + distance);
	}
	else {
		inactive = true;
	}
}

//Dieu chinh toa do x de rocket bay sang trai
void FireMissile::moveLeft(World &world)
{
	int alignment = computeHorizontalAlignment(Direction::Left, movement.getSpeed(), *this, world);
	int distance = movement.getSpeed() - alignment;

	if (distance != 0) {
		position.setX(position.getX() - distance);
		changeModel();

		if (isRightTime() && isPlayerCloseToFireRocket(*this, world)) {
			lastSoundTime = std::chrono::steady_clock::now();
			SoundController::playFireRocketEffect();
		}
	}
	else {
		inactive = true;
	}
}

//Quyet dinh loai hoa tien la bomb hay rocket
int FireMissile::computeImageIndex() const
{
	return (missileType == MissileType::Bomb ? 2 : model - 1);
}

FireMissile::FireMissile(Position position, MissileType type)
{
	this->position = position;
	moveCounter = 0;
	changeModelCounter = 0;
	healthPoints = 2; 
	inactive = false;
	model = 1;
	missileType = type;
	lastSoundTime = std::chrono::steady_clock::now();
	movement = Movement(1, 1, Direction::None, Direction::None);
	size = Size(50, 16);

	if (type == MissileType::Bomb) {
		movement.setVerticalDirection(Direction::Down);
		size.setSize(20, 22);
	}
}

void FireMissile::loadFireRocketImages(SDL_Surface* display)
{
	missileImages[0] = loadPNG("img/npc_imgs/fire_rocket1.png", display);
	missileImages[1] = loadPNG("img/npc_imgs/fire_rocket2.png", display);
	missileImages[2] = loadPNG("img/npc_imgs/fire_bomb.png", display);
}

bool FireMissile::shouldStartMoving(const Player &player) const
{
	if (movement.getDirection() == Direction::None && position.getX() < player.getX() + 480) {
		return true;
	}

	return false;
}

//Mario khong the nhay len de tieu diet hoa tien (can't be crushed)
bool FireMissile::isCrushproof() const
{
	return true;
}

//Hoa tien co the tieu diet Mario ngay ca o che do Immortal Mario 
bool FireMissile::isResistantToImmortalPlayer() const
{
	return true;
}

//Mario khong the dung fireball pha huy hoa tien
bool FireMissile::isResistantToFireBalls() const
{
	return true;
}

void FireMissile::startMoving()
{
	movement.setDirection(Direction::Left);
}

//Hieu ung chay no khi cham vao vat nao do
void FireMissile::performSpecificActions(World &world, int index)
{
	if (inactive) {
		Position explosionPosition = position;
		if (missileType == MissileType::Bomb) {
			explosionPosition.setY(position.getY() + 7);
		}

		world.deleteNpc(index);
		world.addExplosion(explosionPosition);
	}
}

//Dieu khien di chuyen cua hoa tien tuy loai
void FireMissile::move(World &world)
{
	if (missileType == MissileType::Bomb) {
		fallDown(world);
	}
	else {
		if (movement.getDirection() == Direction::Left) {
			moveLeft(world);
		}
	}
}

void FireMissile::draw(SDL_Surface* display, int beginningOfCamera, int endOfCamera) const
{
	if (isWithinRangeOfCamera(beginningOfCamera, endOfCamera) && !inactive) {
		drawSurface(display, missileImages[computeImageIndex()], position.getX() - beginningOfCamera, position.getY());
	}
}
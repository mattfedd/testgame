#include "Item.h"
#include "Game.h"

Item::Item(void)
{
	setEntityType(ENTITY_TYPE::ITEM);
	setAnimState(ANIM_STATE::DEFAULT);
}


Item::~Item(void)
{
}

void Item::updateInput()
{

}

void Item::initCollisionBoxes()
{
	/*collideBoxes.push_back(new CollideBox(0,0,getWidth(), getHeight()));*/
}

void Item::handleCollision(Entity* ent, CollideBox* us, CollideBox* e)
{
	if(getAnimState() != ANIM_STATE::DEATH) onCollect();
	setAnimState(ANIM_STATE::DEATH);
}

void Item::onCollect()
{

}

//----------------------------------------------------------

HealthPickupItem::HealthPickupItem(unsigned int amount) : Item()
{
	healthRestored = amount;
	setWidth(32 * amount/5);
	setHeight(32 * amount/5);
	initCollisionBoxes();
}

HealthPickupItem::~HealthPickupItem()
{

}

void HealthPickupItem::initCollisionBoxes()
{
	collideBoxes.push_back(new CollideBox(0,0,getWidth(), getHeight()));
}

void HealthPickupItem::onCollect()
{
	GAME->getPlayer()->addHealth(healthRestored);
	LOGI("HEALTH_PICKUP", "Restoring %d health, current health is %d out of %d", healthRestored, GAME->getPlayer()->getHealth(), GAME->getPlayer()->getMaxHealth());
}

HealthPickupItemSprite::HealthPickupItemSprite(int width, int height, SpriteSheet* ss) : Sprite(width, height, ss)
{
	totalFrames_ = 0;
	numAnimations_ = 0;
	sheetWidth_ = 128;
	sheetHeight_ = 128;
	frameWidth_ = 16;
	frameHeight_ = 16;

	spriteInfo_ = NULL;
	
	addAnimInfo(ANIM_STATE::DEFAULT, 1);

	setAnimState(ANIM_STATE::DEFAULT);
}

HealthPickupItemSprite::~HealthPickupItemSprite()
{

}

//-----------------------------------------------------------

#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Weapon.h"

class Player : public Entity
{
private:
	float gravity;
	bool goingUp;
	bool floating;
	float force;

	ATTACK_STATE attack_state;

	Weapon* weapon;

	struct PlayerPermissions {
		bool canAttack;
		bool canUseMagic;
		bool canJump;
		bool canCrouch;
		bool canMove;
		bool canSwitchDirection;
		bool canInteract;
		bool canTakeDamage;
	};

	struct PlayerState {
		bool isAttacking;
		bool isCastingSpell;
		bool isInAir;
		bool isCrouching;
		bool isMoving;
	};

	PlayerPermissions permissions_;
	PlayerState state_;

public:
	Player(void);
	~Player(void);

	void updateInput();
	//void handleCollision(Entity* ent, CollideBox* us, CollideBox* e);

	void crouch();
	void uncrouch();
	void attackGroundHigh();
	void attackGroundMid();
	void attackGroundLow();

	void initCollisionBoxes();

	Weapon* getWeapon();
	void setWeapon(Weapon* weapon);

	//void addDamageBox(int relativeX, int relativeY, int width, int height, int lifetime, int damage);

};

class PlayerSprite : public Sprite
{
public:
	PlayerSprite(int width, int height, SpriteSheet* ss): Sprite(width, height, ss)
	{
		
		totalFrames_ = 0;
		numAnimations_ = 0;
		sheetWidth_ = 512;
		sheetHeight_ = 256;
		frameWidth_ = 64;
		frameHeight_ = 64;

		spriteInfo_ = NULL;
	
		addAnimInfo(ANIM_STATE::DEFAULT, 8);
		addAnimInfo(ANIM_STATE::STAND_MOVE, 8);
		addAnimInfo(ANIM_STATE::CROUCH, 1);

		setAnimState(ANIM_STATE::STAND_MOVE);
	}
	~PlayerSprite(void) {}
};




#endif

#include "PlayerInputSystem.h"
#include "Components.h"
#include "Game.h"

PlayerInputSystem::PlayerInputSystem()
{
	spaceDown = false;

	jumpBuffer = alutCreateBufferFromFile("res/jump.wav");
	alGenSources (1, &jumpSource);
	alSourcei (jumpSource, AL_BUFFER, jumpBuffer);

}

PlayerInputSystem::~PlayerInputSystem()
{

}

void PlayerInputSystem::update(EntityManager* em)
{
	//get player position data
	PhysicsComponent& phys =  em->getComponentVector<PhysicsComponent>()->get(em->getEntities().get(0).components[PHYSICS_ID]);
	Sprite& sprite = em->getComponentVector<SpriteComponent>()->get(em->getEntities().get(0).components[SPRITE_ID]).sprite;
	
	ANIM_STATE temp = ANIM_STATE::DEFAULT;
	
	if(glfwGetKey(GLFW_KEY_UP))
	{
		phys.dy = 5;
		temp=ANIM_STATE::STAND_MOVE;
	}
	//if(glfwGetKey(GLFW_KEY_DOWN))
	//{
	//	
	//}
	if(glfwGetKey(GLFW_KEY_RIGHT))
	{
		phys.dx +=1;
		sprite.setDirection(DIRECTION::RIGHT);
		temp=ANIM_STATE::STAND_MOVE;
	}
	if(glfwGetKey(GLFW_KEY_LEFT))
	{
		phys.dx -=1;
		sprite.setDirection(DIRECTION::LEFT);
		temp=ANIM_STATE::STAND_MOVE;
	}

	if(glfwGetKey(GLFW_KEY_SPACE)==GLFW_PRESS && !spaceDown)
	{
		spaceDown = true;
		alSourcePlay (jumpSource);
		GAME->setScore(GAME->getScore()+1);
	}
	else if(glfwGetKey(GLFW_KEY_SPACE)==GLFW_RELEASE)
		spaceDown = false;

	sprite.setAnimState(temp);


}
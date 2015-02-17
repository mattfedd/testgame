#include "PlayerInputSystem.h"
#include "Components.h"

PlayerInputSystem::PlayerInputSystem()
{

}

PlayerInputSystem::~PlayerInputSystem()
{

}

void PlayerInputSystem::update(EntityManager* em)
{
	//get player position data
	PositionComponent& pos =  em->getComponentVector<PositionComponent>()->get(em->getEntities().get(0).components[POSITION_ID]);

	if(glfwGetKey(GLFW_KEY_UP))
	{
		pos.y+=5;
	}
	if(glfwGetKey(GLFW_KEY_DOWN))
	{
		pos.y -= 5;
	}
	if(glfwGetKey(GLFW_KEY_RIGHT))
	{
		pos.x += 5;
	}
	if(glfwGetKey(GLFW_KEY_LEFT))
	{
		pos.x -= 5;
	}

}
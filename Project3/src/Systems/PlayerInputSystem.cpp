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
	PhysicsComponent& phys =  em->getComponentVector<PhysicsComponent>()->get(em->getEntities().get(0).components[PHYSICS_ID]);

	if(glfwGetKey(GLFW_KEY_UP))
	{
		phys.dy = 5;
	}
	//if(glfwGetKey(GLFW_KEY_DOWN))
	//{
	//	
	//}
	if(glfwGetKey(GLFW_KEY_RIGHT))
	{
		phys.dx +=1;
	}
	if(glfwGetKey(GLFW_KEY_LEFT))
	{
		phys.dx -=1;
	}



}
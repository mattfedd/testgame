#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(void) : Weapon()
{
	inUse = false;
	
	//TODO: make this data come from an external file

	HitboxData* mid1 = new HitboxData();
	mid1->relativeX = 65;
	mid1->relativeY = 50;
	mid1->width = 100;
	mid1->height = 50;
	mid1->delayUntilSpawn = 100;
	mid1->lifetime = 200;
	mid1->damage = 10;
	mid1->next = NULL;

	MidAttack.lifetime = 450;
	MidAttack.hitboxes = mid1;

	HitboxData* low1 = new HitboxData();
	low1->relativeX = 65;
	low1->relativeY = 20;
	low1->width = 100;
	low1->height = 50;
	low1->delayUntilSpawn = 250;
	low1->lifetime = 400;
	low1->damage = 10;
	low1->next = NULL;

	HitboxData* low2 = new HitboxData();
	low2->relativeX = 100;
	low2->relativeY = 20;
	low2->width = 50;
	low2->height = 50;
	low2->delayUntilSpawn = 800;
	low2->lifetime = 200;
	low2->damage = 10;
	low2->next = low1;

	LowAttack.lifetime = 1200;
	LowAttack.hitboxes = low2;
}

MeleeWeapon::~MeleeWeapon(void)
{
	
}

void MeleeWeapon::attackMid()
{
	attack(MidAttack);
}

void MeleeWeapon::attackLow()
{
	attack(LowAttack);
}

void MeleeWeapon::attack(AttackData ad)
{
	if(!inUse)
		timeStamp = glfwGetTime();

	inUse = true;
	
	double delta = (glfwGetTime()-timeStamp)*1000;

	if(delta > ad.lifetime)
	{
		inUse = false;
		
		if(!ad.hitboxes == NULL)
		{
			HitboxData* temp = ad.hitboxes;
			temp->added = false;
			while(temp->next !=NULL)
			{
				temp = temp->next;
				temp->added = false;
			}
		}

		return;
	}

	if(ad.hitboxes == NULL)
	{
		return;
	}

	HitboxData* h = ad.hitboxes;
	if(delta > h->delayUntilSpawn && !h->added)
	{
		/*parent->addDamageBox(h->relativeX, h->relativeY, 
			h->width, h->height, 
			h->lifetime, h->damage);*/
		h->added = true;
	}

	while(h->next != NULL)
	{
		h = h->next;
		if(delta > h->delayUntilSpawn && !h->added)
		{
			/*parent->addDamageBox(h->relativeX, h->relativeY, 
				h->width, h->height, 
				h->lifetime, h->damage);*/
			h->added = true;
		}
	}
}
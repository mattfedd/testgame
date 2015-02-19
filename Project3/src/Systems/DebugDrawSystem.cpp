#include "DebugDrawSystem.h"
#include "Components.h"
#include "Game.h"

DebugDrawSystem::DebugDrawSystem(void)
{
}


DebugDrawSystem::~DebugDrawSystem(void)
{
}

void DebugDrawSystem::update(EntityManager* em)
{
	//get all the collision components
	Container<CollisionComponent>* collisionComps = em->getComponentVector<CollisionComponent>();

	//get all the position components
	Container<PositionComponent>* positionComps = em->getComponentVector<PositionComponent>();
	
	//get "all" text components, maybe there should be different types?
	Container<TextComponent>* textComponents = em->getComponentVector<TextComponent>();

	//get entities with both position and collision
	Container<Entity> ents = em->getEntities();
	for(int i=0; i<CONTAINER_SIZE; ++i)
	{
		unsigned int collisionIndex = ents.get(i).components[COLLISION_ID];
		unsigned int positionIndex = ents.get(i).components[POSITION_ID];
		unsigned int textIndex = ents.get(i).components[TEXT_ID];
		
		//for each entity that has collision and position
		if(ents.get(i).inUse[COLLISION_ID] && ents.get(i).inUse[POSITION_ID])
		{
			float x = positionComps->get(positionIndex).x;
			float y = positionComps->get(positionIndex).y;
			float z = 0;

			if(GAME->getCamera()->isInBounds(x,y,20))
			{
				CollisionComponent c = collisionComps->get(collisionIndex);

				glPushMatrix();
				glTranslatef(x/SCREEN_WIDTH-GAME->getCamera()->getXNorm(), y/SCREEN_HEIGHT-GAME->getCamera()->getYNorm(), z/Z_CAP);
			
				GLfloat tempVerts[4] = 
				{
					1.0f*(c.AABB.x)/SCREEN_WIDTH,1.0f*(c.AABB.y)/SCREEN_HEIGHT,
					1.0f*(c.AABB.x+c.AABB.width)/SCREEN_WIDTH,1.0f*(c.AABB.y + c.AABB.height)/SCREEN_HEIGHT
				};
				glBindTexture(GL_TEXTURE_2D, NULL);
				glLineWidth(1.5); 
				glColor4f(0.0, 1.0, 0.0, 0.3);

				glBegin(GL_LINES);
				glVertex2f(tempVerts[0], tempVerts[3]);
				glVertex2f(tempVerts[2], tempVerts[3]);
				glEnd();

				glBegin(GL_LINES);
				glVertex2f(tempVerts[2], tempVerts[1]);
				glVertex2f(tempVerts[0], tempVerts[1]);
				glEnd();

				glBegin(GL_LINES);
				glVertex2f(tempVerts[2], tempVerts[3]);
				glVertex2f(tempVerts[2], tempVerts[1]);
				glEnd();

				glBegin(GL_LINES);
				glVertex2f(tempVerts[0], tempVerts[1]);
				glVertex2f(tempVerts[0], tempVerts[3]);
				glEnd();

				glColor4f(1.0,1.0,1.0, 1.0);
		
				glPopMatrix();
			}
		}

		//for all entities with position AND text
		if(ents.get(i).inUse[TEXT_ID] && ents.get(i).inUse[POSITION_ID])
		{
			float x = positionComps->get(positionIndex).x;
			float y = positionComps->get(positionIndex).y;
			float z = 0;

			TextComponent t = textComponents->get(textIndex);
			TextSprite* ts = t.sprite;
	
			glBindTexture(GL_TEXTURE_2D, ts->getSpriteSheet()->getGLuintTexture());

			for(int j=0; j<t.text.size(); ++j)
			{
				ts->setLetter(t.text.at(j));
				ts->calcLetter();
				glPushMatrix();
				glTranslatef((x+t.textSize*j)/SCREEN_WIDTH, y/SCREEN_HEIGHT, z/Z_CAP);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glEnableClientState(GL_VERTEX_ARRAY);
		
				glVertexPointer(3, GL_FLOAT, 0, ts->getVertexPoints());
				glTexCoordPointer(2, GL_FLOAT, 0, ts->getTexturePoints());
				glDrawArrays(GL_QUADS, 0, 4);
	
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);

				glPopMatrix();
			}
			
		}
	}
}
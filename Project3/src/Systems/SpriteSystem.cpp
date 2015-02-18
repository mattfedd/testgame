#include "SpriteSystem.h"
#include "Game.h"

SpriteSystem::SpriteSystem()
{

}

SpriteSystem::~SpriteSystem()
{

}

void SpriteSystem::update(EntityManager* em)
{
	//get all the sprite components
	Container<SpriteComponent>* sprites = em->getComponentVector<SpriteComponent>();

	//get all the position components
	Container<PositionComponent>* positions = em->getComponentVector<PositionComponent>();

	//filter for all the entities that have both sprite and position components
	Container<Object> ents = em->getEntities();
	for(int i=0; i<CONTAINER_SIZE; ++i)
	{
		unsigned int spriteIndex = ents.get(i).components[SPRITE_ID];
		unsigned int positionIndex = ents.get(i).components[POSITION_ID];

		if(ents.get(i).inUse[SPRITE_ID] && ents.get(i).inUse[POSITION_ID])
		{
			//draw that shit
			Sprite s = sprites->get(spriteIndex).sprite;
			float x = positions->get(positionIndex).x;
			float y = positions->get(positionIndex).y;
			float z = positions->get(positionIndex).z;

			if(GAME->getCamera()->isInBounds(x,y,20))
			{
				s.calcNextFrame();
	
				glBindTexture(GL_TEXTURE_2D, s.getSpriteSheet()->getGLuintTexture());

				glPushMatrix();
				glTranslatef(x/SCREEN_WIDTH-GAME->getCamera()->getXNorm(), y/SCREEN_HEIGHT-GAME->getCamera()->getYNorm(), z/Z_CAP);
				glEnableClientState(GL_TEXTURE_COORD_ARRAY);
				glEnableClientState(GL_VERTEX_ARRAY);
		
				glVertexPointer(3, GL_FLOAT, 0, s.getVertexPoints());
				glTexCoordPointer(2, GL_FLOAT, 0, s.getTexturePoints());
				glDrawArrays(GL_QUADS, 0, 4);
	
				glDisableClientState(GL_VERTEX_ARRAY);
				glDisableClientState(GL_TEXTURE_COORD_ARRAY);

				glPopMatrix();
			}
		}
	}
}
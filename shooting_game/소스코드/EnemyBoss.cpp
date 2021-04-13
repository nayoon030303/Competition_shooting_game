#include "stdafx.h"
#include "EnemyBoss.h"
#include "global.h"

EnemyBoss::EnemyBoss()
{
	isDead = false;
	width = 208;
	height = 106;
	state = start;
	hp = 50;
	speed = 50;
	posX = WINDOW_WIDTH/2;
	posY = -(height+30);
	
	velX = 0;
	velY = 0;
}

void EnemyBoss::Render()
{
	TextureElement* element = textureManager.GetTexture(ENEMYBOSS);
	element->g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 208;
	srcRect.bottom = 106;

	D3DXVECTOR3 pos(posX, posY, 0);
	D3DXVECTOR3 cen(width / 2, height / 2, 0);
	if (isHit)
	{
		int randv = rand() % 10;
		if (randv % 2 == 0)
		{
			element->g_Sprite->Draw(element->g_pTexture, &srcRect, &cen, &pos, D3DCOLOR_XRGB(0, 255, 0));
		}isHit = false;

	}
	else
	{
		element->g_Sprite->Draw(element->g_pTexture, &srcRect, &cen, &pos, D3DCOLOR_XRGB(255, 255, 255));
	}

	element->g_Sprite->End();
}

void EnemyBoss::Update()
{
	
	int randValue = rand() % 100;
	switch (state)
	{
	case start:
		velY = speed * deltatime;
		state = stop;
		break;
	case stop:
		if (posY > WINDOW_HEIGHT*0.2)
		{
			velY = 0;
			state = move;
		}
		break;
	case move:
		
		if (randValue %2==0)
		{
			posY += 10*deltatime;
			posX += 10 * deltatime;
			
		}
		else
		{
			posY -= 10 * deltatime;
			posX -= 10 * deltatime;
		}
		break;
	case end:
		endState();
		break;
	default:
		break;
	}
	
	posY += velY;
	posX += velX;
}

D3DXVECTOR2	 EnemyBoss::GetPos()
{
	return	D3DXVECTOR2(posX, posY);
}

void EnemyBoss::Hit(int damage)
{
	hp = hp - damage;
	isHit = true;
	if (hp <= 0)
	{
		
		isDead = true;
		gameSystem.MakeItem(posX, posY);
	}


}

bool EnemyBoss::IsDead()
{
	return isDead;
}


void EnemyBoss::endState()
{
	if (hp<=0)
	{
		isDead = true;
		gameSystem.MakeItem(posX, posY);
	}
}

float EnemyBoss::GetWidth()
{
	return width;
}
float EnemyBoss::GteteHeight()
{
	return height;
}
float EnemyBoss::Getradious()
{
	return 62;
}
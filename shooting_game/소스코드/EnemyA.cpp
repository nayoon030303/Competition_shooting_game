#include "stdafx.h"
#include "EnemyA.h"	
#include "global.h"

EnemyA::EnemyA()
{
	isDead = false;
	state = start;
	width = 56;
	height = 65;

	hp = 5;
	speed = 100;
	posY = -50;
	posX = rand() % 400 + 100;
	velX = 0;
	velY = 0;
}

void EnemyA::Render()
{
	TextureElement* element = textureManager.GetTexture(ENEMYA);
	element->g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 56;
	srcRect.bottom = 65;

	D3DXVECTOR3 pos(posX, posY, 0);
	D3DXVECTOR3 cen(width/2, height/2, 0);
	element->g_Sprite->Draw(element->g_pTexture, &srcRect, &cen, &pos, D3DCOLOR_XRGB(255, 255, 255));

	element->g_Sprite->End();
}

void EnemyA::Update()
{
	switch (state)
	{
	
	case start:
		velY = speed;
		state = move;
		break;
	case move:
		moveState();
		break;
	case movePoint:
		movePointState();
		state = end;
		break;
	case end:
		endState();
		break;
	default:
		break;
	}

	posX += velX * deltatime;
	posY += velY * deltatime;

}

D3DXVECTOR2	 EnemyA::GetPos()
{
	return	D3DXVECTOR2(posX, posY);
}

void EnemyA::Hit(int damage)
{
	hp = hp - damage;
	if (hp <= 0)
	{
		isDead = true;
	}

	
}

bool EnemyA::IsDead()
{
	return isDead;
}


void EnemyA::moveState()
{
	if (posY > WINDOW_HEIGHT*0.3)
	{
		state = movePoint;
	}
	
}

void EnemyA::movePointState()
{
	const int randValue = rand() % 100;
	if(randValue>50)
	{
		velX = -(rand()%200 + 80);
		velY *= 2;
	}
	else
	{
		velX = (rand() % 200 + 80);
		velY *= 2;
	}
}


void EnemyA::endState()
{
	if(posX<0 || posX>WINDOW_WIDTH || posY>WINDOW_HEIGHT)
	{
		isDead = true;
	}
}

float EnemyA::GetWidth()
{
	return width;
}
float EnemyA::GteteHeight()
{
	return height;
}
float EnemyA::Getradious()
{
	return 30;
} 
#include "stdafx.h"
#include "EnemyB.h"
#include "global.h"

EnemyB::EnemyB()
{
	isDead = false;
	width = 32;
	height = 16;

	hp = 2;
	speed = 100;
	int randValue = rand()%100;
	if (randValue > 50) {
		posX = -20;
		state = start1;
	}
	else {
		posX = 660;
		state = start2;
	}
	posY = rand() % 150 ;
	velX = 0;
	velY = 0;
}

void EnemyB::Render()
{
	TextureElement* element = textureManager.GetTexture(ENEMYB);
	element->g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 32;
	srcRect.bottom = 16;

	D3DXVECTOR3 pos(posX, posY, 0);
	D3DXVECTOR3 cen(width / 2, height / 2, 0);
	element->g_Sprite->Draw(element->g_pTexture, &srcRect, &cen, &pos, D3DCOLOR_XRGB(255, 255, 255));

	element->g_Sprite->End();
}

void EnemyB::Update()
{
	switch (state)
	{

	case start1:
		velY = speed;
		velX = 50;
		state = end;
		break;
	case start2:
		velY = speed;
		velX = -speed;
		state = end;
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

D3DXVECTOR2	 EnemyB::GetPos()
{;
	return	D3DXVECTOR2(posX, posY);
}

void EnemyB::Hit(int damage)
{
	hp = hp - damage;
	if (hp <= 0)
	{
		isDead = true;
	}


}

bool EnemyB::IsDead()
{
	return isDead;
}


void EnemyB::moveState()
{
	if (posY > WINDOW_HEIGHT*0.5)
	{
		state = movePoint;
	}

}

void EnemyB::movePointState()
{
	const int randValue = rand() % 100;
	if (randValue>50)
	{
		velX = -(rand() % 200 + 80);
		velY *= 2;
	}
	else
	{
		velX = (rand() % 200 + 80);
		velY *= 2;
	}
}


void EnemyB::endState()
{
	if (posY>WINDOW_HEIGHT)
	{
		isDead = true;
	}
}

float EnemyB::GetWidth()
{
	return width;
}
float EnemyB::GteteHeight()
{
	return height;
}
float EnemyB::Getradious()
{
	return 30;
}
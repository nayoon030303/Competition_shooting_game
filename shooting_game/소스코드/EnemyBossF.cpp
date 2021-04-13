#include "stdafx.h"
#include "EnemyBossF.h"
#include "global.h"

EnemyBossF::EnemyBossF()
{
	isDead = false;
	width = 208;
	height = 106;
	state = start;
	hp = 50;
	speed = 50;
	posX = WINDOW_WIDTH / 2;
	posY = -(height + 30);

	velX = 0;
	velY = 0;
}

void EnemyBossF::Render()
{
	TextureElement* element = textureManager.GetTexture(EENMYBOSSF);
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
			element->g_Sprite->Draw(element->g_pTexture, &srcRect, &cen, &pos, D3DCOLOR_XRGB(255, 255, 0));
		}isHit = false;

	}
	else
	{
		element->g_Sprite->Draw(element->g_pTexture, &srcRect, &cen, &pos, D3DCOLOR_XRGB(0, 255, 0));
	}

	element->g_Sprite->End();
}

void EnemyBossF::Update()
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

		if (randValue % 2 == 0)
		{
			posY += 10 * deltatime;
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

D3DXVECTOR2	 EnemyBossF::GetPos()
{
	return	D3DXVECTOR2(posX, posY);
}

void EnemyBossF::Hit(int damage)
{
	hp = hp - damage;
	isHit = true;
	if (hp <= 0)
	{
		isDead = true;
		stageManager.MakeTitleStage();
	}


}

bool EnemyBossF::IsDead()
{
	return isDead;
}


void EnemyBossF::endState()
{
	if (hp <= 0)
	{
		isDead = true;
		gameSystem.MakeItem(posX, posY);
	}
}

float EnemyBossF::GetWidth()
{
	return width;
}
float EnemyBossF::GteteHeight()
{
	return height;
}
float EnemyBossF::Getradious()
{
	return 62;
}
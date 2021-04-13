#include "stdafx.h"
#include "PlayerBulletB.h"
#include "global.h"

PlayerBulletB::PlayerBulletB(float x, float y)
{
	posX = x;
	posY = y;
	
	attack = 2;
	//bulletG = 2;
	speed = 200;
	isDead = false;
}

void PlayerBulletB::Render()
{
	TextureElement* element = textureManager.GetTexture(PLAYERBULLET2);
	element->g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 11;
	srcRect.bottom = 25;

	D3DXVECTOR3 pos(posX, posY, 0);
	D3DXVECTOR3 cen(5, 9, 0);
	element->g_Sprite->Draw(element->g_pTexture, &srcRect, &cen, &pos, D3DCOLOR_XRGB(255, 255, 255));

	element->g_Sprite->End();
}

void PlayerBulletB::Update()
{
	posY -= speed * deltatime;
	
}
D3DXVECTOR2 PlayerBulletB::GetPos()
{
	return D3DXVECTOR2(posX, posY);
}
void PlayerBulletB::Hit()
{
	isDead = true;
}
bool PlayerBulletB::IsDead()
{
	return isDead;
}

float PlayerBulletB::GetRadious()
{
	return 11;
}

void PlayerBulletB::setBullet()
{
	attack = (int)attack * 0.2 + attack;
	//bulletG = bulletG * 0.2 + bulletG;
}

int PlayerBulletB::GetAttack()
{
	return attack;
}


#include "stdafx.h"
#include "PlayerBulletA.h"
#include "global.h"

PlayerBulletA::PlayerBulletA(float x, float y, float vx, float vy)
{
	posX = x;
	posY = y;
	velX = vx;
	vleY = vy;

	attack = 1;
	//bulletG = 4;
	speed = 5;
	isDead = false;
}

void PlayerBulletA::Render()
{
	TextureElement* element = textureManager.GetTexture(PLAYERBULLET1);
	element->g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 14;
	srcRect.bottom = 14;

	D3DXVECTOR3 pos(posX, posY, 0);
	D3DXVECTOR3 cen(7, 7, 0);
	element->g_Sprite->Draw(element->g_pTexture, &srcRect, &cen, &pos, D3DCOLOR_XRGB(255, 255, 255));

	element->g_Sprite->End();
}

void PlayerBulletA::Update()
{
	posX += velX*speed;
	posY += vleY*speed;
}
D3DXVECTOR2 PlayerBulletA::GetPos()
{
	return D3DXVECTOR2(posX, posY);
}
void PlayerBulletA::Hit()
{

	isDead = true;
	
}
bool PlayerBulletA::IsDead()
{
	return isDead;
}

float PlayerBulletA::GetRadious()
{
	return 7;
}

void PlayerBulletA::setBullet()
{
	attack = attack * 0.2 + attack;
	//bulletG = bulletG * 0.2 + bulletG;
}
int PlayerBulletA::GetAttack()
{
	return attack;
}

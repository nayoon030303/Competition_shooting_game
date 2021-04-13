#pragma once
#include "Bullet.h"

class PlayerBulletA:public Bullet
{
public:
	PlayerBulletA(float x, float y, float vx, float vy);
	void Render()override;
	void Update()override;
	D3DXVECTOR2 GetPos()override;
	void Hit()override;
	bool IsDead()override;
	float GetRadious()override;
	void setBullet()override;
	int GetAttack()override;

	float posX;
	float posY;
	float velX;
	float vleY;

	float width;
	float height;
	float radious;


	
	int attack;

	float speed;
	bool isDead;
	bool isHit;
	float hp;
};
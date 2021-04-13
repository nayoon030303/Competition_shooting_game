#pragma once
#include "Enemy.h"

class EnemyBoss :public Enemy
{
public:
	EnemyBoss();
	void Render();
	void Update();
	D3DXVECTOR2 GetPos();

	void Hit(int damage);
	bool IsDead();

	float GetWidth();
	float GteteHeight();
	float Getradious();


	float posX;
	float posY;

	float velX;
	float velY;

	float width;
	float height;
	float radious;


	float speed;
	bool isHit;
	float hp;
	
	float damage;
	bool isDead;
	int state;


	void moveState();
	void movePointState();
	void endState();



	enum state
	{
		start,
		stop,
		move,
		end
	};

};
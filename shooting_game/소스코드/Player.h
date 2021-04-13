#pragma once
#include <d3dx9.h>

class Player
{
public:
	Player();
	void Render();
	void Update();
	D3DXVECTOR2 GetPos(); 
	D3DXVECTOR2 GetPosR();
	void Hit();


	void setHp();

	float posX;
	float posY;
	float width;
	float height;
	float radious;


	int exp;


	int score;
	float speed;
	bool isHit;
	float hitTime;
	int hp;
	int hpMax;
	float level;
	float damage;
	int bulletState;


	bool isF1;
	enum bulletState
	{
		bulletA,
		bulletB
	};
	
};
#pragma once
#include <d3dx9.h>

class Bullet
{
public:
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual D3DXVECTOR2 GetPos() = 0;
	virtual float GetRadious() = 0;

	virtual void Hit() = 0;
	virtual bool IsDead() = 0;

	virtual void setBullet() = 0;

	virtual  int GetAttack() = 0;
};

#pragma once
#include <d3dx9.h>

class Enemy
{
public:
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual D3DXVECTOR2 GetPos() = 0;
	virtual float GetWidth() = 0;
	virtual float GteteHeight() = 0;
	virtual float Getradious() = 0;

	virtual void Hit(int damage) = 0;
	virtual bool IsDead() = 0;
};
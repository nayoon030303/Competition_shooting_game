#pragma once
#include <d3dx9.h>

class Item
{
public:
	Item(float vx, float vy);
	void Render();
	void Update();

	D3DXVECTOR2 GetPos();
	float GeetRadious();
	bool IsHit();
	bool isHit;
	float posX;
	float posY;

	float width;
	float height;
	float radious;
};
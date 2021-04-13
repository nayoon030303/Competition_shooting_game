#include "stdafx.h"
#include "Item.h"
#include "global.h"

Item::Item(float vx, float vy)
{

	width = 37;
	height = 3;
	radious = 18;

	posX = vx;
	posY = vy;
}
void Item::Render()
{
	TextureElement* element = textureManager.GetTexture(ITEM);
	element->g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 37;
	srcRect.bottom = 33;

	D3DXVECTOR3 pos(100, 100, 0);
	D3DXVECTOR3 cen(width / 2, height / 2, 0);
	element->g_Sprite->Draw(element->g_pTexture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

	element->g_Sprite->End();
}

void Item::Update()
{

}

D3DXVECTOR2 Item::GetPos()
{
	return D3DXVECTOR2(posX, posY);
}

float Item::GeetRadious()
{
	return 18;
}

bool Item::IsHit()
{
	return isHit;
}
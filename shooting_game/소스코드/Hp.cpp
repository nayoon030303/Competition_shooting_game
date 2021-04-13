#include "stdafx.h"
#include "Hp.h"
#include "global.h"

Hp::Hp()
{

}
void Hp::Render(int i)
{
	TextureElement* element = textureManager.GetTexture(HP);
	element->g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 27;
	srcRect.bottom = 26;

	D3DXVECTOR3 pos(i*27, 0, 0);
	//D3DXVECTOR3 cen(width / 2, height / 2, 0);
	element->g_Sprite->Draw(element->g_pTexture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

	element->g_Sprite->End();
}

void Hp::Update()
{

}
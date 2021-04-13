#include "stdafx.h"
#include "BackGround.h"
#include "global.h"

BackGround::BackGround()
{
	posY = 0;
	
}

void BackGround::Render(int id)
{
	TextureElement* element = textureManager.GetTexture(id);
	TextureElement* element2 = textureManager.GetTexture(BACKGROUND2);
	element->g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 640;
	srcRect.bottom = 480;

	if (gameSystem.player->level < 3)
	{
		
		element->g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXVECTOR3 pos(0, posY, 0);
		element->g_Sprite->Draw(element->g_pTexture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		D3DXVECTOR3 posa(0, posY - WINDOW_HEIGHT, 0);
		element->g_Sprite->Draw(element->g_pTexture, &srcRect, nullptr, &posa, D3DCOLOR_XRGB(255, 255, 255));
		element->g_Sprite->End();
		
	}else
	{
		
		element2->g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXVECTOR3 pos(0, posY, 0);
		element2->g_Sprite->Draw(element2->g_pTexture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

		D3DXVECTOR3 posa(0, posY - WINDOW_HEIGHT, 0);
		element2->g_Sprite->Draw(element2->g_pTexture, &srcRect, nullptr, &posa, D3DCOLOR_XRGB(255, 255, 255));
		element2->g_Sprite->End();
	}
	
	
}

void BackGround::Update()
{
	
	posY += 2;
	posY =(int) posY % WINDOW_HEIGHT;
}
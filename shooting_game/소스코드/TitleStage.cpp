#include "stdafx.h"
#include "TitleStage.h"
#include "global.h"

TitleStage::TitleStage()
{

}

void TitleStage::Render()
{
	TextureElement* element = textureManager.GetTexture(TITLE);
	element->g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);
	
	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 640;
	srcRect.bottom = 480;

	D3DXVECTOR3 pos(0, 0, 0);
	element->g_Sprite->Draw(element->g_pTexture, &srcRect, nullptr, &pos, D3DCOLOR_XRGB(255, 255, 255));

	element->g_Sprite->End();

}
void TitleStage::Update()
{
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	if (pt.x>164 && pt.x<507 && pt.y>105 && pt.y<442)//버튼 위치 
	{
		if (inputManager.key[VK_LBUTTON] == 0 && inputManager.prevKey[VK_LBUTTON] == 1)
		{
			stageManager.MakeFirstStage(BACKGROUND1);
		}
	}
}
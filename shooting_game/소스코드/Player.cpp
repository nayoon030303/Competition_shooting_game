#include "stdafx.h"
#include "Player.h"
#include "global.h"

Player::Player()
{
	posX = 640 / 2;
	posY = 480 * 0.8;

	speed = 200.0f;
	width = 25;
	height = 38;
	radious = 20;
	score = 0;
	level = 1;

	exp = 0;
	hp = 5;
	hpMax = 5;

	isHit = false;
	hitTime = 0;
	bulletState = bulletB;
	isF1 = false;
}

void Player::Render()
{
	TextureElement* element = textureManager.GetTexture(PLAYER);
	element->g_Sprite->Begin(D3DXSPRITE_ALPHABLEND);

	RECT srcRect;
	srcRect.left = 0;
	srcRect.top = 0;
	srcRect.right = 640;
	srcRect.bottom = 480;

	
	D3DXVECTOR3 pos(posX, posY, 0);
	D3DXVECTOR3 cen(width/2,height/2,0);

	if (hitTime>0)
	{
		int randv = rand() % 10;
		if (randv%2==0)
		{
			element->g_Sprite->Draw(element->g_pTexture, &srcRect, &cen, &pos, D3DCOLOR_XRGB(255, 0, 0));
		}

	}
	else
	{
		element->g_Sprite->Draw(element->g_pTexture, &srcRect, &cen, &pos, D3DCOLOR_XRGB(255, 255, 255));
	}
	

	element->g_Sprite->End();
}

void Player::Update()
{
	hitTime -= deltatime;
	if (hitTime <=0) 
	{
		hitTime = 0;
		isHit = false;
	}

	if (inputManager.key[VK_LEFT] == 1)
	{
		posX -= speed*deltatime;
	}
	if (inputManager.key[VK_RIGHT] == 1 )
	{
		posX += speed * deltatime;
	}
	if (inputManager.key[VK_UP] == 1 )
	{
		posY -= speed * deltatime;
	}
	if (inputManager.key[VK_DOWN] == 1 )
	{
		posY += speed * deltatime;
	}
	if (inputManager.key[VK_ESCAPE] == 0 && inputManager.prevKey[VK_ESCAPE] == 1)
	{
		PostQuitMessage(0);
	}

	if (inputManager.key['Z'] == 0 && inputManager.prevKey['Z'] == 1)
	{
		if (bulletState == bulletA)
		{
			gameSystem.MakePlayerBulletA(posX, posY - 30);
		}
		else
		{
			gameSystem.MakePlayerBulletB(posX, posY - 30);
		}	
	}
	//게임 무적 f1
	if (inputManager.key[VK_F1] == 0 && inputManager.prevKey[VK_F1] == 1)
	{
		if (isF1)
			isF1 = false;
		else 
			isF1 = true;
	}
	if (inputManager.key[VK_F2] == 0 && inputManager.prevKey[VK_F2] == 1)
	{
		gameSystem.LevelUp();
	}


	//아이텀 생성 f3
	if (inputManager.key[VK_F4] == 0 && inputManager.prevKey[VK_F4] == 1)
	{
		stageManager.MakeTitleStage();
	}


	if (inputManager.key[VK_SHIFT] == 0 && inputManager.prevKey[VK_SHIFT] == 1)
	{
		if (bulletState == bulletA)
		{
			bulletState = bulletB;
		}
		else
		{
			bulletState = bulletA;
		}
	}
	
	if(posX<width/2)
	{
		posX = width/2;
	}
	if (posX > WINDOW_WIDTH-width)
	{
		posX = WINDOW_WIDTH - width;
	}
	if (posY < height / 2)
	{
		posY = height / 2;
	}
	if(posY>WINDOW_HEIGHT-height)
	{	
		posY = WINDOW_HEIGHT - height;
	}


	score = exp + hp * 100;
}

D3DXVECTOR2 Player::GetPos()
{
	return D3DXVECTOR2(posX, posY);
}

D3DXVECTOR2 Player::GetPosR()
{
	return D3DXVECTOR2(posX-width/2, posY-height/2);
}

void Player::Hit()
{
	
	if (!isF1)
	{
		
		isHit = true;
		hp--;
		hitTime = 3;
		if (hp <= 0)
		{
			stageManager.MakeTitleStage();
		}
	}
	
}

void Player::setHp()
{
	hpMax = (int)hpMax*0.2 + hpMax;
	hp = hpMax;
}
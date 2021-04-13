#include "stdafx.h"
#include "GameSystem.h"
#include "PlayerBulletA.h"
#include "PlayerBulletB.h"
#include "EnemyA.h"
#include "EnemyB.h"
#include "global.h"
#include "MathUtil.h"
#include "Hp.h"
#include "EnemyBoss.h"
#include "Item.h"
#include "EnemyBossF.h"

GameSystem::GameSystem()
{
	enemyATime = 0; 
	enemyBTime = 0;
	systemScore = 0;
	level = 1;
	count = 0;
	bulletT = 3;
}

void GameSystem::Clear()
{
	playerBullets.clear();
	enemies.clear();
	player->score = 0;
	player->hp = 3;
	systemScore = 0;
	count = 0;
}


void GameSystem::LevelUp()
{
	int lev = player->level;
	switch (lev)
	{
	case 1:
		player->exp = LEVEL2;
		break;
	case 2:
		player->exp = LEVEL3;
		break;
	case 3:
		player->exp = LEVEL4;
		break;
	case 4:
		player->exp = LEVEL5;
		break;
	default:
		break;
	}
}



void GameSystem::MakeItem(float px, float py)
{
	Item* item = new Item(px, py);
	items.push_back(item);
};

void GameSystem::MakeEnemyBoss()
{
	EnemyBoss* enemy = new EnemyBoss();
	enemies.push_back(enemy);

}

void GameSystem::MakeEnemyBossF()
{
	EnemyBossF* enemy = new EnemyBossF();
	enemies.push_back(enemy);
}

void GameSystem::MakePlayerBulletA(float x, float y)
{

	for (int i = 1; i <= 5; i++)
	{
		float angle = (i*8+70)*3.141592 / 180;
		float velx = cos(angle);
		float vleY = -sin(angle);
		PlayerBulletA* bullet = new PlayerBulletA(x, y, velx, vleY);
		playerBullets.push_back(bullet);
		//float d = (i *80 +20 )*3.141592 / 180;
		//float velx = cos(d);
		//float vleY = -sin(d);
		//PlayerBulletA* bullet = new PlayerBulletA(x, y, velx, vleY);
		//playerBullets.push_back(bullet);
	}
	

}

void GameSystem::MakePlayerBulletB(float x, float y)
{
	PlayerBulletB* bullet = new PlayerBulletB(x, y);
	playerBullets.push_back(bullet);
}

void GameSystem::MakeEnemyA()
{
	EnemyA* enemy = new EnemyA();
	enemies.push_back(enemy);
}
void GameSystem::MakeEnemyB()
{
	EnemyB* enemy = new EnemyB();
	enemies.push_back(enemy);
}

void GameSystem::MakeEnemyBullet()
{

}

void GameSystem::Update()
{

	

	enemyATime += deltatime;
	enemyBTime += deltatime;
	if (enemyATime > 1.5f)
	{
		MakeEnemyA();
		enemyATime = 0;
	}

	if(enemyBTime>2.5f)
	{
		MakeEnemyB();
		enemyBTime = 0;
	}


	//enemy업데이트
	for (auto iter = enemies.begin(); iter != enemies.end();)
	{
		(*iter)->Update();
		if ((*iter)->IsDead())
		{
			iter = enemies.erase(iter);
		}
		else
		{
			iter++;
		}
	}

	//player 총알 업데이트 
	for (auto iter = playerBullets.begin(); iter != playerBullets.end();)
	{
		(*iter)->Update();
		if ((*iter)->IsDead())
		{
			iter = playerBullets.erase(iter);
		}
		else
		{
			//bulletT -= (*iter)->bulletG;
			iter++;
		}
	}


	//enemy와 player 충돌처리
	for (int i = 0; i < enemies.size(); i++)
	{
		if (!enemies[i]->IsDead() && !player->isHit )
		{
			D3DXVECTOR2 aPos = enemies[i]->GetPos();
			float aRadious = enemies[i]->Getradious();
			
			D3DXVECTOR2 bPos = player->GetPos();
			bool result = CircleColled(aPos.x, aPos.y, aRadious, bPos.x,bPos.y, player->radious);
		
			if (result)
			{
				player->Hit();
				enemies[i]->Hit(500);
			}
		}
	}


	//enemy 와 player 총알 충돌처리 
	for (auto iter = playerBullets.begin(); iter != playerBullets.end();)
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			if (!(*iter)->IsDead())
			{
				int atack = (*iter)->GetAttack();

				D3DXVECTOR2 aPos = (*iter)->GetPos();
				float aRadious = (*iter)->GetRadious();

				D3DXVECTOR2 bPos = enemies[i]->GetPos();
				float bRadious = enemies[i]->Getradious();

				bool result = CircleColled(aPos.x, aPos.y, aRadious, bPos.x, bPos.y, bRadious);

				if (result)
				{
					(*iter)->Hit();
					enemies[i]->Hit(atack);
					player->exp = player->exp += 5;
				}
			}
		}
		iter++;
	}
	
	int bd = 10;

	if (player->exp >= LEVEL2 && player->level == 1)
	{
		setStat();

	}
	if (player->exp >= LEVEL3 && player->level == 2)
	{
		setStat();
		MakeEnemyBoss();
	}
	if (player->exp >= LEVEL4 && player->level == 3)
	{
		setStat();
	}
	if (player->exp >= LEVEL5 && player->level == 4)
	{
		setStat();
		MakeEnemyBossF();
	}

}

void GameSystem::setStat()
{
	player->level = player->level++;
	player->hpMax += (int)player->hpMax*0.2;
	player->hp = player->hpMax;
}





void GameSystem::Render()
{

	HDC hDC = GetDC(NULL);
	int nLogPixelsY = GetDeviceCaps(hDC, LOGPIXELSY);
	ReleaseDC(NULL, hDC);

	TCHAR g_strFont[LF_FACESIZE];
	int  g_nFontSize = 15;

	int nHeight = -g_nFontSize * nLogPixelsY / 72;
	D3DXCreateFont(g_pd3dDevice,            // D3D device
		nHeight,               // Height
		0,                     // Width
		FW_BOLD,               // Weight
		1,                     // MipLevels, 0 = autogen mipmaps
		FALSE,                 // Italic
		DEFAULT_CHARSET,       // CharSet
		OUT_DEFAULT_PRECIS,    // OutputPrecision
		DEFAULT_QUALITY,       // Quality
		DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
		g_strFont,              // pFaceName
		&g_pFont);              // ppFont


	const int hp = player->hp;
	const int sc = player->score;
	const int s = systemScore;
	const int level = player->level;

	if (inputManager.key[VK_F7] == 1 )
	{
		RECT rc;
		SetRect(&rc, 50, 100, 0, 0);
		WCHAR buffer[128];
		swprintf_s<128>(buffer, L"player 레벨:%d", s);
		g_pFont->DrawText(NULL, buffer, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(122.0f, 146.0f, 190.0f, 1.0f));
		
		rc;
		SetRect(&rc, 50, 200, 0, 0);
		buffer[128];
		swprintf_s<128>(buffer, L"현재까지 누적된 경험치(score):%d", level);
		g_pFont->DrawText(NULL, buffer, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(122.0f,146.0f ,190.0f, 1.0f));

		rc;
		SetRect(&rc, 300, 50, 0, 0);
		buffer[128];
		swprintf_s<128>(buffer, L"Level 1 :%d", 1000);
		g_pFont->DrawText(NULL, buffer, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(122.0f, 146.0f, 190.0f, 1.0f));
		rc;
		SetRect(&rc, 300, 100, 0, 0);
		buffer[128];
		swprintf_s<128>(buffer, L"Level 2 :%d", 2000);
		g_pFont->DrawText(NULL, buffer, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(122.0f, 146.0f, 190.0f, 1.0f));
		rc;
		SetRect(&rc, 300, 150, 0, 0);
		buffer[128];
		swprintf_s<128>(buffer, L"Level 3 :%d", 3000);
		g_pFont->DrawText(NULL, buffer, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(122.0f, 146.0f, 190.0f, 1.0f));
		rc;
		SetRect(&rc, 300, 200, 0, 0);
		buffer[128];
		swprintf_s<128>(buffer, L"Level 4 :%d", 4000);
		g_pFont->DrawText(NULL, buffer, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(122.0f, 146.0f, 190.0f, 1.0f));
		rc;
		SetRect(&rc, 300, 250, 0, 0);
		buffer[128];
		swprintf_s<128>(buffer, L"Level 5 :%d", 5000);
		g_pFont->DrawText(NULL, buffer, -1, &rc, DT_NOCLIP,
			D3DXCOLOR(122.0f,146.0f ,190.0f, 1.0f));
	}
	

	for (int i = 0; i < items.size(); i++)
	{
		items[i]->Render();
	}
	

	for (int i = 0; i < hp; i++)
	{
		playerHp->Render(i);
	}


	
	for (int i = 0; i < playerBullets.size(); i++)
	{
		
		playerBullets[i]->Render();
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Render();
		
	}


	int leve = player->level;
	RECT rc;
	SetRect(&rc, 0, 50, 0, 0);
	WCHAR buffer[128];
	swprintf_s<128>(buffer, L"Level: %d", leve);
	g_pFont->DrawText(NULL, buffer, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(122.0f, 146.0f, 190.0f, 1.0f));

	int ex = player->exp;
	rc;
	SetRect(&rc, 0, 100, 0, 0);
	buffer[128];
	swprintf_s<128>(buffer, L"Ex: %d", ex);
	g_pFont->DrawText(NULL, buffer, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(122.0f, 146.0f, 190.0f, 1.0f));

	int sco = player->score;
	rc;
	SetRect(&rc, 0, 150, 0, 0);
	buffer[128];
	swprintf_s<128>(buffer, L"score :%d", sco);
	g_pFont->DrawText(NULL, buffer, -1, &rc, DT_NOCLIP,
		D3DXCOLOR(122.0f, 146.0f, 190.0f, 1.0f));

	

}




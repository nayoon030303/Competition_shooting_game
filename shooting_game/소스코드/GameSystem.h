#pragma once

#include <vector>
#include "Player.h"

using namespace std;

class Bullet;
class Enemy;
class Hp;
class Item;

class GameSystem
{
public:
	GameSystem();
	void Clear();
	
	void MakePlayerBulletA(float x, float y);
	void MakePlayerBulletB(float x, float y);
	void MakeEnemyA();
	void MakeEnemyB();
	void MakeEnemyBoss();
	void MakeEnemyBossF();
	void MakeEnemyBullet();
	
	void MakeItem(float px, float py);


	void setStat();

	int count;

	void LevelUp();
	void AddScore();


	void Update();
	void Render();

	float enemyATime;
	float enemyBTime;
	int level;

	float bulletT;

	void Level1();
	void Level2();
	 

	float systemScore;
	 
	Player* player;
	ID3DXFont* g_pFont;
	
	vector<Item*> items;
	vector<Bullet*> playerBullets;
	vector<Enemy*> enemies;
	Hp* playerHp;
};
#pragma once
#include "Stage.h"
#include "BackGround.h"
#include "Player.h"
#include "GameSystem.h"

class FirstStage :public Stage
{
public:
	FirstStage(int id);
	void Render()override;
	void Update()override;
	
	BackGround background;
	Player player;
	
	int imgId;
};
#include "stdafx.h"
#include "FristStage.h"
#include "Player.h"
#include "global.h"


FirstStage::FirstStage(int id)
{
	
	

	gameSystem.player = &player;
	gameSystem.Clear();

	imgId = id;
}

void FirstStage::Render()
{
	background.Render(imgId);
	player.Render();
	gameSystem.Render();
	

}
	

void FirstStage::Update()
{
	background.Update();
	player.Update();
	gameSystem.Update();


}
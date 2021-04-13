#include "stdafx.h"
#include "StageManager.h"
#include "TitleStage.h"
#include "FristStage.h"


StageManager::StageManager()
{
	if (currentStage != nullptr)
	{
		delete currentStage;
	}
	TitleStage* stage = new TitleStage();
	currentStage = stage;
}

void StageManager::MakeTitleStage()
{
	if (currentStage != nullptr)
	{
		delete currentStage;
	}

	TitleStage* stage = new TitleStage();
	currentStage = stage;
}

void StageManager::MakeFirstStage(int id)
{
	if (currentStage != nullptr)
	{
		delete currentStage;
	}
	FirstStage* stage = new FirstStage(id);
	currentStage = stage;

}



void StageManager::Render()
{
	if (currentStage != nullptr)
	{
		currentStage->Render();
	}
}

void StageManager::Update()
{
	if (currentStage != nullptr)
	{
		currentStage->Update();
	}
}
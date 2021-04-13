#pragma once

class Stage;

class StageManager
{
public:
	StageManager();
	void MakeTitleStage();
	void MakeFirstStage(int id);
	void MakeSecondStage();

	void Render();
	void Update();
	
	bool isScrool = 0;
	Stage* currentStage;
};
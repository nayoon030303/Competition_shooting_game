#pragma once
#include "Stage.h"

class TitleStage:public Stage
{
public:
	TitleStage();
	void Render()override;
	void Update()override;
};
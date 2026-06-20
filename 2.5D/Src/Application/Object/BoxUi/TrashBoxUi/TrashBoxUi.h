#pragma once

#include "../BoxUiBase.h"

class TrashBoxUi : public BoxUiBase
{
public:

	TrashBoxUi() {}
	~TrashBoxUi() {}

	void Init() override;

	void Update() override;

	void DrawSprite() override;

private:

	const float PosX = 50;
	
	const float GoalPosY = -290;

	const float MaxPosY = -580;

	const float MoveSpeed = 20;

	float PosY;
};
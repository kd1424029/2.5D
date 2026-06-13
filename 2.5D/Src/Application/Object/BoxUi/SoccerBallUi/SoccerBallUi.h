#pragma once

#include "../BoxUiBase.h"

class SoccerBallUi : public BoxUiBase
{
public:

	SoccerBallUi() {}
	~SoccerBallUi() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawSprite() override;


private:


};
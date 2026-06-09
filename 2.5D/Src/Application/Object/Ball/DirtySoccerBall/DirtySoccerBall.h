#pragma once

#include "../BallBase.h"

class DirtySoccerBall : public BallBase
{
public:

	DirtySoccerBall() {}
	~DirtySoccerBall() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawLit() override;


private:

};
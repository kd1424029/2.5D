#pragma once

#include "../BallBase.h"

class SoccerBall : public BallBase
{
public:

	SoccerBall() {}
	~SoccerBall() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawLit() override;


private:


};
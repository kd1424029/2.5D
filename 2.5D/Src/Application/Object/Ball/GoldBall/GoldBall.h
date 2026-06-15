#pragma once

#include "../BallBase.h"

class GoldBall : public BallBase
{
public:

	GoldBall() {}
	~GoldBall() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawLit() override;

	void DrawBright() override;


private:


};
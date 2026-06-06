#pragma once

#include "../BallBase.h"

class BasketBall : public BallBase
{
public:

	BasketBall() {}
	~BasketBall() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawLit() override;


private:


};
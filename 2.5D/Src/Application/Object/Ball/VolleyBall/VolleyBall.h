#pragma once

#include "../BallBase.h"

class VolleyBall : public BallBase
{
public:

	VolleyBall() {}
	~VolleyBall() {}

	void Init() override;

	void Update() override;

	void PostUpdate() override;

	void DrawLit() override;


private:


};
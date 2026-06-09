#include "DirtySoccerBall.h"

void DirtySoccerBall::Init()
{
	BallBase::Init();

	ballKind = BallKind::Kind_DirtySoccerBall;
}

void DirtySoccerBall::Update()
{
	BallBase::Update();
}

void DirtySoccerBall::PostUpdate()
{
	BallBase::PostUpdate();
}

void DirtySoccerBall::DrawLit()
{
	BallBase::DrawLit();
}

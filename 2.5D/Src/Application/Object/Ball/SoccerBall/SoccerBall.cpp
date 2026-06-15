#include "SoccerBall.h"

void SoccerBall::Init()
{
	BallBase::Init();

	ballKind = BallKind::Kind_NormalBall;
}

void SoccerBall::Update()
{
	BallBase::Update();
}

void SoccerBall::PostUpdate()
{
	BallBase::PostUpdate();
}

void SoccerBall::DrawLit()
{
	BallBase::DrawLit();
}

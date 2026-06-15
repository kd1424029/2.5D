#include "BasketBall.h"

void BasketBall::Init()
{
	BallBase::Init();

	ballKind = BallKind::Kind_NormalBall;
}

void BasketBall::Update()
{
	BallBase::Update();
}

void BasketBall::PostUpdate()
{
	BallBase::PostUpdate();
}

void BasketBall::DrawLit()
{
	BallBase::DrawLit();
}

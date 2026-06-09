#include "BasketBall.h"

void BasketBall::Init()
{
	BallBase::Init();

	ballKind = BallKind::Kind_BasketBall;
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

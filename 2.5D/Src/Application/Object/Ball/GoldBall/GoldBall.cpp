#include "GoldBall.h"

void GoldBall::Init()
{
	BallBase::Init();

	ballKind = BallKind::Kind_GoldBall;

}

void GoldBall::Update()
{
	BallBase::Update();
}

void GoldBall::PostUpdate()
{
	BallBase::PostUpdate();
}

void GoldBall::DrawLit()
{
	BallBase::DrawLit();
}

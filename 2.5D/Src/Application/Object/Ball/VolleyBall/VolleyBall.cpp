#include "VolleyBall.h"

void VolleyBall::Init()
{
	BallBase::Init();

	ballKind = BallKind::Kind_VolleyBall;

}

void VolleyBall::Update()
{
	BallBase::Update();
}

void VolleyBall::PostUpdate()
{
	BallBase::PostUpdate();
}

void VolleyBall::DrawLit()
{
	BallBase::DrawLit();
}

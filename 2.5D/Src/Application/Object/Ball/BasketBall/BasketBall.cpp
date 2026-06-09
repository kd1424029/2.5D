#include "BasketBall.h"

void BasketBall::Init()
{
	BallBase::Init();

	//ポインタのままでは使い物にならないので、実体化
	m_BallModel = std::make_shared<KdModelData>();
	m_BallModel->Load("Asset/Models/Ball/BasketBall/BasketBall.gltf");

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
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BallModel, m_mWorld);
}

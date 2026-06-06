#include "BasketBall.h"

void BasketBall::Init()
{
	BallBase::Init();

	//ポインタのままでは使い物にならないので、実体化
	m_BallModel = std::make_shared<KdModelData>();
	m_BallModel->Load("Asset/Models/Ball/BasketBall.gltf");

	m_pos = { 6.4,5.9,-5 };

	Math::Matrix scaleMat = Math::Matrix::CreateScale(0.6f, 0.6f, 0.6f);

	m_mWorld = scaleMat;
	m_mWorld.Translation(m_pos);
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

#include "BasketBall.h"

void BasketBall::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_BallModel = std::make_shared<KdModelData>();
	m_BallModel->Load("Asset/Models/Ball/BasketBall.gltf");

	m_pos = { 0,4,11 };

	m_mWorld.Translation(m_pos);
}

void BasketBall::Update()
{
}

void BasketBall::PostUpdate()
{
}

void BasketBall::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BallModel, m_mWorld);
}

#include "SoccerBall.h"

void SoccerBall::Init()
{
	BallBase::Init();

	//ポインタのままでは使い物にならないので、実体化
	m_BallModel = std::make_shared<KdModelData>();
	m_BallModel->Load("Asset/Models/Ball/SoccerBall/SoccerBall.gltf");
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
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BallModel, m_mWorld);
}

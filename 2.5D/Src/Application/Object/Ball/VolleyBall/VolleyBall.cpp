#include "VolleyBall.h"

void VolleyBall::Init()
{
	BallBase::Init();

	//ポインタのままでは使い物にならないので、実体化
	m_BallModel = std::make_shared<KdModelData>();
	m_BallModel->Load("Asset/Models/Ball/VolleyBall/VolleyBall.gltf");

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
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BallModel, m_mWorld);
}

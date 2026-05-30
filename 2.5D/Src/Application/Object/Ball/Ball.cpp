#include "Ball.h"

#include "../Pipe/Pipe.h" 

void Ball::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_BallModel = std::make_shared<KdModelData>();
	m_BallModel->Load("Asset/Models/Object/Ball/Ball.gltf");

	m_pos = { -0.15,7,0 };

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld =  transMat;
}

void Ball::PreUpdate()
{
}

void Ball::Update()
{
	m_color = m_Pipe->GetColor();
}

void Ball::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BallModel, m_mWorld, m_color);
}

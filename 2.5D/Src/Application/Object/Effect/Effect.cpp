#include "Effect.h"

void Effect::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_Model = std::make_shared<KdModelData>();
	m_Model->Load("Asset/Models/Ball/ParticleBall/Ball.gltf");

}

void Effect::Update()
{
	LifeSpan--;

	if (LifeSpan <= 0)
	{
		m_isExpired = true;
		return;
	}

	// 毎フレーム移動
	m_pos += m_Move;

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;
}

void Effect::DrawLit()
{	
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_Model,m_mWorld,m_Color);
}

void Effect::SetParam(Math::Vector3 pos, Math::Vector3 move, float lifeSpan , Math::Color color)
{
	m_pos = pos;
	m_Move = move;
	LifeSpan = lifeSpan;
	m_Color = color;
}

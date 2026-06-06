#include "BallBase.h"

void BallBase::Init()
{
	m_BallModel = nullptr;
}

void BallBase::Update()
{
}

void BallBase::PostUpdate()
{
}

void BallBase::DrawLit()
{
	if (m_BallModel)
	{
		KdShaderManager::Instance().
			m_StandardShader.DrawModel(*m_BallModel, m_mWorld);
	}
}

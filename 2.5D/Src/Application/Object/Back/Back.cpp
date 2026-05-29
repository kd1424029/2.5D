#include "Back.h"

void Back::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_BackPolygon = std::make_shared<KdSquarePolygon>();
	m_BackPolygon->SetMaterial("Asset/Textures/Back/Back.png");

	m_pos = { 0,0,15 };

	Math::Matrix scaleMat = Math::Matrix::CreateScale(200, 200, 1);

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = scaleMat * transMat;
}

void Back::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawPolygon(*m_BackPolygon, m_mWorld);
}

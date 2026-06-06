#include "Back.h"

void Back::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_BackModel = std::make_shared<KdModelData>();
	m_BackModel->Load("Asset/Models/Back/Back.gltf");

	m_pos = { 0,0,4 };

	Math::Matrix scaleMat = Math::Matrix::CreateScale(1, 2, 2);

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = scaleMat * transMat;
}

void Back::DrawLit()
{
	//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BackModel, m_mWorld);
}

#include "Ground.h"

void Ground::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_GroundModel = std::make_shared<KdModelData>();
	m_GroundModel->Load("Asset/Models/Ground/Ground.gltf");

	
}

void Ground::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_GroundModel, m_mWorld);
}

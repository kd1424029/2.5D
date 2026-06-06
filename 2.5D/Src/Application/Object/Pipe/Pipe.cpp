#include "Pipe.h"

void Pipe::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_PipeModel = std::make_shared<KdModelData>();
	m_PipeModel->Load("Asset/Models/Pipe/Pipe.gltf");

	m_pos = { 0,7,11 };

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;
}

void Pipe::Update()
{
}

void Pipe::DrawLit()
{
	//KdShaderManager::Instance().m_StandardShader.DrawModel(*m_PipeModel, m_mWorld);
}

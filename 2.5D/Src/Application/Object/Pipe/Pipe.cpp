#include "Pipe.h"

void Pipe::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_PipeModel = std::make_shared<KdModelData>();
	m_PipeModel->Load("Asset/Models/Object/Pipe.gltf");

	m_pos = { -0.1,5,0 };

	//m_color = { 0,1,0,1 };

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld =  transMat;
}

void Pipe::PreUpdate()
{
}

void Pipe::Update()
{
	
}

void Pipe::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_PipeModel, m_mWorld, m_color);
}

#include "BeltConveyor.h"

void BeltConveyor::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_BeltConveyorModel = std::make_shared<KdModelData>();
	m_BeltConveyorModel->Load("Asset/Models//BeltConveyor/BeltConveyor.gltf");

	m_pos = {0,3,6.4};

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;
}

void BeltConveyor::Update()
{
}

void BeltConveyor::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BeltConveyorModel, m_mWorld);
}

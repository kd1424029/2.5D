#include "BeltConveyor.h"

void BeltConveyor::Init(int index)
{
	//ポインタのままでは使い物にならないので、実体化
	m_BeltConveyorModel = std::make_shared<KdModelData>();
	m_BeltConveyorModel->Load("Asset/Models/Object/BeltConveyor/BeltConveyor.gltf");

	//モデルの間隔
	float interval = 2.0f;

	//indexに応じてX座標をずらす（中心が左から3番目）
	m_pos = { (index - IndexObject) * interval, 3, 6.4 };

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;
}

void BeltConveyor::PreUpdate()
{
}

void BeltConveyor::Update()
{
	
}

void BeltConveyor::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BeltConveyorModel, m_mWorld);
}

#include "BeltConveyor.h"

void BeltConveyor::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_BeltConveyorModel = std::make_shared<KdModelData>();
	m_BeltConveyorModel->Load("Asset/Models/BeltConveyor/BeltConveyor.gltf");

	m_pos = {0,3,6.5};

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;

	//当たられる側の処理========
	//当たり判定をつけたいから実体化
	m_pCollider = std::make_unique<KdCollider>();

	//モデルの形状で当たり判定を登録
	m_pCollider->RegisterCollisionShape(
		"BeltConveyorModelCollision",
		m_BeltConveyorModel,
		KdCollider::TypeGround
	);
	//==========================
}

void BeltConveyor::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BeltConveyorModel, m_mWorld);
}

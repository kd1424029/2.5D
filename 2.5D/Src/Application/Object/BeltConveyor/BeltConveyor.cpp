#include "BeltConveyor.h"

#include "../Player/Player.h"

void BeltConveyor::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_BeltConveyorModel = std::make_shared<KdModelData>();
	m_BeltConveyorModel->Load("Asset/Models/BeltConveyor/BeltConveyor.gltf");

	m_ArrowUpModel = std::make_shared<KdModelData>();
	m_ArrowUpModel->Load("Asset/Models/BeltConveyor/ArrowUp/ArrowUp.gltf");

	m_ArrowDownModel = std::make_shared<KdModelData>();
	m_ArrowDownModel->Load("Asset/Models/BeltConveyor/ArrowDown/ArrowDown.gltf");

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;

	ArrowUpV = 0;

	ArrowDownV = 0;

	//当たられる側の処理
	m_pCollider = std::make_unique<KdCollider>();

	m_pCollider->RegisterCollisionShape(
		"BeltConveyorModelCollision",
		m_BeltConveyorModel,
		KdCollider::TypeGround
	);
}

void BeltConveyor::Update()
{
	if (m_TargetPlayer && m_TargetPlayer->GetGameStopped() == true)
	{
		return;
	}

	if (m_TargetPlayer && m_TargetPlayer->GetFeverFlg())
	{
		ArrowUpV += ArrowUpFeverSpeed;
		if (ArrowUpV > MaxV)
		{
			ArrowUpV -= MaxV;
		}

		ArrowDownV -= ArrowDownFeverSpeed;
		if (ArrowDownV < MaxV)
		{
			ArrowDownV += MaxV;
		}
	}
	else
	{
		ArrowUpV += ArrowUpSpeed;
		if (ArrowUpV > MaxV)
		{
			ArrowUpV -= MaxV;
		}

		ArrowDownV -= ArrowDownSpeed;
		if (ArrowDownV < MaxV)
		{
			ArrowDownV += MaxV;
		}
	}
}

void BeltConveyor::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BeltConveyorModel, m_mWorld);

	KdShaderManager::Instance().m_StandardShader.SetUVOffset({ 0,ArrowUpV });
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_ArrowUpModel, m_mWorld);
	KdShaderManager::Instance().m_StandardShader.SetUVOffset({ 0,0 });

	
	KdShaderManager::Instance().m_StandardShader.SetUVOffset({ 0,ArrowDownV });
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_ArrowDownModel, m_mWorld);
	KdShaderManager::Instance().m_StandardShader.SetUVOffset({ 0,0 });

}

void BeltConveyor::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BeltConveyorModel, m_mWorld);

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_ArrowUpModel, m_mWorld);

	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_ArrowDownModel, m_mWorld);
}

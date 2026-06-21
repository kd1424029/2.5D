#include "Shelf.h"

#include "../Player/Player.h"

void Shelf::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_ShelfModel = std::make_shared<KdModelData>();
	m_ShelfModel->Load("Asset/Models/Shelf/Shelf.gltf");

	Scale = MiddleScale;

	ScaleFlg = true;
}

void Shelf::Update()
{

	if (m_TargetPlayer != nullptr && m_TargetPlayer->GetFeverFlg())
	{
		if (ScaleFlg == true)
		{

			Scale += ScaleSpeed;

			if (Scale > MaxScale)
			{
				ScaleFlg = false;
			}
		}
		else
		{
			Scale -= ScaleSpeed;

			if (Scale < MiddleScale)
			{
				ScaleFlg = true;
			}
		}

	}
	else
	{
		Scale = MiddleScale;
	}

	Math::Matrix ScaleMat = Math::Matrix::CreateScale(Scale);

	Math::Matrix TransMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = ScaleMat * TransMat;
}

void Shelf::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_ShelfModel, m_mWorld);
}

void Shelf::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_ShelfModel, m_mWorld);
}

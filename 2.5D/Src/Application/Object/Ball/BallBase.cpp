#include "BallBase.h"

void BallBase::Init()
{
	m_BallModel = std::make_shared<KdModelData>();

	// 子クラスごとの初期化（モデル読み込みや座標設定）を実行
	ChildClassInit();

	RotationXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(RotationX));

	TransMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = RotationXMat * TransMat;
}

void BallBase::PreUpdate() 
{
}

void BallBase::DrawLit()
{
	if (m_BallModel)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BallModel, m_mWorld, m_color);
	}
}
#include "NormalBall.h"

#include "../../Pipe/Pipe.h" 

void NormalBall::ChildClassInit()
{
	//ポインタのままでは使い物にならないので、実体化
	m_BallModel = std::make_shared<KdModelData>();
	m_BallModel->Load("Asset/Models/Object/Ball/Ball.gltf");

	m_pos = { -0.08,9,0 };

	RotationX = 0.0f;

}

void NormalBall::Update()
{
	//ノーマルボールだけパイプの色と同期する
	if (m_Pipe)
	{
		m_color = m_Pipe->GetColor();
	}

	// 移動制御
	m_pos.y -= 0.05f;

	if (m_pos.y < 0)
	{
		Destroy();
	}

	RotationX += 5.0f; // 回転速度を調整

	RotationXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(RotationX));

	TransMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = RotationXMat * TransMat;
}


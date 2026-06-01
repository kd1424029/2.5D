#include "NormalBall.h"

#include "../../Pipe/Pipe.h" 

void NormalBall::ChildClassInit()
{
	//ポインタのままでは使い物にならないので、実体化
	m_BallModel = std::make_shared<KdModelData>();
	m_BallModel->Load("Asset/Models/Object/Ball/Ball.gltf");

	m_pos.x = m_Pipe->GetPos().x;
	m_pos.y = 9;
	m_pos.z = m_Pipe->GetPos().z;

	RotationX = 0.0f;


	//AliveFlg = true;
}

void NormalBall::Update()
{
	//ノーマルボールだけパイプの色と同期する
	if (!ColorGetFlg && m_Pipe)
	{		
		Math::Color color = m_Pipe->GetColor();
		//黒でなければ取得確定
		//        R                 G                 B   
		if (color.x > 0.0f || color.y > 0.0f || color.z > 0.0f)
		{
			m_color = color;
			ColorGetFlg = true;
		}
	}

	// 移動制御
	m_pos.y -= 0.07f;

	if (m_pos.y < 0)
	{
		OutputDebugStringA("[NormalBall] Destroy() 呼び出し\n");

		Destroy();

		return;
	}

	RotationX += 5.0f; // 回転速度を調整

	RotationXMat = Math::Matrix::CreateRotationX(DirectX::XMConvertToRadians(RotationX));

	TransMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = RotationXMat * TransMat;
}


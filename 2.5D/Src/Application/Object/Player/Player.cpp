#include "Player.h"

void Player::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_BasketBallBoxModel = std::make_shared<KdModelData>();
	m_BasketBallBoxModel->Load("Asset/Models/Box/BasketBallBox/BasketBallBox.gltf");

	m_ValleyBallBoxModel = std::make_shared<KdModelData>();
	m_ValleyBallBoxModel->Load("Asset/Models/Box/VolleyBallBox/VolleyBallBox.gltf");

	m_SoccerBallBoxModel = std::make_shared<KdModelData>();
	m_SoccerBallBoxModel->Load("Asset/Models/Box/SoccerBallBox/SoccerBallBox.gltf");

	m_pos = { 0,1.9,-0.1 };

	MoveCoolDownCount = 0;

	BoxPosZ = -0.1f;

	KeyFlg = false;

	m_TargetPos = m_pos; 

	MoveFlgLeft = true;

	MoveFlgRight = true;
}

void Player::PreUpdate()
{
}

void Player::Update()
{

	{//移動中の処理
		switch (m_State)
		{
		case PlayerState::Idle:
		{
			Math::Vector3 nextTarget = m_pos;
			bool inputDetected = false;

			if (GetAsyncKeyState(VK_LEFT) & 0x8000 && MoveFlgLeft == true)
			{
				nextTarget.x -= MoveAmount;
				inputDetected = true;
			}
			else if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && MoveFlgRight == true)
			{
				nextTarget.x += MoveAmount;
				inputDetected = true;
			}

			if (inputDetected == true)
			{
				m_TargetPos = nextTarget;
				m_State = PlayerState::Moving; //移動状態へ遷移
			}
		}
		break;

		case PlayerState::Moving:
		{
			Math::Vector3 moveDir = m_TargetPos - m_pos;
			float distance = moveDir.Length();

			if (distance <= MoveSpeed)
			{
				m_pos = m_TargetPos;
				MoveCoolDownCount = MoveCoolDownMax;
				m_State = PlayerState::CoolDown; //クールタイム状態へ遷移
			}
			else
			{
				moveDir.Normalize();
				m_pos += moveDir * MoveSpeed;
			}
		}
		break;

		case PlayerState::CoolDown:
		{
			MoveCoolDownCount--;

			if (MoveCoolDownCount <= 0)
			{
				m_State = PlayerState::Idle; //入力待ち状態へ遷移
			}
		}
		break;

		case PlayerState::SwitchOut:
		{
			m_pos.z -= SwitchSpeed; //奥へ引っ込む

			if (m_pos.z < SwitchDepth)
			{
				m_pos.z = SwitchDepth;

				//確定した次のタイプを代入する
				m_BoxType = m_NextBoxType;

				m_State = PlayerState::SwitchIn; //前に戻る状態へ
			}
		}
		break;

		case PlayerState::SwitchIn:
		{
			m_pos.z += SwitchSpeed; //手前へ戻る

			if (m_pos.z > BoxPosZ)
			{
				m_pos.z = BoxPosZ;
				m_State = PlayerState::Idle; //待機状態へ
			}
		}
		break;
		}
	}

	{//移動範囲の制限
		if (m_pos.x >= MoveMaxAmount)
		{
			MoveFlgRight = false;
		}
		else
		{
			MoveFlgRight = true;
		}

		if (m_pos.x <= -MoveMaxAmount)
		{
			MoveFlgLeft = false;
		}
		else
		{
			MoveFlgLeft = true;
		}
	}

	//Box切り替え処理

	// 1. まず、どれか1つでも切り替えキーが押されているかチェック
	if ((GetAsyncKeyState('Z') & 0x8000) ||(GetAsyncKeyState('X') & 0x8000) ||(GetAsyncKeyState('C') & 0x8000))
	{
		// 待機状態(Idle)かつ、まだ押しっぱなしロックがかかっていない時だけ受け付ける
		if (KeyFlg == false && m_State == PlayerState::Idle)
		{
			// 押されたキーに応じて、次に切り替える箱のタイプをあらかじめ決定する
			if (GetAsyncKeyState('Z') & 0x8000)
			{
				m_NextBoxType = BoxType::BasketBallBox;
			}

			else if (GetAsyncKeyState('X') & 0x8000)
			{
				m_NextBoxType = BoxType::VolleyBallBox;
			}

			else if (GetAsyncKeyState('C') & 0x8000)
			{
				m_NextBoxType = BoxType::SoccerBallBox;
			}

			//すでにその箱だったら下がる必要はないという最適化を入れる
			if (m_BoxType != m_NextBoxType)
			{
				m_State = PlayerState::SwitchOut; // 後ろに下がる状態へ移行！
				KeyFlg = true;                    // 押しっぱなし防止ロック！
			}
		}
	}
	else
	{
		// Z, X, C のどれも押されていない時だけロックを解除
		KeyFlg = false;
	}


	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;

}

void Player::DrawLit()
{
	// 現在のタイプに応じて描画するモデルを切り替える！
	if (m_BoxType == BoxType::BasketBallBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BasketBallBoxModel, m_mWorld);
	}
	else if(m_BoxType == BoxType::VolleyBallBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_ValleyBallBoxModel, m_mWorld);
	}
	else if (m_BoxType == BoxType::SoccerBallBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_SoccerBallBoxModel, m_mWorld);
	}
}

void Player::GenerateDepthMapFromLight()
{
	if (m_BoxType == BoxType::BasketBallBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_BasketBallBoxModel, m_mWorld);
	}
	else if (m_BoxType == BoxType::VolleyBallBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_ValleyBallBoxModel, m_mWorld);
	}
	else if (m_BoxType == BoxType::SoccerBallBox)
	{
		KdShaderManager::Instance().m_StandardShader.DrawModel(*m_SoccerBallBoxModel, m_mWorld);
	}
}

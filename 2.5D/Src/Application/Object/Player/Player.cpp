#include "Player.h"

void Player::Init()
{
	//ポインタのままでは使い物にならないので、実体化
	m_PlayerModel = std::make_shared<KdModelData>();
	m_PlayerModel->Load("Asset/Models/Player/Box.gltf");

	m_pos = { 0,1.9,-0.1 };

	MoveCoolDownCount = 0;

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

	Math::Matrix transMat = Math::Matrix::CreateTranslation(m_pos);

	m_mWorld = transMat;

}

void Player::DrawLit()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_PlayerModel, m_mWorld);
}

void Player::GenerateDepthMapFromLight()
{
	KdShaderManager::Instance().m_StandardShader.DrawModel(*m_PlayerModel, m_mWorld);
}
